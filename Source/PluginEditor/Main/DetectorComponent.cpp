#include "DetectorComponent.h"
#include "../PluginEditor.h"

//==============================================================================
DetectorComponent::DetectorComponent() {
  
}

void DetectorComponent::init(PluginEditor& editor)
{
  editorRef = &editor;
  const Font fontSemoBold { FontOptions { editorRef->pretendardSemiBoldTypeface } };
  
  addAndMakeVisible(sectionLabel);
  sectionLabel.setFont(fontSemoBold);
  sectionLabel.setText("Transient Pepper", juce::dontSendNotification);
  sectionLabel.setJustificationType(juce::Justification::centredLeft);
  
  thresholdKnob.init(editor, ID::threshold.getParamID(), "Threshold");
  thresholdKnob.setColor("secondary");
  addAndMakeVisible(thresholdKnob);
  
  bpfFreqKnob.init(editor, ID::bpfFrequency.getParamID(), "BPF Freq");
  thresholdKnob.setRingColor("secondary");
  addAndMakeVisible(bpfFreqKnob);
  
  channelLinkButton.init(editor, ID::linkChannels.getParamID(), "L/R Link");
  addAndMakeVisible(channelLinkButton);
  bpfPowerButton.init(editor, ID::bpfPower.getParamID(), "BPF");
  addAndMakeVisible(bpfPowerButton);
  sidechainListenButton.init(editor, ID::sidechainListen.getParamID(), "Listen");
  addAndMakeVisible(sidechainListenButton);
}

DetectorComponent::~DetectorComponent() = default;

void DetectorComponent::paint(juce::Graphics& g)
{
  g.fillAll(juce::Colours::transparentBlack);
}

void DetectorComponent::resized()
{
  auto area = getLocalBounds().reduced(0);

  sectionLabel.setBounds(area.removeFromTop(30));
  
  auto buttonArea = area.removeFromTop(30);
  channelLinkButton.setBounds(buttonArea.removeFromLeft(area.getWidth()/3));
  bpfPowerButton.setBounds(buttonArea.removeFromLeft(area.getWidth()/6));
  sidechainListenButton.setBounds(buttonArea.removeFromLeft(area.getWidth()/6));
  auto SliderArea = area;
  
  thresholdKnob.setBounds(SliderArea.removeFromLeft(area.getWidth()/3));
  bpfFreqKnob.setBounds(SliderArea.removeFromLeft(area.getWidth()/3));

}
