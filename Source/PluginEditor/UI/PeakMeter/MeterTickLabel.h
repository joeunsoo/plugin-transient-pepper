#pragma once

#include <JuceHeader.h>
#include "../../Provider/ScaleProvider.h"
#include "../../DefineUI.h"
#include "../../../Utils.h"

class MeterTickLabel : public juce::Component
{
  public:
  MeterTickLabel(const ScaleProvider& sp,
                 bool hasMeterLabelValue,
                 bool showLabel)
  :scaleProvider(sp)
  {
    isLabel = showLabel;
    hasMeterLabel = hasMeterLabelValue;
  };
  ~MeterTickLabel() override = default;
  
  void paint(juce::Graphics& g) override
  {
    auto scale = scaleProvider.getScale();
    auto boundsOut = getLocalBounds().toFloat();
    auto bounds = boundsOut;
    auto labelHeight = hasMeterLabel ? 18 : 0;
    bounds.removeFromTop(UI_METER_PADDING_TOP + labelHeight * scale);
    bounds.removeFromLeft(UI_METER_PADDING_LEFT * scale);
    bounds.removeFromBottom(UI_METER_PADDING_BOTTOM * scale);
    bounds.removeFromRight(UI_METER_PADDING_RIGHT * scale);
    // ===== 눈금 라벨 및 눈금선 추가 =====
    // 표기할 라벨들
    static const std::array<float, 9> kLabels = { -0.0f, -3.0f, -6.0f, -10.0f, -20.0f, -30.0f, -40.0f, -50.0f, -60.0f };
    // 텍스트 스타일
    g.setFont(FONT_PRETENDARD_REGULAR.withHeight(10.0f * scale));
    
    g.setColour(UI_METER_TICK_COLOR);

    for (float dbLabel : kLabels)
    {
      // dB가 미터 범위 밖이면 스킵
      if (dbLabel < kMeterMinDb || dbLabel > kMeterMaxDb)
        continue;
      
      const float n01 = skewedMap(dbLabel, kMeterMinDb, kMeterMaxDb, 0.0f, 1.0f, 1.0f);
      const float y   = bounds.getBottom() - bounds.getHeight() * n01;
      
      if (!isLabel) {
        const float xTickStart = bounds.getX();
        const float xTickEnd   = bounds.getWidth();
        g.drawLine(xTickStart, y, xTickEnd, y, 1.0f);
      } else {
        // 라벨 텍스트
        juce::String text;
        // -0 요청이 있어서 표시 그대로 "-0"로 렌더링
        if (dbLabel == 0.0f)
          text = "-0";
        else
          text = juce::String(dbLabel, 0); // 소수점 없이
        
        // 텍스트 박스: 눈금 왼쪽에 배치
        juce::Rectangle<float> textBox(0 ,y - (8.0f * scale), bounds.getWidth(), 16.0f * scale);
        g.drawFittedText(text, textBox.toNearestInt(), juce::Justification::centred, 1);
      }
    }
  };
  
  private:
  const ScaleProvider& scaleProvider;
  bool isLabel = false;
  bool hasMeterLabel = false;
  
  float kMeterMinDb = UI_METER_MIN_DB;
  float kMeterMaxDb = UI_METER_MAX_DB;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MeterTickLabel)
};


