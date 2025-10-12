#pragma once

#include <JuceHeader.h>
#include "CustomToggleButton.h"
#include "../../Provider/ProcessorProvider.h"
#include "../../Provider/ScaleProvider.h"

//==============================================================================
class ToggleButtonComponent : public juce::Component
{
  public:
  ToggleButtonComponent(const ScaleProvider& sp,
                        ProcessorProvider& pp,
                        const String& parameterID,
                        const String Label
                        );
  ~ToggleButtonComponent() override;
  
  
  void paint(juce::Graphics& g) override;
  void resized() override;
  void setSvgDrawable(std::unique_ptr<Drawable> svgDrawable);
  
  juce::Label label;
  //==============================================================================
  private:
  
  CustomToggleButton toggleButton;
  
  std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> attachment;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ToggleButtonComponent)
};
