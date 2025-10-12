#include "ToneComponent.h"
#include "../../NamespaceParameterId.h"

//==============================================================================
ToneComponent::ToneComponent(Providers& pv)
: scaleProvider(pv.scale), processorProvider(pv.processor),
tiltKnob(pv.editor, pv.scale, pv.processor,  ID::tilt.getParamID(), "Tone"),
midsideKnob(pv.editor, pv.scale, pv.processor, ID::midSide.getParamID(), "Mid/Side"),
graphContainer(pv.scale, pv.processor)
{
  addAndMakeVisible(tiltKnob);
  
  addAndMakeVisible(midsideKnob);

  processorProvider.state().addParameterListener(ID::bypass.getParamID(), this);
  processorProvider.state().addParameterListener(ID::sidechainListen.getParamID(), this);

  parameterChanged("", 0);

  addAndMakeVisible(graphContainer);
}

ToneComponent::~ToneComponent()
{
  processorProvider.state().removeParameterListener(ID::bypass.getParamID(), this);
  processorProvider.state().removeParameterListener(ID::sidechainListen.getParamID(), this);
};

void ToneComponent::parameterChanged (const juce::String&, float) {
  bool bypass = (processorProvider.state().getRawParameterValue(ID::bypass.getParamID())->load() >= 0.5f);
  
  bool sidechainListen = (processorProvider.state().getRawParameterValue(ID::sidechainListen.getParamID())->load() >= 0.5f);
  
  bool isStereo = processorProvider.getTotalNumOutputChannels() > 1;

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
  auto scale = scaleProvider.getScale();
  auto area = getLocalBounds().withTrimmedBottom(int(12 * scale));
  auto graphArea = area.removeFromTop(area.getHeight() - int(UI_KNOB_HEIGHT * scale));
  
  graphContainer.setBounds(graphArea);
  
  auto SliderArea = area;
  SliderArea.removeFromLeft(SliderArea.getWidth()-int(140 * scale));
  tiltKnob.setBounds(SliderArea.removeFromLeft(int(UI_KNOB_WIDTH * scale)));
  midsideKnob.setBounds(SliderArea.removeFromLeft(int(UI_KNOB_WIDTH * scale)));
}
