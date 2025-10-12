// DragOnlySlider.h
#pragma once
#include <JuceHeader.h>
#include "../../Provider/ScaleProvider.h"

// 마우스 드래그 외의 입력(키보드, 휠)을 모두 차단하는 슬라이더
class FaderComponent : public juce::Slider
{
  public:
  FaderComponent()
  : juce::Slider(juce::Slider::LinearVertical, juce::Slider::NoTextBox)
  {
    setScrollWheelEnabled(true);
    setInterceptsMouseClicks(true, true);
    setAlwaysOnTop(true);              // 겹치는 경우 최상위로
    
    // setVelocityModeParameters(true, 1.0, 0.0, 0.0);
    setSliderSnapsToMousePosition(false);
    
    setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    setColour(juce::Slider::trackColourId, juce::Colours::transparentBlack); // 트랙 투명 (미터가 보이도록)
    setColour(juce::Slider::backgroundColourId, juce::Colours::transparentBlack);
    setColour(juce::Slider::thumbColourId, TEAL_RGB_6.withAlpha(0.7f));
    
  };
  ~FaderComponent() override = default;
  
  void mouseEnter(const juce::MouseEvent& e) override
  {
    juce::Slider::mouseEnter(e);
    isValueText = true;
  };
  void mouseExit(const juce::MouseEvent& e) override
  {
    juce::Slider::mouseExit(e);
    isValueText = false;
  };

  void mouseDown(const juce::MouseEvent& e) override
  {
    juce::Slider::mouseDown(e);
  }
  
  // 드래그 중 값 변경은 허용 (기본 구현 사용)
  void mouseDrag(const juce::MouseEvent& e) override
  {
    juce::Slider::mouseDrag(e);
    isValueText = true;
  }
  
  void mouseUp(const juce::MouseEvent& e) override
  {
    juce::Slider::mouseUp(e);
    isValueText = false;
  }
    
  bool getIsValueText () { return isValueText; }
  

  private:
  bool isValueText = false;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FaderComponent)
};
