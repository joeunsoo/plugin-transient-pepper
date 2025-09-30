#include "MainComponent.h"
#include "../DefineUI.h"
#include "../PluginEditor.h"

//==============================================================================
MainComponent::MainComponent(PluginEditor& editor)
: editorRef(editor),
detectorComponent(editor), envelopeComponent(editor),
toneComponent(editor), mixComponent(editor)
{
  // DropShadow 설정
  dropShadow.colour = juce::Colours::black.withAlpha(0.5f); // 그림자 색상
  dropShadow.radius = 10;  // blur 반경
  dropShadow.offset = juce::Point<int>(0, 0); // x, y 오프셋
  
  mainLaf.setFontRegular(editorRef.fontPretendardRegular);
  mainLaf.setFontMedium(editorRef.fontPretendardMedium);
  mainLaf.setFontSemiBold(editorRef.fontPretendardSemiBold);
  mainLaf.setFontBold(editorRef.fontPretendardBold);
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
  auto area = getLocalBounds()
    .withTrimmedLeft(15)
    .withTrimmedTop(14)
    .withTrimmedRight(15)
    .withTrimmedBottom(5);
  auto leftArea = area.removeFromLeft((UI_KNOB_WIDTH * 3)-20);
  detectorComponent.setBounds(leftArea.removeFromTop(160));
  envelopeComponent.setBounds(leftArea);
  area.removeFromLeft(20);
  toneComponent.setBounds(area.removeFromLeft(area.getWidth()-(UI_KNOB_WIDTH * 2)));
  mixComponent.setBounds(area);
}

void MainComponent::paint(juce::Graphics& g)
{
  auto bounds = getLocalBounds().toFloat();
  bounds.setBounds(8,0,bounds.getWidth()-16,bounds.getHeight()-5);
  
  float borderRadius = 15.0f;
  // ---------- 1. 외부 그림자 ----------
  juce::Path roundedRect;
  roundedRect.addRoundedRectangle(bounds, borderRadius);
  dropShadow.drawForPath(g, roundedRect);
  
  // 배경다시 그리기
  g.setColour(SECONDARY_DARK_RGB[9]);
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
  g.setColour (PRIMARY_RGB[7].withAlpha (0.35f));
  g.drawLine (bounds.getX() + borderRadius, bounds.getY() + 1,
              bounds.getRight() - borderRadius, bounds.getY() + 1, 1.5f);
  
  // ---------- 4. 경계선(optional) ----------
  g.setColour(PRIMARY_RGB[9].withAlpha(0.1f));
  g.drawRoundedRectangle(bounds, borderRadius, 1.0f);
}
