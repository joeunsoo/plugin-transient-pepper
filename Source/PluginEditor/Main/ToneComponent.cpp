#include "ToneComponent.h"
#include "../PluginEditor.h"

//==============================================================================
ToneComponent::ToneComponent() {
  
}

ToneComponent::~ToneComponent() = default;

void ToneComponent::init(PluginEditor& editor)
{
  editorRef = &editor;
  
  tiltKnob.init(editor, ID::tilt.getParamID(), "Tone");
  addAndMakeVisible(tiltKnob);
  
  midsideKnob.init(editor, ID::midSide.getParamID(), "Mid/Side");
  addAndMakeVisible(midsideKnob);
  
  editorRef->processorRef.parameters.bypass.addListener(this);
  parameterValueChanged(0, 0);
}

void ToneComponent::parameterValueChanged (int, float) {
  bool bypass = editorRef->processorRef.parameters.bypass.get();
  if (bypass) {
    tiltKnob.setAlpha(DISABLED_ALPHA);
    midsideKnob.setAlpha(DISABLED_ALPHA);
  } else {
    tiltKnob.setAlpha(1.0f);
    midsideKnob.setAlpha(1.0f);
  }
}

void ToneComponent::paint(juce::Graphics& g)
{
  g.fillAll(juce::Colours::transparentBlack);
}

void ToneComponent::resized()
{
  auto area = getLocalBounds().reduced(0);
  auto graphArea = area.removeFromTop(area.getHeight()-UI_KNOB_HEIGHT);
  
  auto SliderArea = area;
  SliderArea.removeFromLeft(SliderArea.getWidth()-140);
  tiltKnob.setBounds(SliderArea.removeFromLeft(UI_KNOB_WIDTH));
  midsideKnob.setBounds(SliderArea.removeFromLeft(UI_KNOB_WIDTH));
}
