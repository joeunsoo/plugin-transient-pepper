#include "BypassComponent.h"
#include "../DefineUI.h"
#include "../../NamespaceParameterId.h"

//==============================================================================
BypassComponent::BypassComponent(ProcessorProvider& pp)
{
  setClickingTogglesState(true);
  
  // SVG 로드
  normalSvg = juce::Drawable::createFromImageData(BinaryData::powerbold_svg, BinaryData::powerbold_svgSize);
  overSvg   = normalSvg->createCopy();
  downSvg   = normalSvg->createCopy();
  
  // 상태 변경 시 다시 그리기
  onStateChange = [this] {
    repaint();
  };
  
  // APVTS 연동
  bypassAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>
  (
   pp.state(), // APVTS
   ID::bypass.getParamID(), // 파라미터 ID
   *this
   );
  
  //초기 색 반영
  repaint();
}

BypassComponent::~BypassComponent()
{
  bypassAttachment.reset();
};

bool BypassComponent::hitTest(int x, int y)
{
    int extraMargin = 5; // 클릭 영역 확대
    return juce::Rectangle<int>(-extraMargin, -extraMargin, getWidth() + extraMargin*2, getHeight() + extraMargin*2)
           .contains(x, y);
}

void BypassComponent::paintButton(juce::Graphics& g, bool isMouseOver, bool isMouseDown)
{
  if (!normalSvg) return;
  
  bool value = getToggleState();
  
  juce::Colour activeColor = value ? DARK_RGB_5 : UI_HEADER_MAIN;
  juce::Colour overColor   = value ? DARK_RGB_5.darker(0.5f) : UI_HEADER_MAIN.darker(0.5f);
  juce::Colour downColor   = value ? DARK_RGB_5.darker(0.8f) : UI_HEADER_MAIN.darker(0.8f);
  
  // 매번 새 Drawable 생성 (기존 색 누적 방지)
  auto normal = normalSvg->createCopy();
  auto over   = normalSvg->createCopy();
  auto down   = normalSvg->createCopy();
  
  normal->replaceColour(juce::Colours::black, activeColor);
  over->replaceColour(juce::Colours::black, overColor);
  down->replaceColour(juce::Colours::black, downColor);
  
  juce::Drawable* svgToDraw = normal.get();
  if (isMouseDown) svgToDraw = down.get();
  else if (isMouseOver) svgToDraw = over.get();
  
  svgToDraw->drawWithin(g, getLocalBounds().toFloat(), juce::RectanglePlacement::centred, 1.0f);
}
