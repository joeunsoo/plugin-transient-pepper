#pragma once
#include <JuceHeader.h>
#include "../../DefineUI.h"
#include "../../Provider/ScaleProvider.h"
#include "../../Provider/ProcessorProvider.h"
#include "GraphComponent.h"

class GraphContainer : public juce::Component,
private juce::Timer
{
  public:
  GraphContainer(const ScaleProvider& sp,
                 ProcessorProvider& pp);
  ~GraphContainer() override;
  //==============================================================================

  void paint(juce::Graphics& g) override;
  void resized() override;
  
  //==============================================================================
  private:
  //==============================================================================
  void timerCallback() override; // 단일 타이머
  //==============================================================================
  
  const ScaleProvider& scaleProvider;
  ProcessorProvider& processorProvider;

  GraphComponent inputLevelGraph, envGraph;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GraphContainer)
};
