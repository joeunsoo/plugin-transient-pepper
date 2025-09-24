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
  addAndMakeVisible(noiseLevelGainKnob);

  wetSoloButton.init(editor, ID::wetSolo.getParamID(), "Wet Solo");
  addAndMakeVisible(wetSoloButton);
  
  dryWetKnob.init(editor, ID::dryWet.getParamID(), "Dry/Wet");
  addAndMakeVisible(dryWetKnob);
  
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
  auto meterArea = area.removeFromTop(area.getHeight()-(75+20+75));
  noiseLevelGainKnob.setBounds(area.removeFromTop(75));
  wetSoloButton.setBounds(area.removeFromTop(20));
  dryWetKnob.setBounds(area);
}
