#include "MainComponent.h"
#include "../../Define.h"
#include "../PluginEditor.h"

//==============================================================================
MainComponent::MainComponent() {
  // DropShadow 설정
  dropShadow.colour = juce::Colours::black.withAlpha(1.0f); // 그림자 색상
  dropShadow.radius = 10;  // blur 반경
  dropShadow.offset = juce::Point<int>(0, 4); // x, y 오프셋
}

MainComponent::~MainComponent()
{
  setLookAndFeel(nullptr);
};

void MainComponent::init(PluginEditor& editor)
{
  editorRef = &editor;

  mainLaf.setFontRegular(editorRef->fontRegular);
  mainLaf.setFontMedium(editorRef->fontMedium);
  mainLaf.setFontSemiBold(editorRef->fontSemiBold);
  mainLaf.setFontBold(editorRef->fontBold);
  setLookAndFeel (&mainLaf);

  addAndMakeVisible(detectorComponent);
  detectorComponent.init(editor);

  addAndMakeVisible(envelopeComponent);
  envelopeComponent.init(editor);
  
  addAndMakeVisible (toneComponent);
  toneComponent.init(editor);

  addAndMakeVisible (mixComponent);
  mixComponent.init(editor);
}

void MainComponent::resized()
{
  auto area = getLocalBounds()
    .withTrimmedLeft(15)
    .withTrimmedTop(5)
    .withTrimmedRight(15)
    .withTrimmedBottom(15);
  auto leftArea = area.removeFromLeft(UI_KNOB_WIDTH * 3);
  detectorComponent.setBounds(leftArea.removeFromTop(150));
  envelopeComponent.setBounds(leftArea);
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
