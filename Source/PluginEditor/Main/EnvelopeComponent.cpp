#include "EnvelopeComponent.h"
#include "../../NamespaceParameterId.h"

//==============================================================================
EnvelopeComponent::EnvelopeComponent(Providers& pv)
: scaleProvider(pv.scale), processorProvider(pv.processor),
attackKnob (pv.editor, pv.scale, pv.processor, ID::attack.getParamID(), "Attack" ),
releaseKnob (pv.editor, pv.scale, pv.processor, ID::release.getParamID(), "Release")
{
  addAndMakeVisible(sectionLabel);
  sectionLabel.setText("Noise Shape", juce::dontSendNotification);
  sectionLabel.setJustificationType(juce::Justification::centredLeft);
  
  attackKnob.setColor("secondary");
  addAndMakeVisible(attackKnob);
  
  releaseKnob.setColor("secondary");
  addAndMakeVisible(releaseKnob);

  processorProvider.state().addParameterListener(ID::bypass.getParamID(), this);
  processorProvider.state().addParameterListener(ID::sidechainListen.getParamID(), this);
  parameterChanged("", 0);
}

EnvelopeComponent::~EnvelopeComponent()
{
  processorProvider.state().removeParameterListener(ID::bypass.getParamID(), this);
  processorProvider.state().removeParameterListener(ID::sidechainListen.getParamID(), this);
};

void EnvelopeComponent::parameterChanged (const juce::String&, float) {
  bool bypass = (processorProvider.state().getRawParameterValue(ID::bypass.getParamID())->load() >= 0.5f);
  bool sidechainListen = (processorProvider.state().getRawParameterValue(ID::sidechainListen.getParamID())->load() >= 0.5f);

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
  auto scale = scaleProvider.getScale();
  sectionLabel.setFont(FONT_PRETENDARD_MEDIUM.withHeight(UI_SECTION_LABEL_FONT_HEIGHT * scale));

  auto area = getLocalBounds().withTrimmedBottom(int(10 * scale));
  auto labelArea = area.removeFromTop(int(UI_SECTION_LABEL_HEIGHT * scale));
  sectionLabel.setBounds(labelArea);
  
  auto SliderArea = area;
  attackKnob.setBounds(SliderArea.removeFromLeft(area.getWidth()/2));
  releaseKnob.setBounds(SliderArea.removeFromLeft(area.getWidth()/2));
}
