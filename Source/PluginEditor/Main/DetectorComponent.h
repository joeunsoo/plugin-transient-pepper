#pragma once

#include <JuceHeader.h>

// Forward declaration
class PluginEditor;

//==============================================================================
class DetectorComponent : public juce::Component
{
  public:
  DetectorComponent();
  ~DetectorComponent() override;
  
  void paint(juce::Graphics& g) override;
  void resized() override;
  
  void setEditorRef(PluginEditor& editor);
  //==============================================================================
  private:
  PluginEditor* editorRef = nullptr; // 포인터로 저장하면 forward declaration 가능

  juce::Label label;
  juce::Label logoLabel;
  Slider rotarySlider    { Slider::RotaryHorizontalVerticalDrag, Slider::NoTextBox};

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DetectorComponent)
};
