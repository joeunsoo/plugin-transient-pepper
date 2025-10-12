#include "MixComponent.h"
#include "../../NamespaceParameterId.h"

//==============================================================================
MixComponent::MixComponent(Providers& pv)
: scaleProvider(pv.scale), processorProvider(pv.processor),
wetSoloButton(pv.scale, pv.processor, ID::wetSolo.getParamID(), "Wet Solo"),
noiseLevelGainKnob(pv.editor, pv.scale, pv.processor, ID::noiseLevelGain.getParamID(), "Noise Gain"),
dryWetKnob(pv.editor, pv.scale, pv.processor, ID::dryWet.getParamID(), "Dry/Wet"),
outputGainKnob(pv.editor, pv.scale, pv.processor, ID::outputGain.getParamID(), "Output Gain"),
noisePeakMeter(pv.processor, 2, true),
outputPeakMeter(pv.processor, 0, true)
{
  addAndMakeVisible(noisePeakMeter);

  addAndMakeVisible(outputPeakMeter);
  
  noiseLevelGainKnob.setRingColor("secondary");
  addAndMakeVisible(noiseLevelGainKnob);
  
  addAndMakeVisible(wetSoloButton);
  
  addAndMakeVisible(dryWetKnob);
  
  addAndMakeVisible(outputGainKnob);
  
  processorProvider.state().addParameterListener(ID::bypass.getParamID(), this);
  processorProvider.state().addParameterListener(ID::wetSolo.getParamID(), this);
  processorProvider.state().addParameterListener(ID::sidechainListen.getParamID(), this);
  parameterChanged("", 0);
}

MixComponent::~MixComponent()
{
  processorProvider.state().removeParameterListener(ID::bypass.getParamID(), this);
  processorProvider.state().removeParameterListener(ID::wetSolo.getParamID(), this);
  processorProvider.state().removeParameterListener(ID::sidechainListen.getParamID(), this);
};

void MixComponent::parameterChanged (const juce::String&, float) {
  bool bypass = (processorProvider.state().getRawParameterValue(ID::bypass.getParamID())->load() >= 0.5f);
  bool sidechainListen = (processorProvider.state().getRawParameterValue(ID::sidechainListen.getParamID())->load() >= 0.5f);
  bool wetSolo = (processorProvider.state().getRawParameterValue(ID::wetSolo.getParamID())->load() >= 0.5f);
  
  if (bypass) {
    outputGainKnob.setAlpha(DISABLED_ALPHA);
  } else {
    outputGainKnob.setAlpha(1.0f);
  }
  
  if (bypass || sidechainListen) {
    noiseLevelGainKnob.setAlpha(DISABLED_ALPHA);
    wetSoloButton.setAlpha(DISABLED_ALPHA);
  } else {
    noiseLevelGainKnob.setAlpha(1.0f);
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
  auto scale = scaleProvider.getScale();

  int NoiseGainGap = 11;
  auto area = getLocalBounds().withTrimmedBottom(int(21 * scale));
  auto leftArea = area.removeFromLeft(area.getWidth() / 2);
  noisePeakMeter.setBounds(leftArea.removeFromTop(leftArea.getHeight() - int((UI_KNOB_HEIGHT+NoiseGainGap+UI_BUTTON_HEIGHT+UI_KNOB_HEIGHT) * scale)));
  noiseLevelGainKnob.setBounds(leftArea.removeFromTop(int(UI_KNOB_HEIGHT * scale)));
  leftArea.removeFromTop(int(NoiseGainGap * scale));
  wetSoloButton.setBounds(leftArea.removeFromTop(int(UI_BUTTON_HEIGHT * scale)).reduced(int(2 * scale),0));
  dryWetKnob.setBounds(leftArea);

  auto rightArea = area;
  outputPeakMeter.setBounds(rightArea.removeFromTop(rightArea.getHeight()-(int(UI_KNOB_HEIGHT * scale))));
  outputGainKnob.setBounds(rightArea);
}
