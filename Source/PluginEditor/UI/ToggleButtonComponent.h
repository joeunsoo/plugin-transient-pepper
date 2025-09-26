#pragma once

#include <JuceHeader.h>
#include "CustomToggleButton.h"

// Forward declaration
class PluginEditor;

//==============================================================================
class ToggleButtonComponent : public juce::Component
{
  public:
  ToggleButtonComponent(
                        PluginEditor& editor,
                        const String& parameterID,
                        const String Label
                        );
  ~ToggleButtonComponent() override;
  
  
  void paint(juce::Graphics& g) override;
  void resized() override;
  void setSvgDrawable(std::unique_ptr<Drawable> svgDrawable);
  
  //==============================================================================
  private:
  PluginEditor& editorRef; // 포인터로 저장하면 forward declaration 가능
  
  juce::Label label;
  CustomToggleButton toggleButton;
  
  std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> attachment;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ToggleButtonComponent)
};
