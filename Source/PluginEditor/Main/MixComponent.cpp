#include "MixComponent.h"
#include "../PluginEditor.h"

//==============================================================================
MixComponent::MixComponent() {
  
}

MixComponent::~MixComponent() = default;

void MixComponent::init(PluginEditor& editor)
{
  editorRef = &editor;
  
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
}

void MixComponent::parameterValueChanged (int, float) {
  bool bypass = editorRef->processorRef.parameters.bypass.get();
  if (bypass) {
    noiseLevelGainKnob.setAlpha(DISABLED_ALPHA);
    wetSoloButton.setAlpha(DISABLED_ALPHA);
    dryWetKnob.setAlpha(DISABLED_ALPHA);
  } else {
    noiseLevelGainKnob.setAlpha(1.0f);
    wetSoloButton.setAlpha(1.0f);
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
  leftArea.removeFromTop(leftArea.getHeight()-(UI_KNOB_HEIGHT+20+UI_KNOB_HEIGHT));
  noiseLevelGainKnob.setBounds(leftArea.removeFromTop(UI_KNOB_HEIGHT));
  wetSoloButton.setBounds(leftArea.removeFromTop(UI_BUTTON_HEIGHT).reduced(UI_GAP_SIZE));
  dryWetKnob.setBounds(leftArea);
  auto rightArea = area;
  rightArea.removeFromTop(rightArea.getHeight()-(UI_KNOB_HEIGHT));
  outputGainKnob.setBounds(rightArea);
}
