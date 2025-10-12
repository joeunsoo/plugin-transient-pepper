#pragma once

#include <JuceHeader.h>
#include "KnobSlider.h"
#include "../../Provider/EditorProvider.h"
#include "../../Provider/ProcessorProvider.h"
#include "../../Provider/ScaleProvider.h"

//==============================================================================
class KnobComponent : public juce::Component
{
  public:
  KnobComponent(EditorProvider& ep,
                const ScaleProvider& sp,
                ProcessorProvider& pp,
                const String& parameterID,
                const String labelText
                );
  ~KnobComponent() override;
  
  void paint(juce::Graphics& g) override;
  void resized() override;
  
  void sendTooltip();

  void setColor(const String color);
  void setRingColor(const String color);

  void mouseEnter(const juce::MouseEvent& event) override;
  void mouseExit(const juce::MouseEvent& event) override;

  void setKnobDisabled(bool value);

  //==============================================================================
  private:
  EditorProvider& editorProvider;
  const ScaleProvider& scaleProvider;
  ProcessorProvider& processorProvider;
  
  bool isDrag = false;

  KnobSlider rotarySlider;
  juce::Label label;
  String parameterID;
  
  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KnobComponent)
};
