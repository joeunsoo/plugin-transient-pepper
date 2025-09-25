#include "MixComponent.h"
#include "../PluginEditor.h"

//==============================================================================
MixComponent::MixComponent() {
  
}

MixComponent::~MixComponent() = default;

void MixComponent::init(PluginEditor& editor)
{
  editorRef = &editor;
  
  noisePeakMeter.init(editor, 2);
  addAndMakeVisible(noisePeakMeter);

  outputPeakMeter.init(editor, 0);
  addAndMakeVisible(outputPeakMeter);
  
  noiseLevelGainKnob.init(editor, ID::noiseLevelGain.getParamID(), "Noise Level");
  noiseLevelGainKnob.setRingColor("secondary");
  addAndMakeVisible(noiseLevelGainKnob);

  wetSoloButton.init(editor, ID::wetSolo.getParamID(), "Wet Solo");
  addAndMakeVisible(wetSoloButton);
  
  dryWetKnob.init(editor, ID::dryWet.getParamID(), "Dry/Wet");
  addAndMakeVisible(dryWetKnob);
  
  outputGainKnob.init(editor, ID::outputGain.getParamID(), "Output");
  addAndMakeVisible(outputGainKnob);

  editorRef->processorRef.parameters.bypass.addListener(this);
  editorRef->processorRef.parameters.wetSolo.addListener(this);
  editorRef->processorRef.parameters.sidechainListen.addListener(this);
  parameterValueChanged(0, 0);
}

void MixComponent::parameterValueChanged (int, float) {
  bool bypass = editorRef->processorRef.parameters.bypass.get();
  bool sidechainListen = editorRef->processorRef.parameters.sidechainListen.get();
  bool wetSolo = editorRef->processorRef.parameters.wetSolo.get();

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
  auto area = getLocalBounds().reduced(0);
  auto leftArea = area.removeFromLeft(area.getWidth() / 2);
  noisePeakMeter.setBounds(leftArea.removeFromTop(leftArea.getHeight()-(UI_KNOB_HEIGHT+UI_BUTTON_HEIGHT+UI_KNOB_HEIGHT)));
  noiseLevelGainKnob.setBounds(leftArea.removeFromTop(UI_KNOB_HEIGHT));
  wetSoloButton.setBounds(leftArea.removeFromTop(UI_BUTTON_HEIGHT).reduced(UI_GAP_SIZE));
  dryWetKnob.setBounds(leftArea);
  auto rightArea = area;
  outputPeakMeter.setBounds(rightArea.removeFromTop(rightArea.getHeight()-(UI_KNOB_HEIGHT)));
  outputGainKnob.setBounds(rightArea);
}
