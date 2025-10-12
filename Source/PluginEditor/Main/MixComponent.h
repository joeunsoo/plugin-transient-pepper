#pragma once

#include <JuceHeader.h>
#include "../Provider/Providers.h"
#include "../Provider/ScaleProvider.h"
#include "../Provider/ProcessorProvider.h"
#include "../UI/Knob/KnobComponent.h"
#include "../UI/ToggleButton/ToggleButtonComponent.h"
#include "../UI/PeakMeter/PeakMeterStereoComponent.h"

//==============================================================================
class MixComponent : public juce::Component,
public juce::AudioProcessorValueTreeState::Listener
{
  public:
  MixComponent(Providers& pv);
  ~MixComponent() override;
  
  void paint(juce::Graphics& g) override;
  void resized() override;
  
  void parameterChanged (const juce::String& parameterID, float newValue) override;
  //==============================================================================
  private:
  const ScaleProvider& scaleProvider;
  ProcessorProvider& processorProvider;
  //==============================================================================

  ToggleButtonComponent wetSoloButton;
  KnobComponent noiseLevelGainKnob, dryWetKnob, outputGainKnob;
  PeakMeterStereoComponent noisePeakMeter, outputPeakMeter;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MixComponent)
};
