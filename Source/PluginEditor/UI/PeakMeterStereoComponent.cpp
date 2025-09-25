#pragma once
#include "PeakMeterStereoComponent.h"
#include "../PluginEditor.h"

PeakMeterStereoComponent::PeakMeterStereoComponent()
{

}

PeakMeterStereoComponent::~PeakMeterStereoComponent() = default;

void PeakMeterStereoComponent::init(
                              PluginEditor& editor,
                              int index
                              )
{
  editorRef = &editor;
  isStereo = editorRef->processorRef.getTotalNumOutputChannels() > 1;
  
  leftPeakMeter.init(editor, index);
  addAndMakeVisible(leftPeakMeter);

  if (isStereo) {
    rightPeakMeter.init(editor, index + 1);
    addAndMakeVisible(rightPeakMeter);
  }
}

void PeakMeterStereoComponent::paint(juce::Graphics& g)
{
  g.fillAll(juce::Colours::transparentBlack);
}

void PeakMeterStereoComponent::resized()
{
  auto area = getLocalBounds();
  auto meterArea = area;
  meterArea.setWidth(std::min(UI_STEREO_METER_MAX_WIDTH,area.getWidth()));
  meterArea.setX((area.getWidth()-meterArea.getWidth())/2);

  auto leftArea = meterArea.removeFromLeft(meterArea.getWidth() / 2);
  auto rightArea = meterArea;

  if (!isStereo) {
    leftPeakMeter.setBounds(meterArea);
  } else {
    leftPeakMeter.setBounds(leftArea);
    rightPeakMeter.setBounds(rightArea);
  }
}
