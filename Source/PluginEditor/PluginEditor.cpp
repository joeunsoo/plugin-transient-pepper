#include "PluginEditor.h"
#include "DefineUI.h"
#include "../PluginWrapper.h"

// 생성자 정의
PluginEditor::PluginEditor(PluginAudioProcessor& p)
: AudioProcessorEditor(&p), processorRef(p),
wrapperRef(dynamic_cast<PluginWrapper&>(p)),
processorProvider(p),
licenseProvider(wrapperRef),
providers{*this, *this, *this, processorProvider, licenseProvider},
headerComponent(providers), mainComponent(providers),
aboutModal(providers.scale), activateModal(providers.scale, providers.license)
{
  addAndMakeVisible (headerComponent);
  addAndMakeVisible (mainComponent);
  
  // 기본 크기
  setSize(640, 360);
  setScale(wrapperRef.windowScale);
  
  // 툴팁
  tooltipLabel = std::make_unique<RoundedLabel>();
  tooltipLabel->setColour(juce::Label::backgroundColourId, UI_MAIN_BACKGROUND);
  tooltipLabel->setColour(juce::Label::textColourId, juce::Colours::white);
  tooltipLabel->setJustificationType(juce::Justification::centred);
  tooltipLabel->setBorderRadius(UI_TOOLTIP_BORDER_RADIUS);
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
  g.fillAll(UI_MAIN_BACKGROUND);
}

void PluginEditor::resized()
{
  // UI layout code
  auto area = getLocalBounds();
  headerComponent.setBounds(area.removeFromTop(int (34.0f * getScale())));
  mainComponent.setBounds(area);
  
  // 모달이 떠있다면 부모 변화에 맞춰 모달 크기/레이아웃 갱신
  if (aboutModal.isVisible())
  {
    aboutModal.setBounds(mainComponent.getLocalBounds()); // 전체 오버레이 크기 동기화
    aboutModal.resized();                   // 내부 Flex 레이아웃 즉시 갱신
    aboutModal.repaint();                   // 배경/라운디드 박스 다시 그리기
  }
  
  if (activateModal.isVisible())
  {
    activateModal.setBounds(mainComponent.getLocalBounds());
    activateModal.resized();
    activateModal.repaint();
  }
}

void PluginEditor::setDrag(bool value, String id) noexcept
{
  isDrag = value;
  if (!value) {
    dragID = "";
  } else {
    dragID = id;
  }
}

void PluginEditor::showTooltipAt(String id, const juce::Rectangle<int>& area, const juce::String& text) const noexcept
{
  auto scale = getScale();
  if (isDrag && dragID != id) { return ; }
  tooltipLabel->setText(text, juce::dontSendNotification);
  tooltipLabel->setBounds(area.getX(), area.getY() + int(UI_TOOLTIP_OFFSET_TOP * scale), area.getWidth(), int(20.0f * scale)); // slider 위로 위치
  
  tooltipLabel->setFont(FONT_PRETENDARD_MEDIUM.withHeight(UI_TOOLTIP_FONT_HEIGHT*scale));
  auto textWidth  = tooltipLabel->getFont().getStringWidth(tooltipLabel->getText());
  auto textHeight = tooltipLabel->getFont().getHeight();
  
  // padding 포함
  int labelWidth  = textWidth + int(UI_TOOLTIP_PADDING_X * 2 * scale);
  int labelHeight = static_cast<int>(textHeight) + int(UI_TOOLTIP_PADDING_Y * 2 * scale);
  
  // 부모 기준 가운데 정렬
  int x = area.getCentreX() - labelWidth / 2;
  
  tooltipLabel->setBounds(x, area.getY() + 3, labelWidth, labelHeight);
  tooltipLabel->toFront(true);  // 다른 컴포넌트 위로 올림
  tooltipLabel->setVisible(true);
  
  // 일정 시간 후 숨기기
  // juce::Timer::callAfterDelay(3000, [this]{ tooltipLabel->setVisible(false); });
}


void PluginEditor::setTooltipLabelVisible(bool value) const noexcept
{
  tooltipLabel->setVisible(value);
}

void PluginEditor::setScale(int scale) noexcept
{
  wrapperRef.windowScale = scale;
  
  float factor = 1.0f;
  switch (scale)
  {
    case 150: factor = 1.5f; break;
    case 200: factor = 2.0f; break;
    default:  factor = 1.0f; break;
  }
  setSize((int)(640.0f * factor), (int)(360.0f * factor));
}

void PluginEditor::showAbout()
{
  aboutModal.showIn (mainComponent);
}

void PluginEditor::showActivate()
{
  activateModal.showIn (mainComponent);
}
