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

  auto area = getLocalBounds().toFloat();
  auto meterArea = area;
  meterArea.setWidth(fminf(UI_STEREO_METER_MAX_WIDTH,area.getWidth()));
  meterArea.setX((area.getWidth()-meterArea.getWidth())/2);

  if (!isStereo) {
    meterArea.removeFromTop(UI_METER_PADDING_TOP);
    meterArea.removeFromLeft(UI_METER_PADDING_LEFT);
    meterArea.removeFromBottom(UI_METER_PADDING_BOTTOM);
    meterArea.removeFromRight(UI_METER_PADDING_RIGHT);

    // Drop shadow
    juce::Image graphImage(
                            juce::Image::ARGB,
                            juce::roundToInt(area.getWidth()),
                            juce::roundToInt(area.getHeight()),
                            true);
    juce::Graphics g2(graphImage);
    g2.fillRoundedRectangle(meterArea, UI_METER_BORDER_RADIUS);
    
    juce::DropShadow ds(
                        juce::Colours::black.withAlpha(0.5f),
                        2,
                        {0, 3});

    ds.drawForImage(g, graphImage);  // 이제 2개 인자
  } else {
    auto leftArea = meterArea.removeFromLeft(meterArea.getWidth() / 2);
    auto rightArea = meterArea;
    leftArea.removeFromTop(UI_METER_PADDING_TOP);
    leftArea.removeFromLeft(UI_METER_PADDING_LEFT);
    leftArea.removeFromBottom(UI_METER_PADDING_BOTTOM);
    leftArea.removeFromRight(UI_METER_PADDING_RIGHT);
    rightArea.removeFromTop(UI_METER_PADDING_TOP);
    rightArea.removeFromLeft(UI_METER_PADDING_LEFT);
    rightArea.removeFromBottom(UI_METER_PADDING_BOTTOM);
    rightArea.removeFromRight(UI_METER_PADDING_RIGHT);
    {
      // Drop shadow
      juce::Image graphImage(
                              juce::Image::ARGB,
                              juce::roundToInt(area.getWidth()),
                              juce::roundToInt(area.getHeight()),
                              true);
      juce::Graphics g2(graphImage);
      g2.fillRoundedRectangle(leftArea, UI_METER_BORDER_RADIUS);
      g2.fillRoundedRectangle(rightArea, UI_METER_BORDER_RADIUS);
      
      juce::DropShadow ds(
                          juce::Colours::black.withAlpha(0.5f),
                          2,
                          {0, 3});

      ds.drawForImage(g, graphImage);  // 이제 2개 인자
    }
  }
}

void PeakMeterStereoComponent::resized()
{
  auto area = getLocalBounds();
  auto meterArea = area;
  meterArea.setWidth(std::min(UI_STEREO_METER_MAX_WIDTH,area.getWidth()));
  meterArea.setX((area.getWidth()-meterArea.getWidth())/2);

  if (!isStereo) {
    leftPeakMeter.setBounds(meterArea);
  } else {
    leftPeakMeter.setBounds(meterArea.removeFromLeft(meterArea.getWidth() / 2));
    rightPeakMeter.setBounds(meterArea);
  }
}
