#pragma once

#include <JuceHeader.h>
#include "../Provider/Providers.h"
#include "../Provider/ScaleProvider.h"
#include "../Provider/ProcessorProvider.h"
#include "../UI/Knob/KnobComponent.h"
#include "../UI/Graph/GraphContainer.h"

//==============================================================================
class ToneComponent : public juce::Component,
public juce::AudioProcessorValueTreeState::Listener
{
  public:
  ToneComponent(Providers& pv);
  ~ToneComponent() override;
  //==============================================================================
  void paint(juce::Graphics& g) override;
  void resized() override;
  //==============================================================================
  void parameterChanged (const juce::String& parameterID, float newValue) override;
  
  //==============================================================================
  private:
  const ScaleProvider& scaleProvider;
  ProcessorProvider& processorProvider;
  
  KnobComponent tiltKnob, midsideKnob;
  
  // GraphContainer graphContainer;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ToneComponent)
};
