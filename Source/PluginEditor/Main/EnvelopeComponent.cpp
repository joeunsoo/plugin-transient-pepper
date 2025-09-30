#include "EnvelopeComponent.h"
#include "../PluginEditor.h"

//==============================================================================
EnvelopeComponent::EnvelopeComponent(PluginEditor& editor)
: editorRef(editor),
attackKnob (editor, ID::attack.getParamID(), "Attack" ),
releaseKnob (editor, ID::release.getParamID(), "Release")
{
  addAndMakeVisible(sectionLabel);
  sectionLabel.setFont(editorRef.fontPretendardMedium.withHeight(UI_SECTION_LABEL_FONT_HEIGHT));
  sectionLabel.setText("Noise Shape", juce::dontSendNotification);
  sectionLabel.setJustificationType(juce::Justification::centredLeft);
  
  attackKnob.setColor("secondary");
  addAndMakeVisible(attackKnob);
  
  releaseKnob.setColor("secondary");
  addAndMakeVisible(releaseKnob);
  
  editorRef.processorRef.parameters.bypass.addListener(this);
  editorRef.processorRef.parameters.sidechainListen.addListener(this);
  parameterValueChanged(0, 0);
}

EnvelopeComponent::~EnvelopeComponent()
{
  editorRef.processorRef.parameters.bypass.removeListener(this);
  editorRef.processorRef.parameters.sidechainListen.removeListener(this);
};

void EnvelopeComponent::parameterValueChanged (int, float) {
  bool bypass = editorRef.processorRef.parameters.bypass.get();
  bool sidechainListen = editorRef.processorRef.parameters.sidechainListen.get();

  if (bypass || sidechainListen) {
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
  auto area = getLocalBounds().withTrimmedBottom(10);
  auto labelArea = area.removeFromTop(UI_SECTION_LABEL_HEIGHT);
  sectionLabel.setBounds(labelArea.reduced(0));
  
  auto SliderArea = area;
  attackKnob.setBounds(SliderArea.removeFromLeft(area.getWidth()/2));
  releaseKnob.setBounds(SliderArea.removeFromLeft(area.getWidth()/2));
}
