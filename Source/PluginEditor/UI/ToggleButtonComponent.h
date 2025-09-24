#pragma once

#include <JuceHeader.h>
#include "CustomToggleButton.h"

// Forward declaration
class PluginEditor;

//==============================================================================
class ToggleButtonComponent : public juce::Component
{
  public:
  ToggleButtonComponent();
  ~ToggleButtonComponent() override;
  
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
  
  juce::Label label;
  CustomToggleButton toggleButton;
  
  std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> attachment;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ToggleButtonComponent)
};
