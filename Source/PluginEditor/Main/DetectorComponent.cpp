#include "DetectorComponent.h"
#include "../PluginEditor.h"

//==============================================================================
DetectorComponent::DetectorComponent() {
  
}

void DetectorComponent::setEditorRef(PluginEditor& editor)
{
  editorRef = &editor;
  const Font fontBold { FontOptions { editorRef->pretendardBoldTypeface } };
  
  addAndMakeVisible(sectionLabel);
  sectionLabel.setFont(fontBold);
  sectionLabel.setText("Transient Pepper", juce::dontSendNotification);
  sectionLabel.setJustificationType(juce::Justification::centredLeft);
  
  addAndMakeVisible (thresholdRotarySlider);
  thresholdAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
  (
   editorRef->processorRef.state,
   ID::threshold.getParamID(),
   thresholdRotarySlider
   );
  
  thresholdLabel.setText("Threshold", juce::dontSendNotification);
  thresholdLabel.setJustificationType(juce::Justification::centred);

  addAndMakeVisible(thresholdLabel);

  addAndMakeVisible (bpfFrequencyRotarySlider);
  bpfFrequencyAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
  (
   editorRef->processorRef.state,
   ID::bpfFrequency.getParamID(),
   bpfFrequencyRotarySlider
   );
}

DetectorComponent::~DetectorComponent() = default;

void DetectorComponent::paint(juce::Graphics& g)
{
  g.fillAll(juce::Colours::transparentBlack);
}

void DetectorComponent::resized()
{
  auto area = getLocalBounds().reduced(0);
  sectionLabel.setBounds (0, 0, 100, 30);
  
  thresholdRotarySlider.setBounds(0, 30, 200, 200);
  thresholdLabel.setBounds(0, 230, 200, 20);
  
  bpfFrequencyRotarySlider.setBounds(200, 30, 100, 100);
}
