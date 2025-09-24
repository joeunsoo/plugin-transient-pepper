#include "MainComponent.h"
#include "../PluginEditor.h"

//==============================================================================
MainComponent::MainComponent() {
  
}

MainComponent::~MainComponent()
{
  setLookAndFeel(nullptr);
};

void MainComponent::init(PluginEditor& editor)
{
  editorRef = &editor;

  mainLaf.setMediumTypeface(editorRef->pretendardMediumTypeface);
  mainLaf.setSemiBoldTypeface(editorRef->pretendardSemiBoldTypeface);
  mainLaf.setBoldTypeface(editorRef->pretendardSemiBoldTypeface);
  setLookAndFeel (&mainLaf);

  addAndMakeVisible(detectorComponent);
  detectorComponent.init(editor);

  // DropShadow 설정
  dropShadow.colour = juce::Colours::black.withAlpha(0.2f); // 그림자 색상
  dropShadow.radius = 10;  // blur 반경
  dropShadow.offset = juce::Point<int>(0, 4); // x, y 오프셋
}

void MainComponent::paint(juce::Graphics& g)
{
  auto bounds = getLocalBounds().toFloat();
  float borderRadius = 15.0f;
  // ---------- 1. 외부 그림자 ----------
  juce::Path roundedRect;
  roundedRect.addRoundedRectangle(bounds, borderRadius);
  dropShadow.drawForPath(g, roundedRect);
  
  // ---------- 2. 반투명 배경 (glass effect) ----------
  juce::ColourGradient glassGradient(
                                     juce::Colours::white.withAlpha(0.15f), // 상단 밝기
                                     bounds.getX(), bounds.getY(),
                                     juce::Colours::white.withAlpha(0.05f), // 하단 살짝 투명
                                     bounds.getX(), bounds.getBottom(),
                                     false
                                     );
  g.setGradientFill(glassGradient);
  g.fillRoundedRectangle(bounds, borderRadius);
  
  // ---------- 3. 상단 하이라이트 ----------
  juce::ColourGradient highlight(
                                 juce::Colours::white.withAlpha(0.2f),
                                 bounds.getX(), bounds.getY(),
                                 juce::Colours::transparentWhite,
                                 bounds.getX(), bounds.getY() + 30.0f,
                                 false
                                 );
  g.setGradientFill(highlight);
  g.fillRoundedRectangle(bounds, borderRadius);
  
  // ---------- 4. 경계선(optional) ----------
  g.setColour(juce::Colours::white.withAlpha(0.1f));
  g.drawRoundedRectangle(bounds, borderRadius, 1.0f);
}

void MainComponent::resized()
{
  auto area = getLocalBounds().reduced(10);
  detectorComponent.setBounds(area);
}
