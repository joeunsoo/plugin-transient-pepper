#include "DetectorComponent.h"
#include "../PluginEditor.h"

//==============================================================================
DetectorComponent::DetectorComponent(PluginEditor& editor)
: editorRef(editor), isStereo(editor.processorRef.getTotalNumOutputChannels() > 1),
thresholdKnob(editor, ID::threshold.getParamID(), "Threshold"),
bpfFreqKnob(editor, ID::bpfFrequency.getParamID(), "BPF Freq"),
channelLinkButton(editor,ID::linkChannels.getParamID(), isStereo ? "L/R Link": "Mono"),
bpfPowerButton(editor, ID::bpfPower.getParamID(), "BPF"),
sidechainListenButton(editor, ID::sidechainListen.getParamID(), "Listen")
{

  addAndMakeVisible(sectionLabel);
  sectionLabel.setFont(editorRef.fontMedium.withHeight(UI_SECTION_LABEL_FONT_HEIGHT));
  sectionLabel.setText("Transient Detector", juce::dontSendNotification);
  sectionLabel.setJustificationType(juce::Justification::centredLeft);
  addAndMakeVisible(channelLinkButton);
  
  addAndMakeVisible(bpfPowerButton);
  
  sidechainListenButton.setSvgDrawable( juce::Drawable::createFromImageData(BinaryData::headphonesbold_svg, BinaryData::headphonesbold_svgSize));
  addAndMakeVisible(sidechainListenButton);
  
  thresholdKnob.setRingColor("secondary");
  addAndMakeVisible(thresholdKnob);

  addAndMakeVisible(bpfFreqKnob);
  
  editorRef.processorRef.parameters.bypass.addListener(this);
  editorRef.processorRef.parameters.bpfPower.addListener(this);
  editorRef.processorRef.parameters.sidechainListen.addListener(this);
  parameterValueChanged(0, 0);
}

DetectorComponent::~DetectorComponent()
{
  editorRef.processorRef.parameters.bypass.removeListener(this);
  editorRef.processorRef.parameters.bpfPower.removeListener(this);
  editorRef.processorRef.parameters.sidechainListen.removeListener(this);
};

void DetectorComponent::parameterValueChanged (int, float) {
  bool bypass = editorRef.processorRef.parameters.bypass.get();
  bool bpfPower = editorRef.processorRef.parameters.bpfPower.get();
  bool sidechainListen = editorRef.processorRef.parameters.sidechainListen.get();

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
  auto area = getLocalBounds().reduced(0);
  sectionLabel.setBounds(area.removeFromTop(UI_SECTION_LABEL_HEIGHT));
  
  auto buttonArea = area.removeFromTop(UI_BUTTON_HEIGHT);
  channelLinkButton.setBounds(buttonArea.removeFromLeft(area.getWidth()/3));
  bpfPowerButton.setBounds(buttonArea.removeFromLeft(area.getWidth()/6));
  sidechainListenButton.setBounds(buttonArea.removeFromLeft(area.getWidth()/6));
  
  auto SliderArea = area.removeFromTop(UI_KNOB_HEIGHT);
  thresholdKnob.setBounds(SliderArea.removeFromLeft(area.getWidth()/3));
  bpfFreqKnob.setBounds(SliderArea.removeFromLeft(area.getWidth()/3));
}
