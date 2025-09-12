/*
 ==============================================================================
 
 TransientNoiseSculptor.h
 Created: 12 Sep 2025 1:32:55am
 Author:  JoEunsoo
 
 ==============================================================================
 */

#pragma once
#include <JuceHeader.h>
#include "TransientNoiseLayer.h"

template <typename SampleType>
class TransientNoiseSculptor : public juce::dsp::ProcessorBase
{
  public:
  void prepare(const juce::dsp::ProcessSpec& spec) override
  {
    sr = spec.sampleRate;
    blockSize = static_cast<int>(spec.maximumBlockSize);
    
    transientFollower.prepare(spec);
    
    hfClick.prepare(spec);
    resonator.prepare(spec);
    bitCrusher.prepare(spec);
    airLayer.prepare(spec);
    
    envelopeBuffer.setSize(1, blockSize);
    envelopeBuffer.clear();
  }
  
  void reset() override
  {
    prevSample = 0.0f;
    envelopeBuffer.clear();
  }
  
  bool detectTransient(SampleType input)
  {
    const SampleType threshold = static_cast<SampleType>(0.05);
    bool isTransient = std::abs(input) > threshold && prevSample <= threshold;
    prevSample = std::abs(input);
    return isTransient;
  }
  
  void process(const juce::dsp::ProcessContextReplacing<SampleType>& context) override
  {
    auto& inputBlock = context.getInputBlock();
    auto& outputBlock = context.getOutputBlock();
    int numSamples = static_cast<int>(outputBlock.getNumSamples());
    int numChannels = static_cast<int>(outputBlock.getNumChannels());
    
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
      
      for (int ch = 0; ch < numChannels; ++ch)
      {
        SampleType input = inputBlock.getChannelPointer(ch)[n];
        // bool trig = detectTransient(input);
        
        SampleType out = 0;
        
        SampleType dynamicNoise = linkChannels ? linkedEnvelope : sampleEnvelopes[ch];
        input = dynamicNoise * input * 1.5f;

          // out += hfClick.processSample(ch, static_cast<float>(1.0));
          out += resonator.processSample(ch, static_cast<float>(input));
          // out += bitCrusher.processSample(static_cast<float>(input));
          // out += airLayer.processSample();
        out = dynamicNoise * out * 0.1f;
        outputBlock.getChannelPointer(ch)[n] = out;
      }
    }
  }
  
  TransientFollower<SampleType> transientFollower;
  
  void setLinkChannels(bool value) { linkChannels = value; }

  private:
  double sr = 44100.0;
  int blockSize = 512;
  SampleType prevSample = 0;
  bool linkChannels = false;
  
  juce::AudioBuffer<float> envelopeBuffer;
  
  
  // 레이어 인스턴스
  HFClick hfClick;
  TransientResonator resonator;
  BitCrusher bitCrusher;
  AirLayer airLayer;
};
