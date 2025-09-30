#include "PluginEditor.h"
#include "DefineUI.h"
#include "../PluginWrapper.h"

// 생성자 정의
PluginEditor::PluginEditor(PluginAudioProcessor& p)
: AudioProcessorEditor(&p), processorRef(p),
  wrapperRef(dynamic_cast<PluginWrapper&>(p)),
  headerComponent(*this), mainComponent(*this),
  aboutModal(*this), activateModal(*this)  // 생성자에서 바로 전달
{
  addAndMakeVisible (headerComponent);
  addAndMakeVisible (mainComponent);
  
  // 기본 크기
  setSize(640, 360);
  setScale(wrapperRef.windowScale);
  
  // 툴팁
  tooltipLabel = std::make_unique<RoundedLabel>();
  tooltipLabel->setColour(juce::Label::backgroundColourId, SECONDARY_RGB_9);
  tooltipLabel->setColour(juce::Label::textColourId, juce::Colours::white);
  tooltipLabel->setJustificationType(juce::Justification::centred);
  tooltipLabel->setBorderRadius(UI_TOOLTIP_BORDER_RADIUS);
  tooltipLabel->setFont(fontPretendardMedium.withHeight(UI_TOOLTIP_FONT_HEIGHT));
  tooltipLabel->setSize(60, 20);
  addAndMakeVisible(*tooltipLabel);
  tooltipLabel->setVisible(false);
  
  if (!wrapperRef.licenseManager.isActivate()
      && wrapperRef.licenseManager.isTrialExpired()) {
    showActivate();
  }
}

// 소멸자
PluginEditor::~PluginEditor() = default;

void PluginEditor::paint(juce::Graphics& g)
{
  g.fillAll(SECONDARY_DARK_RGB_9);
}

void PluginEditor::resized()
{
  // UI layout code
  auto area = getLocalBounds();
  headerComponent.setBounds(area.removeFromTop(34));
  mainComponent.setBounds(area);
}

void PluginEditor::setDrag(bool value, String id) {
  isDrag = value;
  if (!value) {
    dragID = "";
  } else {
    dragID = id;
  }
}
void PluginEditor::showTooltipAt(String id, const juce::Rectangle<int>& area, const juce::String& text)
{
  if (isDrag && dragID != id) { return ; }
  tooltipLabel->setText(text, juce::dontSendNotification);
  tooltipLabel->setBounds(area.getX(), area.getY() + UI_TOOLTIP_OFFSET_TOP, area.getWidth(), 20); // slider 위로 위치
  
  auto textWidth  = tooltipLabel->getFont().getStringWidth(tooltipLabel->getText());
  auto textHeight = tooltipLabel->getFont().getHeight();
  
  // padding 포함
  int labelWidth  = textWidth + (UI_TOOLTIP_PADDING_X*2);
  int labelHeight = static_cast<int>(textHeight) + (UI_TOOLTIP_PADDING_Y*2);
  
  // 부모 기준 가운데 정렬
  int x = area.getCentreX() - labelWidth / 2;
  
  tooltipLabel->setBounds(x, area.getY() + 3, labelWidth, labelHeight);
  tooltipLabel->toFront(true);  // 다른 컴포넌트 위로 올림
  tooltipLabel->setVisible(true);
  
  // 일정 시간 후 숨기기
  // juce::Timer::callAfterDelay(3000, [this]{ tooltipLabel->setVisible(false); });
}

void PluginEditor::setScale(int scale)
{
  wrapperRef.windowScale = scale;
  
#if !DEBUG
  float factor = 1.0f;
  switch (scale)
  {
    case 150: factor = 1.5f; break;
    case 200: factor = 2.0f; break;
    default:  factor = 1.0f; break;
  }

  // 전체 에디터에 transform 적용
  setTransform(juce::AffineTransform::scale(factor));
#else
  setSize(640, 360);
#endif
}

void PluginEditor::showAbout()
{
  aboutModal.showIn (*this);
}

void PluginEditor::showActivate()
{
  activateModal.showIn (mainComponent);
}
