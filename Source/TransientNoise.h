/*
 ==============================================================================
 
 TransientNoise.h
 Created: 8 Sep 2025 3:45:52pm
 Author:  JoEunsoo
 
 ==============================================================================
 */

#pragma once
#include <JuceHeader.h>
#include "TransientFollower.h"
#include "TiltEQ.h"
#include "BandPassFilter.h"
#include "TransientNoiseLayer.h"

template <typename SampleType>
class TransientNoiseProcessor : public juce::dsp::ProcessorBase
{
  public:
  TransientNoiseProcessor() {}
  ~TransientNoiseProcessor() override {}
  
  void prepare(const juce::dsp::ProcessSpec& spec) override
  {
    sampleRate = spec.sampleRate;
    numChannels = spec.numChannels;
    
    sidechainTilt.prepare(spec);
    sidechainTilt.reset();
    sidechainTiltGain.setGainDecibels(0.0f);
    sidechainTiltGain.reset();
    
    sidechainBPF.prepare(spec);
    sidechainBPF.reset();
    sidechainBPFGain.prepare(spec);
    sidechainBPFGain.reset();
    
    transientFollower.prepare(spec);
    
    hfClick.prepare(spec);
    resonator.prepare(spec);
    bitCrusher.prepare(spec);
    airLayer.prepare(spec);
    noiseGenerator.setSeed(juce::Random::getSystemRandom().nextInt());
  }
  
  void reset() override
  {
    
  }
  
  void process(const juce::dsp::ProcessContextReplacing<SampleType>& context) override
  {
    sidechainTilt.setGain(emphasis);
    sidechainTiltGain.setGainDecibels(emphasis * 0.4f);
    
    // (value - minFreq) / (maxFreq - minFreq)
    float normalized = (sidechainBPFFreq - 100.0f) / (12000.0f - 100.0f);
    float skewed = std::pow(normalized, 0.27f); // skew 적용, 중앙값 1000Hz로 맞춘 경우
    sidechainBPFGain.setGainDecibels((skewed * 18.0f) - 12.0f);
    sidechainBPF.setFrequency(sidechainBPFFreq);
    
    sidechainTilt.process(context);
    sidechainTiltGain.process(context);
    
    if (sidechainBPFOn) {
      sidechainBPF.process(context);
      sidechainBPFGain.process(context);
    }
    
    auto& inputBlock = context.getInputBlock();
    auto& outputBlock = context.getOutputBlock();
    
    const auto numSamples = inputBlock.getNumSamples();
    const auto numChannels = inputBlock.getNumChannels();
    
    for (size_t n = 0; n < numSamples; ++n)
    {
      SampleType linkedEnvelope = 0.0f;
      
      // 채널별 엔벨로프 계산
      std::vector<SampleType> sampleEnvelopes(numChannels, 0.0f);
      for (size_t ch = 0; ch < numChannels; ++ch)
      {
        SampleType sample = inputBlock.getChannelPointer(ch)[n];
        sampleEnvelopes[ch] = transientFollower.processSample(sample, ch); // 엔벨로프 팔로워
      }
      
      // Step 2: 링크 모드 처리
      if (linkChannels)
      {
        // 평균값 링크 (원하면 max() 등 다른 방식 가능)
        for (auto v : sampleEnvelopes) linkedEnvelope += v;
        linkedEnvelope /= (SampleType)numChannels;
      }
      
      for (size_t ch = 0; ch < numChannels; ++ch)
      {
        SampleType dynamicNoise = linkChannels ? linkedEnvelope : sampleEnvelopes[ch];
        
        SampleType in = inputBlock.getChannelPointer(ch)[n];
        SampleType out = 0;
        // out = hfClick.processSample(ch, static_cast<float>(1.0));
        // out = resonator.processSample(ch, static_cast<float>(in));
        // out = bitCrusher.processSample(static_cast<float>(in));
        // out = airLayer.processSample();
        out = (noiseGenerator.nextFloat() * 2.0f - 1.0f);
        
#if !CHECK_ENV
        outputBlock.getChannelPointer(ch)[n] = dynamicNoise * out;
#else
        outputBlock.getChannelPointer(ch)[n] = dynamicNoise;
#endif
      }
    }
  }
  
  TransientFollower<SampleType> transientFollower;
  
  void setLinkChannels(bool value) { linkChannels = value; }
  void setEmphasis(SampleType value) { emphasis = value; }
  void setSidechainBPFOn(bool value) { sidechainBPFOn = value; }
  void setSidechainBPFFreq(float value) { sidechainBPFFreq = value; }
  
  private:
  double sampleRate = 44100.0;
  int numChannels = 2;
  bool linkChannels = true;
  
  juce::Random noiseGenerator;
  
  HFClick hfClick;
  TransientResonator resonator;
  BitCrusher bitCrusher;
  AirLayer airLayer;
  
  TiltEQProcessor<SampleType> sidechainTilt;
  dsp::Gain<SampleType> sidechainTiltGain;
  SampleType emphasis = 0.0f;
  
  BandPassFilter<SampleType> sidechainBPF;
  dsp::Gain<SampleType> sidechainBPFGain;
  bool sidechainBPFOn = false;
  float sidechainBPFFreq = 1000.0f;
};
