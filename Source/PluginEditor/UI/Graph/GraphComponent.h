#pragma once
#include <JuceHeader.h>
#include "../../Provider/ScaleProvider.h"
#include "../../DefineUI.h"

class GraphComponent : public juce::Component
{
  public:
  GraphComponent(const ScaleProvider& sp,
                 juce::Colour f,
                 juce::Colour s,
                 int index
                 );
  ~GraphComponent() override;
  
  
  
  void paint(juce::Graphics& g) override;
  void updateGraph (float level1, float level2);
  
  private:  
  const ScaleProvider& scaleProvider;

  int idx = -1;
  float lastY = 1.0f;
  int movePixels = 4;
  
  bool isGraphInit = false;

  // 원시 레벨과 스무딩 레벨
  float displayedLevel = 0.0f;  // raw를 attack/decay로 스무딩한 값

  // 스무딩 계수
  float attackCoeff = 0.5f;
  float decayCoeff  = 0.5f;

  float kMeterMinDb = UI_METER_MIN_DB;
  float kMeterMaxDb = UI_METER_MAX_DB;

  juce::Colour fillColour, strokeColour;

  std::vector<float> graphValues; // x축 값 순서대로 저장
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GraphComponent)
};
