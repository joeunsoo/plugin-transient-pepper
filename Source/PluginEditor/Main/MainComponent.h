#pragma once

#include <JuceHeader.h>
#include "../Provider/Providers.h"
#include "../Provider/ScaleProvider.h"
#include "../Provider/ProcessorProvider.h"
#include "CustomLookAndFeel.h"
#include "DetectorComponent.h"
#include "EnvelopeComponent.h"
#include "ToneComponent.h"
#include "MixComponent.h"

//==============================================================================
class MainComponent : public juce::Component
{
  public:
  MainComponent(Providers& pv);
  ~MainComponent() override;
  
  void paint(juce::Graphics& g) override;
  void resized() override;

  //==============================================================================
  private:
  //==============================================================================
  const ScaleProvider& scaleProvider;
  //==============================================================================
  CustomLookAndFeel mainLaf;

  //==============================================================================
  DetectorComponent detectorComponent;
  EnvelopeComponent envelopeComponent;
  ToneComponent toneComponent;
  MixComponent mixComponent;

  //==============================================================================
  juce::DropShadow dropShadow;
  //==============================================================================
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
