#include "MixComponent.h"
#include "../PluginEditor.h"

//==============================================================================
MixComponent::MixComponent(PluginEditor& editor)
:editorRef(editor),
wetSoloButton(editor, ID::wetSolo.getParamID(), "Wet Solo"),
noiseLevelGainKnob(editor, ID::noiseLevelGain.getParamID(), "Noise Gain"),
dryWetKnob(editor, ID::dryWet.getParamID(), "Dry/Wet"),
outputGainKnob(editor, ID::outputGain.getParamID(), "Output Gain"),
noisePeakMeter(editor, 2),
outputPeakMeter(editor, 0)
{
  addAndMakeVisible(noisePeakMeter);

  addAndMakeVisible(outputPeakMeter);
  
  noiseLevelGainKnob.setRingColor("secondary");
  addAndMakeVisible(noiseLevelGainKnob);
  
  addAndMakeVisible(wetSoloButton);
  
  addAndMakeVisible(dryWetKnob);
  
  addAndMakeVisible(outputGainKnob);
  
  editorRef.processorRef.parameters.bypass.addListener(this);
  editorRef.processorRef.parameters.wetSolo.addListener(this);
  editorRef.processorRef.parameters.sidechainListen.addListener(this);
  parameterValueChanged(0, 0);
}

MixComponent::~MixComponent() = default;

void MixComponent::parameterValueChanged (int, float) {
  bool bypass = editorRef.processorRef.parameters.bypass.get();
  bool sidechainListen = editorRef.processorRef.parameters.sidechainListen.get();
  bool wetSolo = editorRef.processorRef.parameters.wetSolo.get();
  
  if (bypass) {
    noiseLevelGainKnob.setAlpha(DISABLED_ALPHA);
    outputGainKnob.setAlpha(DISABLED_ALPHA);
  } else {
    noiseLevelGainKnob.setAlpha(1.0f);
    outputGainKnob.setAlpha(1.0f);
  }
  
  if (bypass || sidechainListen) {
    wetSoloButton.setAlpha(DISABLED_ALPHA);
  } else {
    wetSoloButton.setAlpha(1.0f);
  }
  
  if (bypass || wetSolo || sidechainListen) {
    dryWetKnob.setAlpha(DISABLED_ALPHA);
  } else {
    dryWetKnob.setAlpha(1.0f);
  }
}

void MixComponent::paint(juce::Graphics& g)
{
  g.fillAll(juce::Colours::transparentBlack);
}

void MixComponent::resized()
{
  int NoiseGainGap = 11;
  auto area = getLocalBounds().withTrimmedBottom(21);
  auto leftArea = area.removeFromLeft(area.getWidth() / 2);
  noisePeakMeter.setBounds(leftArea.removeFromTop(leftArea.getHeight()-(UI_KNOB_HEIGHT+NoiseGainGap+UI_BUTTON_HEIGHT+UI_KNOB_HEIGHT)));
  noiseLevelGainKnob.setBounds(leftArea.removeFromTop(UI_KNOB_HEIGHT));
  leftArea.removeFromTop(NoiseGainGap);
  wetSoloButton.setBounds(leftArea.removeFromTop(UI_BUTTON_HEIGHT).reduced(2,0));
  dryWetKnob.setBounds(leftArea);
  auto rightArea = area;
  outputPeakMeter.setBounds(rightArea.removeFromTop(rightArea.getHeight()-(UI_KNOB_HEIGHT)).withTrimmedBottom(0));
  outputGainKnob.setBounds(rightArea);
}
