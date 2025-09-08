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

    transientFollower.prepare(spec);
    
    noiseGenerator.setSeed(juce::Random::getSystemRandom().nextInt());
  }
  
  void reset() override
  {
    // std::fill(envelopeValues.begin(), envelopeValues.end(), 0.0f);
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
        
        SampleType transient = transientFollower.processSample(sample, ch); // 엔벨로프 팔로워
        float dynamicNoise = transient;
        SampleType noiseSample = dynamicNoise * (noiseGenerator.nextFloat() * 2.0f - 1.0f);

        out[n] = noiseSample;
      }
    }
  }
  
  void setNoiseLevel(SampleType level) { noiseLevel = level; }
  void setTAttack(SampleType value) { transientFollower.setTAttack(value); }
  void setTRelease(SampleType value) { transientFollower.setTRelease(value); }
  void setThreshold(SampleType value) { transientFollower.setThreshold(value); }
  
  private:
  double sampleRate = 44100.0;
  int numChannels = 2;
  
  juce::Random noiseGenerator;
  SampleType noiseLevel = 0.05f;
  
  // std::vector<SampleType> envelopeValues;
  TransientFollower<SampleType> transientFollower;
};
