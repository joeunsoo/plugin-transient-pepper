#pragma once
#include "../AudioProcessor/PluginAudioProcessor.h"
#include "LookAndFeelDemo.h"
#include "Header/HeaderComponent.h"

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
  
  HeaderComponent headerComponent;

  Slider rotarySlider    { Slider::RotaryHorizontalVerticalDrag, Slider::NoTextBox};

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};
