#pragma once

#include <JuceHeader.h>
#include "../UI/KnobComponent.h"
#include "../UI/ToggleButtonComponent.h"

// Forward declaration
class PluginEditor;

//==============================================================================
class DetectorComponent : public juce::Component,
public juce::AudioProcessorParameter::Listener
{
  public:
  DetectorComponent();
  ~DetectorComponent() override;
  
  void init(PluginEditor& editor);
  
  void paint(juce::Graphics& g) override;
  void resized() override;
  
  void parameterValueChanged (int parameterIndex, float newValue) override;
  void parameterGestureChanged (int, bool) override {} //int parameterIndex, bool gestureIsStarting
  
  //==============================================================================
  private:
  PluginEditor* editorRef = nullptr; // 포인터로 저장하면 forward declaration 가능

  
  juce::Label sectionLabel;
  KnobComponent thresholdKnob;
  KnobComponent bpfFreqKnob;
  
  ToggleButtonComponent channelLinkButton;
  ToggleButtonComponent bpfPowerButton;
  ToggleButtonComponent sidechainListenButton;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DetectorComponent)
};
