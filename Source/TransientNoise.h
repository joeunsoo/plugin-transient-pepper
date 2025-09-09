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

    tiltEQ.prepare(spec);
    tiltEQ.reset();
    
    tiltGain.setGainDecibels(0.0f);
    tiltGain.reset();
  }
  
  void reset() override
  {

  }
  
  void process(const juce::dsp::ProcessContextReplacing<SampleType>& context) override
  {
    tiltEQ.setGain(emphasis);
    tiltEQ.process(context);
    
    
    tiltGain.setGainDecibels(emphasis * 0.25f);
    tiltGain.process(context);

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
          linkedEnvelope /= (float)numChannels;
      }

      for (size_t ch = 0; ch < numChannels; ++ch)
      {
        SampleType dynamicNoise = linkChannels ? linkedEnvelope : sampleEnvelopes[ch];
        SampleType noiseSample = dynamicNoise * (noiseGenerator.nextFloat() * 2.0f - 1.0f);

        outputBlock.getChannelPointer(ch)[n] = noiseSample;
      }
    }
  }
  
  TransientFollower<SampleType> transientFollower;

  void setEmphasis(SampleType value) { emphasis = value; }
  void setLinkChannels(bool value) { linkChannels = value; }

  
  private:
  double sampleRate = 44100.0;
  int numChannels = 2;
  
  bool linkChannels = true;
  SampleType emphasis = 0.0f;

  juce::Random noiseGenerator;

  TiltEQProcessor<float> tiltEQ;
  dsp::Gain<float> tiltGain;
};
