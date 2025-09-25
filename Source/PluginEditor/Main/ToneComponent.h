#pragma once

#include <JuceHeader.h>
#include "../UI/KnobComponent.h"

// Forward declaration
class PluginEditor;

//==============================================================================
class ToneComponent : public juce::Component,
public juce::AudioProcessorParameter::Listener
{
  public:
  ToneComponent();
  ~ToneComponent() override;
  
  void init(PluginEditor& editor);
  
  void paint(juce::Graphics& g) override;
  void resized() override;
  
  void parameterValueChanged (int parameterIndex, float newValue) override;
  void parameterGestureChanged (int, bool) override {} //int parameterIndex, bool gestureIsStarting
  
  //==============================================================================
  private:
  PluginEditor* editorRef = nullptr; // 포인터로 저장하면 forward declaration 가능
  
  KnobComponent tiltKnob;
  KnobComponent midsideKnob;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ToneComponent)
};
