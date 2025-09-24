#include "../Define.h"
#include "PluginEditor.h"
#include "../AudioProcessor/PluginAudioProcessor.h"
#include "Header/HeaderComponent.h"
#include "Main/MainComponent.h"

// 생성자 정의
PluginEditor::PluginEditor(PluginAudioProcessor& p)
: AudioProcessorEditor(&p), processorRef(p)
{
  // 헤더 불러오기
  headerComponent.init(*this);
  addAndMakeVisible (headerComponent);

  mainComponent.init(*this);
  addAndMakeVisible (mainComponent);

  // 기본 크기
  setSize(640, 360);
  setScale(processorRef.windowScale);

  tooltipLabel = std::make_unique<juce::Label>();
  tooltipLabel->setColour(juce::Label::backgroundColourId, juce::Colours::black.withAlpha(0.8f));
  tooltipLabel->setColour(juce::Label::textColourId, juce::Colours::white);
  tooltipLabel->setJustificationType(juce::Justification::centred);
  tooltipLabel->setSize(60, 24);
  addAndMakeVisible(*tooltipLabel);
  tooltipLabel->setVisible(false);
}

// 소멸자
PluginEditor::~PluginEditor() = default;

void PluginEditor::paint(juce::Graphics& g)
{
  g.fillAll(SECONDARY_DARK_RGB[9]);
}

void PluginEditor::resized()
{
  // UI layout code
  auto area = getLocalBounds();
  headerComponent.setBounds(area.removeFromTop(35));
  area.setHeight(area.getHeight()-5);
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
    tooltipLabel->setBounds(area.getX(), area.getY() + 3, area.getWidth(), 24); // slider 위로 위치
  
    tooltipLabel->toFront(true);  // 다른 컴포넌트 위로 올림
    tooltipLabel->setVisible(true);

    // 일정 시간 후 숨기기
    // juce::Timer::callAfterDelay(3000, [this]{ tooltipLabel->setVisible(false); });
}

void PluginEditor::setScale(int scale)
{
  processorRef.windowScale = scale;
  
  float factor = 1.0f;
  switch (scale)
  {
    case 150: factor = 1.5f; break;
    case 200: factor = 2.0f; break;
    default:  factor = 1.0f; break;
  }
  
  // 전체 에디터에 transform 적용
  // setTransform(juce::AffineTransform::scale(factor));
}
