#include "PeakMeterComponent.h"
#include "../../Define.h"
#include "../../Utils.h"
#include "../PluginEditor.h"

PeakMeterComponent::PeakMeterComponent()
{
  startTimerHz(UI_TIMER_HZ); // 초당 갱신 프레임
}

PeakMeterComponent::~PeakMeterComponent() = default;

void PeakMeterComponent::init(
                              PluginEditor& editor,
                              int index
                              )
{
  editorRef = &editor;
  idx = index;
}

// 오디오 샘플 값 전달 (0.0 ~ 1.0)
void PeakMeterComponent::setLevel(float newLevel)
{
  float skewLevel = applySkew(newLevel, 0.0f, 1.0f, 0.15f);
  level = juce::jlimit(0.0f, 1.0f, skewLevel);
}

void PeakMeterComponent::paint(juce::Graphics& g)
{
  auto boundsOut = getLocalBounds().toFloat();
  auto bounds = boundsOut;
  bounds.removeFromTop(UI_METER_PADDING_TOP);
  bounds.removeFromLeft(UI_METER_PADDING_LEFT);
  bounds.removeFromBottom(UI_METER_PADDING_BOTTOM);
  bounds.removeFromRight(UI_METER_PADDING_RIGHT);

  // Drop shadow
  juce::Image buttonImage(
                          juce::Image::ARGB,
                          juce::roundToInt(boundsOut.getWidth()),
                          juce::roundToInt(boundsOut.getHeight()),
                          true);
  juce::Graphics g2(buttonImage);
  g2.fillRoundedRectangle(bounds, UI_METER_BORDER_RADIUS);
  
  juce::DropShadow ds(
                      juce::Colours::black.withAlpha(0.5f),
                      1,
                      {0, 3});
  
  // 배경
  g.setColour(SECONDARY_DARK_RGB[9]);
  g.fillRoundedRectangle(bounds, UI_METER_BORDER_RADIUS);
  
  // 클리핑 설정: bounds 안에서만 그리기
  g.saveState();
  g.reduceClipRegion(bounds.getSmallestIntegerContainer());
  
  // 피크 레벨 막대
  float y = bounds.getHeight() * level;
  
  // smoothing
  // smoothedY += 0.2f * (y - smoothedY);
  auto barHeight = y;
  g.setColour(SECONDARY_RGB[6]);
  g.fillRect(bounds.withTop(bounds.getBottom() - barHeight));
  g.restoreState();
}

void PeakMeterComponent::timerCallback()
{
  if (editorRef != nullptr && idx != -1) {
    setLevel(editorRef->processorRef.analysisData[static_cast<size_t>(idx)]);
    repaint();
  }
}
