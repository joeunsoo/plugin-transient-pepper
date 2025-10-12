#pragma once
#include "ProcessorProvider.h"

struct AudioProcessorProvider : ProcessorProvider {
  PluginAudioProcessor& proc;
  explicit AudioProcessorProvider(PluginAudioProcessor& p) : proc(p) {}
  
  // State
  juce::AudioProcessorValueTreeState& state() noexcept override { return proc.state; }
  juce::RangedAudioParameter* getStateParameter(const juce::String& id) noexcept override {
    return proc.state.getParameter(id);
  }
  
  // analysisData
  float getAnalysisData(int i) const noexcept override {
    return proc.analysisData[static_cast<size_t>(i)]; // 내부는 Atomic/lock-free가 이상적
  }
  
  // 출력 채널 - 스테레오 여부
  int getTotalNumOutputChannels() const noexcept override {
    return proc.getTotalNumOutputChannels();
  };
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioProcessorProvider)
};
