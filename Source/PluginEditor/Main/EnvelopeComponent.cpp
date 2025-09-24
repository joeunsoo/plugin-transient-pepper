#include "EnvelopeComponent.h"
#include "../PluginEditor.h"

//==============================================================================
EnvelopeComponent::EnvelopeComponent() {
  
}

void EnvelopeComponent::init(PluginEditor& editor)
{
  editorRef = &editor;

  addAndMakeVisible(sectionLabel);
  sectionLabel.setFont(editorRef->fontMedium.withHeight(12.0f));
  sectionLabel.setText("Noise Shape", juce::dontSendNotification);
  sectionLabel.setJustificationType(juce::Justification::centredLeft);
  
  attackKnob.init(editor, ID::attack.getParamID(), "Attack");
  attackKnob.setColor("secondary");
  addAndMakeVisible(attackKnob);
  
  releaseKnob.init(editor, ID::release.getParamID(), "Release");
  releaseKnob.setColor("secondary");
  addAndMakeVisible(releaseKnob);
  
}

EnvelopeComponent::~EnvelopeComponent() = default;

void EnvelopeComponent::paint(juce::Graphics& g)
{
  g.fillAll(juce::Colours::transparentBlack);
}

void EnvelopeComponent::resized()
{
  auto area = getLocalBounds().reduced(0);
  auto labelArea = area.removeFromTop(15);
  sectionLabel.setBounds(labelArea.reduced(0));
  
  auto SliderArea = area;
  attackKnob.setBounds(SliderArea.removeFromLeft(area.getWidth()/2));
  releaseKnob.setBounds(SliderArea.removeFromLeft(area.getWidth()/2));
}
