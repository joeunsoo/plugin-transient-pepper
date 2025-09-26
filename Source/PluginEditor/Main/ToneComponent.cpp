#include "ToneComponent.h"
#include "../PluginEditor.h"

//==============================================================================
ToneComponent::ToneComponent(PluginEditor& editor)
: editorRef(editor),
tiltKnob(editor, ID::tilt.getParamID(), "Tone"),
midsideKnob(editor, ID::midSide.getParamID(), "Mid/Side"),
graphContainer(editor)
{
  addAndMakeVisible(tiltKnob);
  
  addAndMakeVisible(midsideKnob);
  
  editorRef.processorRef.parameters.bypass.addListener(this);
  editorRef.processorRef.parameters.sidechainListen.addListener(this);
  parameterValueChanged(0, 0);

  addAndMakeVisible(graphContainer);
}

ToneComponent::~ToneComponent() = default;

void ToneComponent::parameterValueChanged (int, float) {
  bool bypass = editorRef.processorRef.parameters.bypass.get();
  bool sidechainListen = editorRef.processorRef.parameters.sidechainListen.get();
  bool isStereo = editorRef.processorRef.getTotalNumOutputChannels() > 1;
  
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
  auto area = getLocalBounds().withTrimmedBottom(21);
  auto graphArea = area.removeFromTop(area.getHeight()-UI_KNOB_HEIGHT);
  
  graphContainer.setBounds(graphArea);
  
  auto SliderArea = area;
  SliderArea.removeFromLeft(SliderArea.getWidth()-140);
  tiltKnob.setBounds(SliderArea.removeFromLeft(UI_KNOB_WIDTH));
  midsideKnob.setBounds(SliderArea.removeFromLeft(UI_KNOB_WIDTH));
}
