// PeakMeter.h
#pragma once

#include <JuceHeader.h>

class PeakMeter
{
public:
  PeakMeter() = default;

  void prepare(const juce::dsp::ProcessSpec& spec)
  {
    numChannels = (int) spec.numChannels;
    numSamples  = (int) spec.maximumBlockSize;
    sampleRate  = spec.sampleRate;

    // 내부 버퍼 준비 (채널 x 샘플)
    data.allocate((size_t)numChannels * (size_t)numSamples, true);

    channelPtrs.resize((size_t)numChannels);
    for (int ch = 0; ch < numChannels; ++ch)
      channelPtrs[(size_t)ch] = data.getData() + (size_t)ch * (size_t)numSamples;

    buffer = juce::dsp::AudioBlock<float>(channelPtrs.data(),
                                          (size_t)numChannels,
                                          (size_t)numSamples);

    writeIx = 0;

    // 현재 블록 내 즉시 피크 (채널별)
    currentPeak.assign((size_t)numChannels, 0.0f);
  }

  template <typename T>
  void push(juce::dsp::AudioBlock<T> block)
  {
    jassert(block.getNumChannels() == buffer.getNumChannels());

    // 내부 버퍼 길이보다 긴 경우 뒤쪽 구간만 사용
    const auto trimmed = block.getSubBlock(block.getNumSamples()
                                           - std::min(block.getNumSamples(), buffer.getNumSamples()));
    const auto bufferLength = (int64) buffer.getNumSamples();

    // 새 블록의 측정을 시작하므로 초기화
    for (size_t ch = 0; ch < buffer.getNumChannels(); ++ch)
      currentPeak[ch] = 0.0f;

    for (auto samplesRemaining = (int64) trimmed.getNumSamples(); samplesRemaining > 0;)
    {
      const auto writeOffset       = writeIx % bufferLength;
      const auto numSamplesToWrite = std::min(samplesRemaining, bufferLength - writeOffset);

      auto destSubBlock   = buffer.getSubBlock((size_t)writeOffset, (size_t)numSamplesToWrite);
      const auto srcBlock = trimmed.getSubBlock(trimmed.getNumSamples() - (size_t)samplesRemaining,
                                                (size_t)numSamplesToWrite);

      destSubBlock.copyFrom(srcBlock);

      // 즉시 피크 계산 (최대 절대값)
      for (size_t ch = 0; ch < buffer.getNumChannels(); ++ch)
      {
        const auto* channelData = destSubBlock.getChannelPointer(ch);
        float peak = currentPeak[ch];
        for (int64 i = 0; i < numSamplesToWrite; ++i)
        {
          const float a = std::abs(channelData[(size_t)i]);
          if (a > peak) peak = a;
        }
        currentPeak[ch] = peak;
      }

      samplesRemaining -= numSamplesToWrite;
      writeIx          += numSamplesToWrite;
    }
  }

  // 현재 측정된 채널별 피크를 출력 배열에 채워 넣기
  // output.size()는 최소 채널 수 이상이어야 합니다.
  void getPeaksLinear(juce::Span<float> output) const
  {
    const size_t chs = buffer.getNumChannels();
    jassert(output.size() >= chs);
    for (size_t ch = 0; ch < chs; ++ch)
      output[ch] = juce::jlimit(0.0f, 1.0f, currentPeak[ch]);
  }

  // dBFS로 변환하여 출력 (-inf 보호: floor로 제한)
  void getPeaksDbfs(juce::Span<float> output, float floorDb = -120.0f) const
  {
    const size_t chs = buffer.getNumChannels();
    jassert(output.size() >= chs);
    for (size_t ch = 0; ch < chs; ++ch)
    {
      const float safe = std::max(currentPeak[ch], 1.0e-12f);
      const float db   = 20.0f * std::log10(safe);
      output[ch] = juce::jlimit(floorDb, 12.0f, db); // +12dB까지 여유 허용(옵션)
    }
  }

private:
  juce::HeapBlock<float> data;                 // float 타입 내부 버퍼
  std::vector<float*> channelPtrs;             // 채널별 포인터
  juce::dsp::AudioBlock<float> buffer { nullptr, 0, 0 };
  int64 writeIx = 0;

  int numChannels = 0;
  int numSamples  = 0;
  double sampleRate = 44100.0;

  // 즉시 피크 (채널별)
  std::vector<float> currentPeak;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PeakMeter)
};
