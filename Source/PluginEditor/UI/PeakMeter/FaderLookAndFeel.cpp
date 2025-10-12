// DragOnlySlider.h
#include <JuceHeader.h>
#include "FaderLookAndFeel.h"
#include "../../DefineUI.h"
#include "../../../Utils.h"
#include "FaderComponent.h"

// 슬라이더 thumb 옆에 값을 표시하는 커스텀 LookAndFeel
void FaderLookAndFeel::drawLinearSlider(juce::Graphics& g,
                                        int x, int y, int width, int height,
                                        float sliderPos,
                                        float minSliderPos,
                                        float maxSliderPos,
                                        const juce::Slider::SliderStyle style,
                                        juce::Slider& slider)
{
  const float scale = (scaleProvider != nullptr) ? scaleProvider->getScale() : 1.0f;

  auto bounds = slider.getLocalBounds().toFloat();
  if (bounds.getWidth() <= 0.0f || bounds.getHeight() <= 0.0f) return;

  // 배경/트랙은 투명하게 (필요 시 커스터마이즈 가능)
  juce::ignoreUnused(x, y, width, height, minSliderPos, maxSliderPos, style);

  // Thumb 그리기: 얇은 화이트 바 (세로 페이더)
  const auto thumbColour = slider.findColour(juce::Slider::thumbColourId);
  const float thumbWidth = bounds.getWidth(); // 얇은 바
  const float thumbHeight = 18.0f * scale; // 가는 가로선 형태
  const float cx = bounds.getCentreX();
  const float cy = sliderPos; // JUCE가 계산한 thumb 중앙 y 위치
  
  g.setColour(thumbColour);
  g.fillRoundedRectangle({ cx - thumbWidth * 0.5f, cy - thumbHeight * 0.5f, thumbWidth, thumbHeight }, thumbHeight * 0.5f);
  
  bool isValueText = false;
  if (auto* sliderFader = dynamic_cast<FaderComponent*>(&slider)) {
    isValueText = sliderFader->getIsValueText();
  };
  
  if (!isValueText) {
    g.setColour(juce::Colours::white.withAlpha(0.7f));
    auto lineWidth = thumbWidth * 0.6f;
    g.drawLine(cx - lineWidth * 0.5f,
               cy - 2.0f * scale,
               cx + lineWidth * 0.5f,
               cy - 2.0f * scale);
    g.drawLine(cx - lineWidth * 0.5f,
               cy + 2.0f * scale,
               cx + lineWidth * 0.5f,
               cy + 2.0f * scale);
  } else {
    // 값 텍스트 준비
    juce::String valueText;
    
    // 슬라이더 텍스트값 포맷 (텍스트 박스 없으므로 여기서 포맷 제어)
    // 예: dB 형태로 표기. 필요에 맞게 변경하세요.
    const double val = slider.getValue();
    if (slider.getSkewFactor() != 1.0)
    {
      // 스큐가 있을 때도 표시값은 실제 value 사용
    }
    valueText = juce::String(val, 1) + " dB";
    
    // 라벨 캡슐 배치: thumb 오른쪽에 살짝
    const float labelPadding = 6.0f * scale;
    const float labelHeight  = 18.0f * scale;
    const float labelMinWidth = 40.0f * scale;
    
    // 폰트 및 텍스트 측정
    juce::Font font = FONT_WANTED_SANS_REGULAR.withHeight(10.0f * scale);
    g.setFont(font);
    const float textWidth = font.getStringWidthFloat(valueText) + 10.0f * scale; // 좌우 내부 패딩
    const float labelWidth = juce::jmax(labelMinWidth, textWidth);
    
    // 기본 위치: thumb 오른쪽
    float labelX = cx + thumbWidth * 0.5f + labelPadding;
    float labelY = cy - labelHeight * 0.5f;
    
    // 경계 클램프: 라벨이 컴포넌트 밖으로 나가지 않도록
    if (labelX + labelWidth > bounds.getRight())
      labelX = bounds.getRight() - labelWidth - (2.0f * scale);
    
    juce::Rectangle<float> labelBounds(labelX, labelY, labelWidth, labelHeight);
    
    // 라벨 배경 및 테두리
    auto fg = juce::Colours::white;
    // 텍스트 중앙 정렬
    g.setColour(fg);
    juce::Rectangle<float> textBounds = labelBounds.reduced(6.0f * scale, 2.0f * scale);
    g.drawFittedText(valueText, textBounds.getSmallestIntegerContainer(), juce::Justification::centred, int(1 * scale));
  }
}
