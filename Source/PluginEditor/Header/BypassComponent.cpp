#include "BypassComponent.h"
#include "../PluginEditor.h"

//==============================================================================
BypassComponent::BypassComponent(PluginEditor& editor)
: editorRef(editor) // 참조 멤버 초기화
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
   editorRef.processorRef.state, // APVTS
   ID::bypass.getParamID(), // 파라미터 ID
   *this
   );

  //초기 색 반영
  repaint();
}

BypassComponent::~BypassComponent() = default;

void BypassComponent::paintButton(juce::Graphics& g, bool isMouseOver, bool isMouseDown)
{
    if (!normalSvg) return;

    bool value = getToggleState();

    juce::Colour activeColor = value ? PRIMARY_RGB[7] : SECONDARY_RGB[6];
    juce::Colour overColor   = value ? PRIMARY_RGB[7].darker(0.5f) : SECONDARY_RGB[6].darker(0.5f);
    juce::Colour downColor   = value ? PRIMARY_RGB[7].darker(0.8f) : SECONDARY_RGB[6].darker(0.8f);

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
