#pragma once

#include <JuceHeader.h>
#include "../UI/KnobComponent.h"

// Forward declaration
class PluginEditor;

//==============================================================================
class DetectorComponent : public juce::Component
{
  public:
  DetectorComponent();
  ~DetectorComponent() override;
  
  void init(PluginEditor& editor);
  
  void paint(juce::Graphics& g) override;
  void resized() override;
  
  //==============================================================================
  private:
  PluginEditor* editorRef = nullptr; // 포인터로 저장하면 forward declaration 가능

  
  juce::Label sectionLabel;
  KnobComponent thresholdKnob;
  KnobComponent bpfFreqKnob;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DetectorComponent)
};
