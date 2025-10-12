#include "DetectorComponent.h"
#include "../../NamespaceParameterId.h"

//==============================================================================
DetectorComponent::DetectorComponent(Providers& pv)
: scaleProvider(pv.scale), processorProvider(pv.processor),
thresholdKnob(pv.editor, pv.scale, pv.processor, ID::threshold.getParamID(), "Threshold"),
bpfFreqKnob(pv.editor, pv.scale, pv.processor, ID::bpfFrequency.getParamID(), "BPF Freq"),
channelLinkButton(pv.scale, pv.processor,ID::linkChannels.getParamID(), isStereo ? "L/R Link": "Mono"),
bpfPowerButton(pv.scale, pv.processor, ID::bpfPower.getParamID(), "BPF"),
sidechainListenButton( pv.scale, pv.processor, ID::sidechainListen.getParamID(), "Listen")
{
  isStereo = pv.processor.getTotalNumOutputChannels() > 1;

  channelLinkButton.setButtonText(isStereo ? "L/R Link": "Mono");

  addAndMakeVisible(sectionLabel);
  sectionLabel.setText("Transient Detector", juce::dontSendNotification);
  sectionLabel.setJustificationType(juce::Justification::centredLeft);
  addAndMakeVisible(channelLinkButton);
  
  addAndMakeVisible(bpfPowerButton);
  
  sidechainListenButton.setSvgDrawable( juce::Drawable::createFromImageData(BinaryData::headphonesbold_svg, BinaryData::headphonesbold_svgSize));
  addAndMakeVisible(sidechainListenButton);
  
  thresholdKnob.setRingColor("secondary");
  addAndMakeVisible(thresholdKnob);

  addAndMakeVisible(bpfFreqKnob);
  
  processorProvider.state().addParameterListener(ID::bypass.getParamID(), this);
  processorProvider.state().addParameterListener(ID::bpfPower.getParamID(), this);
  processorProvider.state().addParameterListener(ID::sidechainListen.getParamID(), this);
  parameterChanged("", 0);
}

DetectorComponent::~DetectorComponent()
{
  processorProvider.state().removeParameterListener(ID::bypass.getParamID(), this);
  processorProvider.state().removeParameterListener(ID::bpfPower.getParamID(), this);
  processorProvider.state().removeParameterListener(ID::sidechainListen.getParamID(), this);
};

void DetectorComponent::parameterChanged (const juce::String&, float) {
  bool bypass = (processorProvider.state().getRawParameterValue(ID::bypass.getParamID())->load() >= 0.5f);
  bool bpfPower = (processorProvider.state().getRawParameterValue(ID::bpfPower.getParamID())->load() >= 0.5f);
  bool sidechainListen = (processorProvider.state().getRawParameterValue(ID::sidechainListen.getParamID())->load() >= 0.5f);
  
  if (bypass) {
    sectionLabel.setAlpha(DISABLED_ALPHA);
    bpfPowerButton.setAlpha(DISABLED_ALPHA);
    sidechainListenButton.setAlpha(DISABLED_ALPHA);
    thresholdKnob.setAlpha(DISABLED_ALPHA);
    bpfFreqKnob.setAlpha(DISABLED_ALPHA);
  } else {
    sectionLabel.setAlpha(1.0f);
    
    bpfPowerButton.setAlpha(1.0f);
    sidechainListenButton.setAlpha(1.0f);
    thresholdKnob.setAlpha(1.0f);
  }

  if (bypass || !isStereo) {
    channelLinkButton.setAlpha(DISABLED_ALPHA);
  } else {
    channelLinkButton.setAlpha(1.0f);
  }

  if (bypass || (!bpfPower && !sidechainListen)) {
    bpfFreqKnob.setAlpha(DISABLED_ALPHA);
  } else {
    bpfFreqKnob.setAlpha(1.0f);
  }
}

void DetectorComponent::paint(juce::Graphics& g)
{
  g.fillAll(juce::Colours::transparentBlack);
}

void DetectorComponent::resized()
{
  auto scale = scaleProvider.getScale();
  sectionLabel.setFont(FONT_PRETENDARD_MEDIUM.withHeight(UI_SECTION_LABEL_FONT_HEIGHT * scale));

  auto area = getLocalBounds().reduced(0);
  sectionLabel.setBounds(area.removeFromTop(int(UI_SECTION_LABEL_HEIGHT * scale)));
  
  auto buttonArea = area.removeFromTop(int(UI_SECTION_LABEL_HEIGHT * scale));
  channelLinkButton.setBounds(buttonArea.removeFromLeft(area.getWidth()/3));
  bpfPowerButton.setBounds(buttonArea.removeFromLeft(area.getWidth()/6));
  sidechainListenButton.setBounds(buttonArea.removeFromLeft(area.getWidth()/6));
  
  auto SliderArea = area.removeFromTop(int(UI_KNOB_HEIGHT * scale));
  thresholdKnob.setBounds(SliderArea.removeFromLeft(area.getWidth()/3));
  bpfFreqKnob.setBounds(SliderArea.removeFromLeft(area.getWidth()/3));
}
