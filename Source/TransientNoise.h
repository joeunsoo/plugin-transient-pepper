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

    envelopeValues.resize(numChannels, 0.0f);
    
    transientFollower.prepare(spec);
    transientFollower.setAttack(0.0001f);   // 0.01f = 10ms attack
    transientFollower.setRelease(0.0001f);   // 0.1f = 100ms release
    
    noiseGenerator.setSeed(juce::Random::getSystemRandom().nextInt());
  }
  
  void reset() override
  {
    std::fill(envelopeValues.begin(), envelopeValues.end(), 0.0f);
  }
  
  void process(const juce::dsp::ProcessContextReplacing<SampleType>& context) override
  {
    auto& inputBlock = context.getInputBlock();
    auto& outputBlock = context.getOutputBlock();
    
    for (size_t ch = 0; ch < inputBlock.getNumChannels(); ++ch)
    {
      auto* in = inputBlock.getChannelPointer(ch);
      auto* out = outputBlock.getChannelPointer(ch);
      
      for (size_t n = 0; n < inputBlock.getNumSamples(); ++n)
      {
        SampleType sample = in[n];
        
        // 노이즈
        envelopeValues[ch] = transientFollower.processSample(sample, envelopeValues[ch]); // 엔벨로프 팔로워
        float dynamicNoise = noiseLevel * 0.01f * envelopeValues[ch];
        SampleType noiseSample = dynamicNoise * (noiseGenerator.nextFloat() * 2.0f - 1.0f);
        
        // out[n] = juce::jlimit(-1.0f, 1.0f, sample * gain + noiseSample);
        out[n] = sample + noiseSample;
      }
    }
  }
  
  void setNoiseLevel(SampleType level) { noiseLevel = level; }
  void setAttack(SampleType value) { transientFollower.setAttack(value); }
  void setRelease(SampleType value) { transientFollower.setRelease(value); }
  
  private:
  double sampleRate = 44100.0;
  int numChannels = 2;
  
  juce::Random noiseGenerator;
  SampleType noiseLevel = 0.05f;

  std::vector<SampleType> envelopeValues;
  TransientFollower<SampleType> transientFollower;
};
