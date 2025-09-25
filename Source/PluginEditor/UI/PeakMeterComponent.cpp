#pragma once
#include "PeakMeterComponent.h"
#include "../PluginEditor.h"

PeakMeterComponent::PeakMeterComponent()
{
  startTimerHz(30); // 초당 30프레임으로 갱신
}

PeakMeterComponent::~PeakMeterComponent() = default;

void PeakMeterComponent::init(
                         PluginEditor& editor)
{
  editorRef = &editor;
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
  g.setColour(juce::Colours::darkgrey);
  g.fillRoundedRectangle(bounds, 4.0f);
  
  // 피크 레벨 막대
  float barHeight = bounds.getHeight() * level;
  g.setColour(juce::Colours::limegreen);
  g.fillRect(bounds.withTop(bounds.getBottom() - barHeight));
  
  // optional: 경계선
  g.setColour(juce::Colours::black);
  g.drawRoundedRectangle(bounds, 4.0f, 1.0f);
}

void PeakMeterComponent::timerCallback()
{
  repaint();
}
