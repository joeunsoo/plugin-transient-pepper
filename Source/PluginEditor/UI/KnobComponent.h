#pragma once

#include <JuceHeader.h>
#include "KnobSlider.h"

// Forward declaration
class PluginEditor;

//==============================================================================
class KnobComponent : public juce::Component
{
  public:
  KnobComponent(
                PluginEditor& editor,
                const String& parameterID,
                const String labelText
                );
  ~KnobComponent() override;
  
  
  void paint(juce::Graphics& g) override;
  void resized() override;
  
  void sendTooltip();

  void setColor(const String color);
  void setRingColor(const String color);

  void mouseEnter(const juce::MouseEvent& event) override;
  void mouseExit(const juce::MouseEvent& event) override;

  void setKnobDisabled(bool value);

  //==============================================================================
  private:
  PluginEditor& editorRef; // 포인터로 저장하면 forward declaration 가능
  
  // Slider rotarySlider    { Slider::RotaryHorizontalVerticalDrag, Slider::NoTextBox};
  KnobSlider rotarySlider;
  juce::Label label;
  String parameterID;
  
  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KnobComponent)
};
