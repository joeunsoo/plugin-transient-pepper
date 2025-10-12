#pragma once
#include <JuceHeader.h>
#include "../../Provider/ProcessorProvider.h"
#include "../../DefineUI.h"

class PeakMeterComponent : public juce::Component,
private juce::Timer
{
  public:
  PeakMeterComponent(
                     ProcessorProvider& pp,
                     int index,
                     bool usePeakHold
                     );
  ~PeakMeterComponent() override;
  
  void paint(juce::Graphics& g) override;
  
  private:
  void timerCallback() override;

  ProcessorProvider& processorProvider;
  
  int idx = -1;
  
  // 원시 레벨과 스무딩 레벨
  float displayedLevel = 0.0f;  // raw를 attack/decay로 스무딩한 값
  float smoothedLevel  = 0.0f;  // 스큐 적용 후 실제 그리기에 사용

  // 스무딩 계수
  float attackCoeff = 0.5f;
  float decayCoeff  = 0.08f;

  // 피크 홀드
  bool showPeakHold = true;
  double peakHoldMs = 300.0;
  double peakHoldElapsedMs = 0.0;
  float peakHoldLevel = 0.0f;
  float peakHoldShownLevel = 0.0f;

  float kMeterMinDb = UI_METER_MIN_DB;
  float kMeterMaxDb = UI_METER_MAX_DB;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PeakMeterComponent)
};
