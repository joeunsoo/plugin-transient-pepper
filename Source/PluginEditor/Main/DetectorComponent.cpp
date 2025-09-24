#include "DetectorComponent.h"
#include "../PluginEditor.h"

//==============================================================================
DetectorComponent::DetectorComponent() {
  
}

DetectorComponent::~DetectorComponent() = default;

void DetectorComponent::init(PluginEditor& editor)
{
  editorRef = &editor;
  
  addAndMakeVisible(sectionLabel);
  sectionLabel.setFont(editorRef->fontMedium.withHeight(12.0f));
  sectionLabel.setText("Transient Detector", juce::dontSendNotification);
  sectionLabel.setJustificationType(juce::Justification::centredLeft);
  
  
  channelLinkButton.init(editor, ID::linkChannels.getParamID(), "L/R Link");
  addAndMakeVisible(channelLinkButton);
  
  bpfPowerButton.init(editor, ID::bpfPower.getParamID(), "BPF");
  addAndMakeVisible(bpfPowerButton);
  
  sidechainListenButton.init(editor, ID::sidechainListen.getParamID(), "Listen");
  addAndMakeVisible(sidechainListenButton);
  
  thresholdKnob.init(editor, ID::threshold.getParamID(), "Threshold");
  thresholdKnob.setRingColor("secondary");
  addAndMakeVisible(thresholdKnob);
  
  bpfFreqKnob.init(editor, ID::bpfFrequency.getParamID(), "BPF Freq");
  addAndMakeVisible(bpfFreqKnob);
  
  editorRef->processorRef.parameters.bypass.addListener(this);
}

void DetectorComponent::parameterValueChanged (int, float) {
  bool bypass = editorRef->processorRef.parameters.bypass.get();
  if (bypass) {
    sectionLabel.setAlpha(DISABLED_ALPHA);
    channelLinkButton.setAlpha(DISABLED_ALPHA);
    bpfPowerButton.setAlpha(DISABLED_ALPHA);
    sidechainListenButton.setAlpha(DISABLED_ALPHA);
    thresholdKnob.setAlpha(DISABLED_ALPHA);
    bpfFreqKnob.setAlpha(DISABLED_ALPHA);
  } else {
    sectionLabel.setAlpha(1.0f);
    channelLinkButton.setAlpha(1.0f);
    bpfPowerButton.setAlpha(1.0f);
    sidechainListenButton.setAlpha(1.0f);
    thresholdKnob.setAlpha(1.0f);
    bpfFreqKnob.setAlpha(1.0f);
  }
}

void DetectorComponent::paint(juce::Graphics& g)
{
  g.fillAll(juce::Colours::transparentBlack);
}

void DetectorComponent::resized()
{
  auto area = getLocalBounds().reduced(0);
  sectionLabel.setBounds(area.removeFromTop(30));
  
  auto buttonArea = area.removeFromTop(20);
  channelLinkButton.setBounds(buttonArea.removeFromLeft(area.getWidth()/3));
  bpfPowerButton.setBounds(buttonArea.removeFromLeft(area.getWidth()/6));
  sidechainListenButton.setBounds(buttonArea.removeFromLeft(area.getWidth()/6));
  
  auto SliderArea = area.removeFromTop(75);
  thresholdKnob.setBounds(SliderArea.removeFromLeft(area.getWidth()/3));
  bpfFreqKnob.setBounds(SliderArea.removeFromLeft(area.getWidth()/3));
}
