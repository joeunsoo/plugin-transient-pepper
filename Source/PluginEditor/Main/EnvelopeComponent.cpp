#include "EnvelopeComponent.h"
#include "../PluginEditor.h"

//==============================================================================
EnvelopeComponent::EnvelopeComponent() {
  
}

EnvelopeComponent::~EnvelopeComponent() = default;

void EnvelopeComponent::init(PluginEditor& editor)
{
  editorRef = &editor;

  addAndMakeVisible(sectionLabel);
  sectionLabel.setFont(editorRef->fontMedium.withHeight(UI_SECTION_LABEL_FONT_HEIGHT));
  sectionLabel.setText("Noise Shape", juce::dontSendNotification);
  sectionLabel.setJustificationType(juce::Justification::centredLeft);
  
  attackKnob.init(editor, ID::attack.getParamID(), "Attack");
  attackKnob.setColor("secondary");
  addAndMakeVisible(attackKnob);
  
  releaseKnob.init(editor, ID::release.getParamID(), "Release");
  releaseKnob.setColor("secondary");
  addAndMakeVisible(releaseKnob);
  
  editorRef->processorRef.parameters.bypass.addListener(this);
}

void EnvelopeComponent::parameterValueChanged (int, float) {
  bool bypass = editorRef->processorRef.parameters.bypass.get();
  if (bypass) {
    sectionLabel.setAlpha(DISABLED_ALPHA);
    attackKnob.setAlpha(DISABLED_ALPHA);
    releaseKnob.setAlpha(DISABLED_ALPHA);
  } else {
    sectionLabel.setAlpha(1.0f);
    attackKnob.setAlpha(1.0f);
    releaseKnob.setAlpha(1.0f);
  }
}

void EnvelopeComponent::paint(juce::Graphics& g)
{
  g.fillAll(juce::Colours::transparentBlack);
}

void EnvelopeComponent::resized()
{
  auto area = getLocalBounds().reduced(0);
  auto labelArea = area.removeFromTop(UI_SECTION_LABEL_HEIGHT);
  sectionLabel.setBounds(labelArea.reduced(0));
  
  auto SliderArea = area;
  attackKnob.setBounds(SliderArea.removeFromLeft(area.getWidth()/2));
  releaseKnob.setBounds(SliderArea.removeFromLeft(area.getWidth()/2));
}
