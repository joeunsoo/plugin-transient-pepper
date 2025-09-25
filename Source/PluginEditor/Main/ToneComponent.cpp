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
  editorRef->processorRef.parameters.sidechainListen.addListener(this);
  parameterValueChanged(0, 0);
}

void ToneComponent::parameterValueChanged (int, float) {
  bool bypass = editorRef->processorRef.parameters.bypass.get();
  bool sidechainListen = editorRef->processorRef.parameters.sidechainListen.get();
  bool isStereo = editorRef->processorRef.getTotalNumOutputChannels() > 1;

  if (bypass || sidechainListen) {
    tiltKnob.setAlpha(DISABLED_ALPHA);
  } else {
    tiltKnob.setAlpha(1.0f);
  }
  
  
  if (bypass || sidechainListen || !isStereo) {
    midsideKnob.setAlpha(DISABLED_ALPHA);
  } else {
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
