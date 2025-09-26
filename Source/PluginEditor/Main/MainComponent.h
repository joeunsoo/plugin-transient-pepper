#pragma once

#include <JuceHeader.h>
#include "DetectorComponent.h"
#include "EnvelopeComponent.h"
#include "ToneComponent.h"
#include "MixComponent.h"
#include "../UI/CustomLookAndFeel.h"

// Forward declaration
class PluginEditor;


//==============================================================================
class MainComponent : public juce::Component
{
  public:
  MainComponent();
  ~MainComponent() override;
  
  void init(PluginEditor& editor);

  void paint(juce::Graphics& g) override;
  void resized() override;

  //==============================================================================
  private:
  PluginEditor* editorRef = nullptr; // 포인터로 저장하면 forward declaration 가능
  CustomLookAndFeel mainLaf;

  DetectorComponent detectorComponent;
  EnvelopeComponent envelopeComponent;
  ToneComponent toneComponent;
  MixComponent mixComponent;

  juce::DropShadow dropShadow;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
