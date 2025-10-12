#pragma once

#include <JuceHeader.h>
#include "../Provider/Providers.h"
#include "../Provider/ScaleProvider.h"
#include "../Provider/ProcessorProvider.h"
#include "../UI/Knob/KnobComponent.h"

// Forward declaration
class PluginEditor;

//==============================================================================
class EnvelopeComponent : public juce::Component,
public juce::AudioProcessorValueTreeState::Listener
{
  public:
  EnvelopeComponent(Providers& pv);
  ~EnvelopeComponent() override;
  
  void paint(juce::Graphics& g) override;
  void resized() override;
  
  void parameterChanged (const juce::String& parameterID, float newValue) override;
  
  //==============================================================================
  private:
  const ScaleProvider& scaleProvider;
  ProcessorProvider& processorProvider;
  //==============================================================================
  
  juce::Label sectionLabel;
  KnobComponent attackKnob, releaseKnob;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EnvelopeComponent)
};
