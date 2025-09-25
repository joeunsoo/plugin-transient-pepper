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
    currentPeak.assign((size_t) numChannels, 0.0f);
    
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
      
      
      // --- 여기서 즉시 피크 계산 ---
      for (size_t ch = 0; ch < buffer.getNumChannels(); ++ch)
      {
        auto* channelData = destSubBlock.getChannelPointer(ch);
        float localPeak = currentPeak[ch];
        for (size_t i = 0; i < numSamplesToWrite; ++i)
          localPeak = std::max(localPeak, std::abs(channelData[i]));
        currentPeak[ch] = localPeak;
      }
      
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
  
  void computePeak(juce::Span<float> output, size_t offset)
  {
    for (size_t ch = 0; ch < buffer.getNumChannels(); ++ch)
    {
      // 블럭 단위 decay 적용
      if (offset == 6) { // 엔벨로프 그래프는 다른 디케이 적용
        currentPeak[ch] *= envDecayCoeff;
      } else {
        currentPeak[ch] *= levelDecayCoeff;
      }
      
      // 블럭 전체 샘플에서 최대값 계산
      auto* channelData = buffer.getChannelPointer(ch);
      for (size_t i = 0; i < buffer.getNumSamples(); ++i)
        currentPeak[ch] = std::max(currentPeak[ch], std::abs(channelData[i]));
      
      // 출력값 0~1로 제한
      output[ch + offset] = juce::jlimit(0.0f, 1.0f, currentPeak[ch]);
    }
  }
  
  private:
  
  void updateCoefficients()
  {
    if (sampleRate <= 0.0 || numSamples <= 0)
      return;
    
    // decay 시간(ms) → 초 단위
    float decayTimeSec = levelDecayTimeMs / 1000.0f;
    float envDecayTimeSec = envDecayTimeMs / 1000.0f;
    
    // 블럭 단위 decay 계수 계산
    // formula: level *= exp(-blockSize / (sampleRate * decayTimeSec))
    levelDecayCoeff = (float)std::exp(-float(numSamples) / (sampleRate * decayTimeSec));
    envDecayCoeff   = (float)std::exp(-float(numSamples) / (sampleRate * envDecayTimeSec));
  }
  
  
  HeapBlock<float> data;                  // float 타입으로 직접 할당
  std::vector<float*> channelPtrs;        // 채널별 포인터
  dsp::AudioBlock<float> buffer { nullptr, 0, 0 }; // 나중에 prepare()에서 세팅
  int64 writeIx = 0;
  
  int numChannels = 0;
  int numSamples  = 0;
  double sampleRate = 44100.0;
  
  std::vector<float> envelope;
  std::vector<float> currentPeak; // 채널별 현재 피크
  
  float levelDecayTimeMs = 100.0f;
  float levelDecayCoeff  = 0.0f;
  
  float envDecayTimeMs = 10.0f;
  float envDecayCoeff  = 0.0f;
};
