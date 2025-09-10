/*
 ==============================================================================
 
 PluginAudioProcessor.cpp
 Created: 3 Sep 2025 11:01:38am
 Author:  JoEunsoo
 
 ==============================================================================
 */

#include <JuceHeader.h>
#include "Define.h"
#include "PluginAudioProcessor.h"


//==============================================================================
PluginAudioProcessor::PluginAudioProcessor (AudioProcessorValueTreeState::ParameterLayout layout)
: AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                  .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
#endif
                  .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
#endif
                  ),
parameters (layout),
state (*this, nullptr, "STATE", std::move (layout))
{
  // PropertiesFile 옵션 설정
  juce::PropertiesFile::Options options;
  options.applicationName     = "preferences";
  options.filenameSuffix      = ".xml";
  options.folderName          = "JoEunsoo/RustyTone"; // macOS: ~/Library/Application Support/JoEunsoo/RustyTone.settings
  options.osxLibrarySubFolder = "Application Support";
  options.storageFormat       = juce::PropertiesFile::storeAsXML;
  
  // ApplicationProperties 객체를 통해 관리
  appProperties.setStorageParameters(options);
  
  // PropertiesFile 가져오기
  props = appProperties.getUserSettings();
  
  // 값 불러오기
  windowScale  = props->getIntValue("windowScale", 100);
}

//==============================================================================
PluginAudioProcessor::~PluginAudioProcessor()
{
  // 종료 시 값 저장
  props->setValue("windowScale", windowScale);
  
  props->saveIfNeeded();
}

//==============================================================================
void PluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
  const auto channels = std::max (getTotalNumInputChannels(), getTotalNumOutputChannels());
  
  if (channels == 0)
    return;
  
  const juce::dsp::ProcessSpec spec =
  { sampleRate, (uint32_t) samplesPerBlock, (uint32_t) channels };
  
  sampleRate = spec.sampleRate;
  
  
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
  
  noisePeakMeter.prepare(channels, samplesPerBlock);
  peakMeter.prepare(channels, samplesPerBlock);
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
  
  noiseLevelGain.setGainDecibels(parameters.noiseLevelGain.get());
  
  float dryWetAdjust = 6.0f - 0.12f * std::abs(parameters.dryWet.get() - 50.0f); // Dry/Wet 50% -6dB 손실 보정
  outputGain.setGainDecibels(parameters.outputGain.get() + dryWetAdjust);
  
  tiltEQ.setGain(parameters.tilt.get());
  tiltGain.setGainDecibels(parameters.tilt.get() * (-0.6f));
  
  midSideMixer.setMixLevel(parameters.midSide.get() / 100.0f);
  
  transientNoise.setEmphasis(parameters.emphasis.get());
  transientNoise.transientFollower.setTAttack(parameters.attack.get());
  transientNoise.transientFollower.setTRelease(parameters.release.get());
  transientNoise.transientFollower.setThresholdDecibels(parameters.threshold.get());
  transientNoise.setLinkChannels(parameters.linkChannels.get());
  
#if ADVANCED
  transientNoise.transientFollower.setFastAttack(parameters.fastAttack.get());
  transientNoise.transientFollower.setFastRelease(parameters.fastRelease.get());
  transientNoise.transientFollower.setSlowAttack(parameters.slowAttack.get());
  transientNoise.transientFollower.setSlowRelease(parameters.slowRelease.get());
#endif
  
  float wetMix = (parameters.dryWet.get() / 100.0f);
  if (parameters.wetSolo.get()) {
    wetMix = 1.0f;
  }
  if (parameters.bypass.get()) {
    wetMix = 0.0f;
  }
  dryWetMixer.setWetMixProportion (wetMix);
  
  auto outBlock = dsp::AudioBlock<float> { buffer }.getSubsetChannelBlock (0, (size_t) getTotalNumOutputChannels());

  dryWetMixer.pushDrySamples (outBlock); // Dry 신호 저장
  
  transientNoise.process(dsp::ProcessContextReplacing<float> (outBlock));
  
  tiltEQ.process(dsp::ProcessContextReplacing<float> (outBlock));
  tiltGain.process(dsp::ProcessContextReplacing<float> (outBlock));
  
  midSideMixer.process(dsp::ProcessContextReplacing<float> (outBlock));
  
  dcBlocker.process(dsp::ProcessContextReplacing<float> (outBlock));
  
  noiseLevelGain.process(dsp::ProcessContextReplacing<float> (outBlock));
  noisePeakMeter.push (outBlock);

  dryWetMixer.mixWetSamples (outBlock); // Dry/Wet 믹스
  
  if (!parameters.bypass.get()) {
    outputGain.process(dsp::ProcessContextReplacing<float> (outBlock));
  }
  
  peakMeter.push (outBlock);
  {
    const SpinLock::ScopedTryLockType lock (peakDataLock);
    
    if (! lock.isLocked()) { return; }
    
    Span<float> peakMeterSpan(analysisData.data(), 4); // 0,1 사용
    
    peakMeter.computePeak ({ peakMeterSpan.data(), peakMeterSpan.size() }, 0); // 0,1
    noisePeakMeter.computePeak ({ peakMeterSpan.data(), peakMeterSpan.size() }, 2); // 2,3
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
