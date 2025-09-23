#pragma once
#include "../AudioProcessor/PluginAudioProcessor.h"
#include "LookAndFeelDemo.h"

class PluginEditor : public juce::AudioProcessorEditor
{
  public:
  PluginEditor(PluginAudioProcessor& p);
  ~PluginEditor() override;
  
  void paint(juce::Graphics& g) override;
  void resized() override;
  
  void setScale(int scale);

  private:
  PluginAudioProcessor& processorRef;
  
  Slider rotarySlider    { Slider::RotaryHorizontalVerticalDrag, Slider::NoTextBox};

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};
