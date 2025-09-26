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
  DetectorComponent(PluginEditor& editor);
  ~DetectorComponent() override;
  
  void paint(juce::Graphics& g) override;
  void resized() override;
  
  void parameterValueChanged (int parameterIndex, float newValue) override;
  void parameterGestureChanged (int, bool) override {} //int parameterIndex, bool gestureIsStarting
  
  //==============================================================================
  private:
  PluginEditor& editorRef; // 포인터로 저장하면 forward declaration 가능
  
  bool isStereo = false;
  juce::Label sectionLabel;
  KnobComponent thresholdKnob, bpfFreqKnob;
  
  ToggleButtonComponent channelLinkButton, bpfPowerButton, sidechainListenButton;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DetectorComponent)
};
