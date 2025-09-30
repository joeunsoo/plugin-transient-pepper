#pragma once

#include <JuceHeader.h>
#include "CustomLookAndFeel.h"
#include "DetectorComponent.h"
#include "EnvelopeComponent.h"
#include "ToneComponent.h"
#include "MixComponent.h"

// Forward declaration
class PluginEditor;

//==============================================================================
class MainComponent : public juce::Component
{
  public:
  MainComponent(PluginEditor& editor);
  ~MainComponent() override;
  
  void paint(juce::Graphics& g) override;
  void resized() override;

  //==============================================================================
  private:
  //==============================================================================
  PluginEditor& editorRef; // 포인터로 저장하면 forward declaration 가능
  CustomLookAndFeel mainLaf;
  
  DetectorComponent detectorComponent;
  EnvelopeComponent envelopeComponent;
  ToneComponent toneComponent;
  MixComponent mixComponent;
  
  juce::DropShadow dropShadow;
  //==============================================================================
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
