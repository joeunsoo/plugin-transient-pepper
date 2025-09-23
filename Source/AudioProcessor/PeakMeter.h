/*
 ==============================================================================
 
 PeakMeter.h
 Created: 9 Sep 2025
 Author:  JoEunsoo
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>

class PeakMeter
{
  public:
  PeakMeter () = default; // 크기 모르는 상태로 생성
  
  void prepare (const juce::dsp::ProcessSpec& spec)
  {
    this->numChannels = static_cast<int>(spec.numChannels);
    this->numSamples  = static_cast<int>(spec.maximumBlockSize);
    this->sampleRate  = spec.sampleRate;
    
    // 필요한 샘플 공간 확보 (채널 * 샘플)
    data.allocate ((size_t) numChannels * (size_t) numSamples, true);
    
    // 포인터 배열 준비
    channelPtrs.resize ((size_t) numChannels);
    for (int ch = 0; ch < numChannels; ++ch)
      channelPtrs[(size_t) ch] = data.getData() + (size_t) ch * (size_t) numSamples;
    
    // dsp::AudioBlock 생성
    buffer = dsp::AudioBlock<float> (channelPtrs.data(),
                                     (size_t) numChannels,
                                     (size_t) numSamples);
    
    writeIx = 0;

    // envelope 초기화
    envelope.assign((size_t) numChannels, 0.0f);

    updateCoefficients();
  }

  template <typename T>
  void push (dsp::AudioBlock<T> block)
  {
    jassert (block.getNumChannels() == buffer.getNumChannels());
    
    const auto trimmed = block.getSubBlock ( block.getNumSamples()
                                            - std::min (block.getNumSamples(), buffer.getNumSamples()));
    
    const auto bufferLength = (int64) buffer.getNumSamples();
    
    for (auto samplesRemaining = (int64) trimmed.getNumSamples(); samplesRemaining > 0;)
    {
      const auto writeOffset      = writeIx % bufferLength;
      const auto numSamplesToWrite = std::min (samplesRemaining, bufferLength - writeOffset);
      
      auto destSubBlock   = buffer.getSubBlock ((size_t) writeOffset, (size_t) numSamplesToWrite);
      const auto srcBlock = trimmed.getSubBlock (trimmed.getNumSamples() - (size_t) samplesRemaining,
                                                 (size_t) numSamplesToWrite);
      
      destSubBlock.copyFrom (srcBlock);
      
      samplesRemaining -= numSamplesToWrite;
      writeIx          += numSamplesToWrite;
    }
  }
  
  template <typename T>
  void push (Span<T> s)
  {
    auto* ptr = s.begin();
    dsp::AudioBlock<T> b (&ptr, 1, s.size());
    push (b);
  }
  
  void computePeak (juce::Span<float> output, size_t offset)
  {
    jassert ((size_t) output.size() >= buffer.getNumChannels() + (size_t)offset);

    for (size_t ch = 0; ch < buffer.getNumChannels(); ++ch)
    {
      float peak = 0.0f;
      auto* channelData = buffer.getChannelPointer (ch);
      
      for (size_t i = 0; i < buffer.getNumSamples(); ++i) {
        /*
        float sample = std::fabs(channelData[i]);
        if (!std::isfinite(sample))
          sample = 0.0f;

        if (sample > envelope[ch])
          envelope[ch] = sample;
        else
          envelope[ch] += (sample - envelope[ch]) * levelDecayCoeff;
        
        // envelope 안정화
        if (!std::isfinite(envelope[ch]))
            envelope[ch] = 0.0f;
         */
        peak = std::max (peak, std::abs (channelData[i]));
      }
      
      output[ch + offset] = juce::jlimit(0.0f, 1.0f, peak);
    }
  }
  
  private:

  void updateCoefficients()
  {
      if (sampleRate <= 0.0)
          return;

    levelDecayCoeff = 1.0f - std::exp(-1.0f / (float(sampleRate) * levelDecayTimeMs / 1000.0f));
  }

  HeapBlock<float> data;                  // float 타입으로 직접 할당
  std::vector<float*> channelPtrs;        // 채널별 포인터
  dsp::AudioBlock<float> buffer { nullptr, 0, 0 }; // 나중에 prepare()에서 세팅
  int64 writeIx = 0;
  
  int numChannels = 0;
  int numSamples  = 0;
  double sampleRate = 44100.0;

  std::vector<float> envelope;

  float levelDecayTimeMs = 300.0f;
  float levelDecayCoeff  = 0.0f;
};
