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
  isStereo = editorRef->processorRef.getTotalNumOutputChannels();
  
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
  auto leftArea = area.removeFromLeft(area.getWidth() / 2);
  auto rightArea = area;
  
  if (!isStereo) {
    leftPeakMeter.setBounds(area);
  } else {
    leftPeakMeter.setBounds(leftArea);
    rightPeakMeter.setBounds(rightArea);
  }
  
  
}
