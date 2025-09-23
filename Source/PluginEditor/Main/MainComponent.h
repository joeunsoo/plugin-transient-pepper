#pragma once

#include <JuceHeader.h>
#include "DetectorComponent.h"

// Forward declaration
class PluginEditor;


//==============================================================================
class MainComponent : public juce::Component
{
  public:
  MainComponent();
  ~MainComponent() override;
  
  void paint(juce::Graphics& g) override;
  void resized() override;
  
  void setEditorRef(PluginEditor& editor);
  //==============================================================================
  private:
  PluginEditor* editorRef = nullptr; // 포인터로 저장하면 forward declaration 가능

  DetectorComponent detectorComponent;

  juce::DropShadow dropShadow;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
