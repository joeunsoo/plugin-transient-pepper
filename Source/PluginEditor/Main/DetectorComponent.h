#pragma once

#include <JuceHeader.h>

// Forward declaration
class PluginEditor;

//==============================================================================
class DetectorComponent : public juce::Component
{
  public:
  DetectorComponent();
  ~DetectorComponent() override;
  
  void setEditorRef(PluginEditor& editor);
  
  void paint(juce::Graphics& g) override;
  void resized() override;
  
  //==============================================================================
  private:
  PluginEditor* editorRef = nullptr; // 포인터로 저장하면 forward declaration 가능

  juce::Label sectionLabel;
  juce::Label thresholdLabel;
  Slider thresholdRotarySlider    { Slider::RotaryHorizontalVerticalDrag, Slider::NoTextBox};
  Slider bpfFrequencyRotarySlider    { Slider::RotaryHorizontalVerticalDrag, Slider::NoTextBox};

  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> thresholdAttachment;
  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> bpfFrequencyAttachment;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DetectorComponent)
};
