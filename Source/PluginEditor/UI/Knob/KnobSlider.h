#pragma once

#include "../../DefineUI.h"
#include "../../Provider/ScaleProvider.h"

struct KnobSlider : public juce::Slider
{
  KnobSlider(const ScaleProvider& sp)
  : juce::Slider(juce::Slider::RotaryHorizontalVerticalDrag, juce::Slider::NoTextBox),
  scaleProvider(sp)
  {
    setMouseDragSensitivity (UI_KNOB_DRAG_SENSITIVITY);
  }

  void resized() override
  {
    // 유효 크기 보장 후만 작업
    if (getWidth() <= 0 || getHeight() <= 0)
      return;

    setMouseDragSensitivity(juce::jmax(1, int(UI_KNOB_DRAG_SENSITIVITY * scaleProvider.getScale())));

    juce::Slider::resized();
  };
  
  // 커스텀 멤버
  juce::String color = "primary";
  juce::String ringColor = "primary";
  bool isDisabled = false;
  
  private:
  const ScaleProvider& scaleProvider;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KnobSlider)
};
