#pragma once

#include <JuceHeader.h>
#include "../UI/KnobComponent.h"
#include "../UI/ToggleButtonComponent.h"

// Forward declaration
class PluginEditor;

//==============================================================================
class EnvelopeComponent : public juce::Component
{
  public:
  EnvelopeComponent();
  ~EnvelopeComponent() override;
  
  void init(PluginEditor& editor);
  
  void paint(juce::Graphics& g) override;
  void resized() override;
  
  //==============================================================================
  private:
  PluginEditor* editorRef = nullptr; // 포인터로 저장하면 forward declaration 가능

  
  juce::Label sectionLabel;
  KnobComponent attackKnob;
  KnobComponent releaseKnob;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EnvelopeComponent)
};
