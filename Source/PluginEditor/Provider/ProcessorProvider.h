#pragma once

struct ProcessorProvider {
  virtual ~ProcessorProvider() = default;
  
  // State
  virtual juce::AudioProcessorValueTreeState& state() noexcept = 0;
  // 선택: 편의 메서드들
  virtual juce::RangedAudioParameter* getStateParameter(const juce::String& id) noexcept = 0;
  
  // 주의: 오디오 스레드에서 갱신된 값을 메시지 스레드가 안전하게 읽을 수 있어야 함
  virtual float getAnalysisData(int index) const noexcept = 0;
  
  // 출력 채널 - 스테레오 여부
  virtual int getTotalNumOutputChannels() const noexcept = 0;
};
