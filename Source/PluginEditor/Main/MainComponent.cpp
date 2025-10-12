#include "MainComponent.h"
#include "../DefineUI.h"
#include "../PluginEditor.h"

//==============================================================================
MainComponent::MainComponent(Providers& pv)
: scaleProvider(pv.scale), mainLaf(pv.scale),
detectorComponent(pv), envelopeComponent(pv),
toneComponent(pv), mixComponent(pv)
{
  // DropShadow 설정
  dropShadow.colour = juce::Colours::black.withAlpha(0.5f); // 그림자 색상
  dropShadow.radius = 10;  // blur 반경
  dropShadow.offset = juce::Point<int>(0, 0); // x, y 오프셋

  setLookAndFeel (&mainLaf);
  
  addAndMakeVisible(detectorComponent);
  addAndMakeVisible(envelopeComponent);
  addAndMakeVisible (toneComponent);
  addAndMakeVisible (mixComponent);
}

MainComponent::~MainComponent()
{
  setLookAndFeel(nullptr);
};

void MainComponent::resized()
{
  auto scale = scaleProvider.getScale();
  auto area = getLocalBounds()
    .withTrimmedLeft(int(18 * scale))
    .withTrimmedTop(int(14 * scale))
    .withTrimmedRight(int(18 * scale))
    .withTrimmedBottom(int(18 * scale));
  auto leftArea = area.removeFromLeft(int (((UI_KNOB_WIDTH * 3)-20) * scale));
  detectorComponent.setBounds(leftArea.removeFromTop(int(160 * scale)));
  envelopeComponent.setBounds(leftArea);
  area.removeFromLeft(int(20 * scale));
  toneComponent.setBounds(area.removeFromLeft(area.getWidth()-(int(UI_KNOB_WIDTH * scale) * 2)));
  mixComponent.setBounds(area);
}

void MainComponent::paint(juce::Graphics& g)
{
  auto scale = scaleProvider.getScale();

  auto bounds = getLocalBounds().toFloat();
  bounds.setBounds(8 * scale, 0, bounds.getWidth() - (16 * scale), bounds.getHeight() -(5 * scale));
  
  const float borderRadius = 15.0f * scale;
  // ---------- 1. 외부 그림자 ----------
  juce::Path roundedRect;
  roundedRect.addRoundedRectangle(bounds, borderRadius);
  dropShadow.drawForPath(g, roundedRect);
  
  // 배경다시 그리기
  g.setColour(SECONDARY_DARK_RGB_9);
  g.fillRoundedRectangle(bounds, borderRadius);
  
  // ---------- 2. 반투명 배경 (glass effect) ----------
  juce::ColourGradient glassGradient(
                                     juce::Colours::white.withAlpha(0.10f), // 상단 밝기
                                     bounds.getX(), bounds.getY(),
                                     juce::Colours::white.withAlpha(0.0f), // 하단 살짝 투명
                                     bounds.getX(), bounds.getBottom(),
                                     false
                                     );
  g.setGradientFill(glassGradient);
  g.fillRoundedRectangle(bounds, borderRadius);
  
  // 3) 위쪽 하이라이트 (빛 반사)
  g.setColour (DARK_RGB_5.withAlpha (0.35f));
  g.drawLine (bounds.getX() + borderRadius, bounds.getY() + 1,
              bounds.getRight() - borderRadius, bounds.getY() + 1, 1.5f);
  
  // ---------- 4. 경계선(optional) ----------
  g.setColour(juce::Colours::black.withAlpha(0.1f));
  g.drawRoundedRectangle(bounds, borderRadius, 1.0f * scale);
}
