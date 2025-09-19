/*
 ==============================================================================
 
 MidSideMixer.h
 Created: 9 Sep 2025 3:00:31am
 Author:  JoEunsoo
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>

template <typename SampleType>
class MidSideMixer : public juce::dsp::ProcessorBase
{
  public:
  MidSideMixer() = default;
  
  void prepare(const juce::dsp::ProcessSpec& spec) override
  {
    sampleRate = spec.sampleRate;
  }
  
  void reset() override {}
  
  void process(const juce::dsp::ProcessContextReplacing<SampleType>& context) override
  {
    auto& inBlock = context.getInputBlock();
    auto& outBlock = context.getOutputBlock();
    
    auto numSamples = inBlock.getNumSamples();
    auto numChannels = inBlock.getNumChannels();

    if (numChannels < 2) { // 모노면 그냥 넘어감
      return;
    }

    jassert(numChannels >= 2); // 최소 스테레오 필요
    
    int numSamplesInt = static_cast<int>(numSamples);

    for (int i = 0; i < numSamplesInt; ++i)
    {
      SampleType L = inBlock.getSample(0, i);
      SampleType R = inBlock.getSample(1, i);
      
      // LR -> MS 변환
      SampleType mid = 0.5f * (L + R);
      SampleType side = 0.5f * (L - R);
      
      // MixLevel = 0 → Mid만, 1 → Side만
      SampleType mixedMid  = mid  * (1.0f - mixLevel);
      SampleType mixedSide = side * mixLevel;

      // MS -> LR 변환
      outBlock.setSample(0, i, mixedMid + mixedSide);
      outBlock.setSample(1, i, mixedMid - mixedSide);
    }
  }
  
  // 단일 믹스 레벨 (0.0 ~ 2.0)
  void setMixLevel(SampleType level) { mixLevel = juce::jlimit(0.0f, 1.0f, level); }
  
  private:
  double sampleRate = 44100.0;
  SampleType mixLevel = 1.0f;
};
