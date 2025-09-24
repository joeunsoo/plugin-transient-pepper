#pragma once

#include <JuceHeader.h>
#include "KnobSlider.h"

// Forward declaration
class PluginEditor;

//==============================================================================
class KnobComponent : public juce::Component
{
  public:
  KnobComponent();
  ~KnobComponent() override;
  
  void init(
            PluginEditor& editor,
            const String& parameterID,
            const String Label
            );
  
  void paint(juce::Graphics& g) override;
  void resized() override;
  
  //==============================================================================
  private:
  PluginEditor* editorRef = nullptr; // 포인터로 저장하면 forward declaration 가능
  
  // Slider rotarySlider    { Slider::RotaryHorizontalVerticalDrag, Slider::NoTextBox};
  KnobSlider rotarySlider;
  juce::Label label;
  juce::Label tooltipLabel;
  
  
  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KnobComponent)
};
