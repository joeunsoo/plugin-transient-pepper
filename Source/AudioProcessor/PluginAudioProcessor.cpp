/*
 ==============================================================================
 
 PluginAudioProcessor.cpp
 Created: 3 Sep 2025 11:01:38am
 Author:  JoEunsoo
 
 ==============================================================================
 */

#include <JuceHeader.h>
#include "../Define.h"
#include "PluginAudioProcessor.h"


//==============================================================================
PluginAudioProcessor::PluginAudioProcessor(AudioProcessorValueTreeState::ParameterLayout layout)
: AudioProcessor (BusesProperties()
                  .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                  .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
parameters (layout),
state (*this, nullptr, "STATE", std::move (layout))
{
  
}

PluginAudioProcessor::~PluginAudioProcessor() = default;


//==============================================================================
void PluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
  const auto channels = std::max (getTotalNumInputChannels(), getTotalNumOutputChannels());
  
  if (channels == 0)
    return;
  
  juce::dsp::ProcessSpec spec = { sampleRate, (uint32_t) samplesPerBlock, (uint32_t) channels };
  
  noiseLevelGain.setGainDecibels(0.0f);
  noiseLevelGain.reset();
  outputGain.setGainDecibels(0.0f);
  outputGain.reset();
  tiltGain.setGainDecibels(0.0f);
  tiltGain.reset();
  
  dryWetMixer.setMixingRule (juce::dsp::DryWetMixingRule::linear);
  dryWetMixer.prepare (spec);
  dryWetMixer.setWetMixProportion (1.0f);
  
  transientNoise.prepare(spec);
  transientNoise.reset();
  
  tiltEQ.prepare(spec);
  
  midSideMixer.prepare(spec);
  midSideMixer.reset();
  
  noisePeakMeter.prepare(spec);
  peakMeter.prepare(spec);
  envPeakMeter.prepare(spec);
  inputPeakMeter.prepare(spec);
  
  dcBlocker.prepare(spec);
  dcBlocker.reset();
}

bool PluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
      && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
    return false;
  
  if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
    return false;
  
  return true;
}

void PluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                         juce::MidiBuffer&)
{
  juce::ScopedNoDenormals noDenormals;
  
  const auto totalNumInputChannels  = getTotalNumInputChannels();
  const auto totalNumOutputChannels = getTotalNumOutputChannels();
  
  for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    buffer.clear (i, 0, buffer.getNumSamples());
  
  transientNoise.setSidechainBPFOn(parameters.bpfPower.get());
  transientNoise.setSidechainBPFFreq(parameters.bpfFrequency.get());
  transientNoise.setSidechainListen(parameters.sidechainListen.get());
  
  transientNoise.setAttack(parameters.attack.get());
  transientNoise.setRelease(parameters.release.get());
  transientNoise.setThresholdDecibels(parameters.threshold.get());
  transientNoise.setLinkChannels(parameters.linkChannels.get());
  
  noiseLevelGain.setGainDecibels(parameters.noiseLevelGain.get());
  
  float tiltValue = parameters.tilt.get();
  tiltEQ.setGain(tiltValue);
  float tiltGainValue = skewedMap(tiltValue, -12.0f, 12.0f, -6.0f, 0.0f, 1.0f);
  tiltGain.setGainDecibels(tiltGainValue);
  
  midSideMixer.setMixLevel(parameters.midSide.get() / 100.0f);
  
  float wetMix = parameters.dryWet.get();
  if (parameters.wetSolo.get()) wetMix = 100.0f;
  if (parameters.bypass.get()) wetMix = 0.0f;
  if (parameters.sidechainListen.get()) wetMix = 100.0f;
  dryWetMixer.setWetMixProportion(wetMix / 100.0f);
  
  float dryWetAdjust = 6.0f - 0.12f * std::abs(wetMix - 50.0f); // Dry/Wet 50% -6dB 손실 보정
  outputGain.setGainDecibels(parameters.outputGain.get() + dryWetAdjust);
  
  /// DSP 계산 시작
  auto outBlock = dsp::AudioBlock<float> { buffer }.getSubsetChannelBlock (0, (size_t) getTotalNumOutputChannels());
  
  
  const auto numSamples = outBlock.getNumSamples();
  const auto numChannels = outBlock.getNumChannels();
  
  inputPeakMeter.push (outBlock);
  
  if (!parameters.bypass.get() && activated) { // Bypass 아닐때, 그리고 제품활성화 중일때
    dryWetMixer.pushDrySamples (outBlock); // Dry 신호 저장
    
    transientNoise.process(dsp::ProcessContextReplacing<float> (outBlock));
    envPeakMeter.push (transientNoise.envBlock); // Ouput 피크미터 저장
    
    if (!parameters.sidechainListen.get()) {
      tiltEQ.process(dsp::ProcessContextReplacing<float> (outBlock));
      tiltGain.process(dsp::ProcessContextReplacing<float> (outBlock));
      
      midSideMixer.process(dsp::ProcessContextReplacing<float> (outBlock)); // 미드 사이드 믹서
      
#if !CHECK_ENV && !CHECK_SIDECHAIN && !DISABLE_DCOFFSET_FILTER
      dcBlocker.process(dsp::ProcessContextReplacing<float> (outBlock)); // 초저음 제거
#endif
      noiseLevelGain.process(dsp::ProcessContextReplacing<float> (outBlock)); // 노이즈 게인
    }
    noisePeakMeter.push (outBlock); // 노이즈 레벨 미터 저장
    
    dryWetMixer.mixWetSamples (outBlock); // Dry/Wet 믹스
    
    outputGain.process(dsp::ProcessContextReplacing<float> (outBlock)); // 출력 게인
  } else { // Bypass 중
    juce::AudioBuffer<float> bypassBuffer((int)numChannels, (int)numSamples);
    bypassBuffer.clear(); // 완전히 0으로 초기화
    
    juce::dsp::AudioBlock<float> emptyBlock(bypassBuffer);
    
    envPeakMeter.push (emptyBlock); // Ouput 피크미터 저장
    noisePeakMeter.push (emptyBlock); // 노이즈 레벨 미터 저장
  }
  
  peakMeter.push (outBlock); // Ouput 피크미터 저장
  
  // 미터 데이터 락
  {
    const SpinLock::ScopedTryLockType lock (peakDataLock);
    
    if (! lock.isLocked()) { return; }
    
    Span<float> peakMeterSpan(analysisData.data(), 8); // 0,1 사용
    
    peakMeter.getPeaksDbfs ({ peakMeterSpan.data(), peakMeterSpan.size() }); // 0,1
    noisePeakMeter.getPeaksDbfs ({ peakMeterSpan.data() + 2, peakMeterSpan.size() }); // 2,3
    inputPeakMeter.getPeaksDbfs ({ peakMeterSpan.data() + 4, peakMeterSpan.size() }); // 4,5
    envPeakMeter.getPeaksDbfs ({ peakMeterSpan.data() + 6, peakMeterSpan.size() }); // 6,7
  }
}

//==============================================================================
void PluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
  // juce::ignoreUnused (destData);
  
  auto vsState = state.copyState();
  std::unique_ptr<juce::XmlElement> xml (vsState.createXml());
  copyXmlToBinary (*xml, destData);
}

void PluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
  // juce::ignoreUnused (data, sizeInBytes);
  
  std::unique_ptr<juce::XmlElement> xml (getXmlFromBinary (data, sizeInBytes));
  
  if (xml != nullptr && xml->hasTagName (state.state.getType()))
    state.replaceState (juce::ValueTree::fromXml (*xml));
}

int PluginAudioProcessor::getLatencySamples() const
{
  return 0;
}
