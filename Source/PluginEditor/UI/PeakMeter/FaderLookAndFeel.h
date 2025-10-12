// DragOnlySlider.h
#pragma once
#include <JuceHeader.h>
#include "../../Provider/ScaleProvider.h"

class FaderComponent;

// 슬라이더 thumb 옆에 값을 표시하는 커스텀 LookAndFeel
class FaderLookAndFeel : public juce::LookAndFeel_V4
{
  public:
  FaderLookAndFeel() = default;                 // 기본 생성 허용
  explicit FaderLookAndFeel(const ScaleProvider& sp) : scaleProvider(&sp) {}
  void setScaleProvider(const ScaleProvider* sp) { scaleProvider = sp; }

  ~FaderLookAndFeel() override = default;
  
  void drawLinearSlider(juce::Graphics& g,
                        int x, int y, int width, int height,
                        float sliderPos,
                        float minSliderPos,
                        float maxSliderPos,
                        const juce::Slider::SliderStyle style,
                        juce::Slider& slider) override;
  private:
  const ScaleProvider* scaleProvider = nullptr;  // 포인터로 변경
};
