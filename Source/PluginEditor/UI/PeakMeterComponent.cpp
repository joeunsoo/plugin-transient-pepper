#pragma once
#include "PeakMeterComponent.h"
#include "../../Define.h"
#include "../PluginEditor.h"

PeakMeterComponent::PeakMeterComponent()
{
  startTimerHz(60); // 초당 갱신 프레임
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
  level = juce::jlimit(0.0f, 1.0f, newLevel);
}

void PeakMeterComponent::paint(juce::Graphics& g)
{
  auto bounds = getLocalBounds().toFloat();
  
  // 배경
  g.setColour(SECONDARY_DARK_RGB[9]);
  g.fillRoundedRectangle(bounds, UI_METER_BORDER_RADIUS);
  
  // 클리핑 설정: bounds 안에서만 그리기
  g.saveState();
  g.reduceClipRegion(bounds.getSmallestIntegerContainer());
  
  // 피크 레벨 막대
  float barHeight = bounds.getHeight() * level;
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
