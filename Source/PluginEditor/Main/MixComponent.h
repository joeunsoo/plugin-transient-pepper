#pragma once

#include <JuceHeader.h>
#include "../UI/KnobComponent.h"
#include "../UI/ToggleButtonComponent.h"
#include "../UI/PeakMeterStereoComponent.h"

// Forward declaration
class PluginEditor;

//==============================================================================
class MixComponent : public juce::Component,
public juce::AudioProcessorParameter::Listener
{
  public:
  MixComponent();
  ~MixComponent() override;
  
  void init(PluginEditor& editor);
  
  void paint(juce::Graphics& g) override;
  void resized() override;
  
  void parameterValueChanged (int parameterIndex, float newValue) override;
  void parameterGestureChanged (int, bool) override {} //int parameterIndex, bool gestureIsStarting
  
  //==============================================================================
  private:
  PluginEditor* editorRef = nullptr; // 포인터로 저장하면 forward declaration 가능
  
  ToggleButtonComponent wetSoloButton;
  KnobComponent noiseLevelGainKnob;
  KnobComponent dryWetKnob;
  KnobComponent outputGainKnob;
  PeakMeterStereoComponent noisePeakMeter;
  PeakMeterStereoComponent outputPeakMeter;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MixComponent)
};
