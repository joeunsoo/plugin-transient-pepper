#pragma once

#include <JuceHeader.h>
#include "../Provider/Providers.h"
#include "../Provider/ScaleProvider.h"
#include "../Provider/ProcessorProvider.h"
#include "../UI/Knob/KnobComponent.h"
#include "../UI/ToggleButton/ToggleButtonComponent.h"

//==============================================================================
class DetectorComponent : public juce::Component,
public juce::AudioProcessorValueTreeState::Listener
{
  public:
  DetectorComponent(Providers& pv);
  ~DetectorComponent() override;
  
  void paint(juce::Graphics& g) override;
  void resized() override;
  
  void parameterChanged (const juce::String& parameterID, float newValue) override;
  
  //==============================================================================
  private:
  const ScaleProvider& scaleProvider;
  ProcessorProvider& processorProvider;

  //==============================================================================
  bool isStereo = false;
  juce::Label sectionLabel;
  KnobComponent thresholdKnob, bpfFreqKnob;
  
  ToggleButtonComponent channelLinkButton, bpfPowerButton, sidechainListenButton;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DetectorComponent)
};
