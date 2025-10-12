#include "PeakMeterComponent.h"
#include "../../DefineUI.h"
#include "../../../Utils.h"

PeakMeterComponent::PeakMeterComponent(
                                       ProcessorProvider& pp,
                                       int index,
                                       bool usePeakHold
                                       )
: processorProvider(pp), idx(index)
{
  startTimerHz(UI_TIMER_HZ); // 초당 갱신 프레임
  
  // 초기 스무딩 상태
  displayedLevel = kMeterMinDb;
  smoothedLevel = kMeterMinDb;
  peakHoldLevel  = kMeterMinDb;
  peakHoldShownLevel = kMeterMinDb;
  peakHoldMs     = 300.0;          // 300ms 홀드
  peakHoldElapsedMs = 0.0;
  showPeakHold = usePeakHold;

  // 타이머 주기에 따른 기본 계수 (경험값)
  // attack은 빠르게 따라가고, decay는 천천히 감소
  attackCoeff = 0.5f;              // 0..1 (클수록 빠른 상승)
  decayCoeff  = 0.08f;             // 0..1 (클수록 빠른 하강)
}

PeakMeterComponent::~PeakMeterComponent() = default;

void PeakMeterComponent::paint(juce::Graphics& g)
{
  auto boundsOut = getLocalBounds().toFloat();
  auto bounds = boundsOut;
  bounds.removeFromTop(UI_METER_PADDING_TOP);
  bounds.removeFromLeft(UI_METER_PADDING_LEFT);
  bounds.removeFromBottom(UI_METER_PADDING_BOTTOM);
  bounds.removeFromRight(UI_METER_PADDING_RIGHT);
  
  // Drop shadow
  juce::Image buttonImage(
                          juce::Image::ARGB,
                          juce::roundToInt(boundsOut.getWidth()),
                          juce::roundToInt(boundsOut.getHeight()),
                          true);
  juce::Graphics g2(buttonImage);
  g2.fillRoundedRectangle(bounds, UI_METER_BORDER_RADIUS);
  
  juce::DropShadow ds(
                      juce::Colours::black.withAlpha(0.5f),
                      1,
                      {0, 3});
  
  // 배경
  g.setColour(UI_METER_BACKGROUND);
  g.fillRoundedRectangle(bounds, UI_METER_BORDER_RADIUS);
  
  // 클리핑 설정: bounds 안에서만 그리기
  g.saveState();
  juce::Path clipPath;
  clipPath.addRoundedRectangle(bounds, UI_METER_BORDER_RADIUS);
  g.reduceClipRegion(clipPath); // clip 영역을 둥근 사각형으로 제한
  
  // 피크 레벨 막대

  const float level01   = skewedMap(smoothedLevel, kMeterMinDb, kMeterMaxDb, 0.0f, 1.0f, 1.0f);
  float barHeight = bounds.getHeight() * level01;
  
  juce::ColourGradient meterGradient(SECONDARY_RGB_6,
                                     bounds.getX(), bounds.getY(),
                                     SECONDARY_RGB_6,
                                     bounds.getX(), bounds.getBottom(),
                                     false
                                     );
  
  //g.setColour(TEAL_RGB_6);
  g.setGradientFill(meterGradient);
  g.fillRect(bounds.withTop(bounds.getBottom() - barHeight));
  

  // 선택: 피크 홀드 인디케이터 라인(얇은 선)
  if (showPeakHold)
  {
    const float hold01 = skewedMap(peakHoldShownLevel, kMeterMinDb, kMeterMaxDb, 0.0f, 1.0f, 1.0f);
    const float holdY = bounds.getBottom() - bounds.getHeight() * hold01;
    g.setColour(SECONDARY_RGB_4);
    g.fillRect(bounds.withTop(holdY).withHeight(2.0f));
  }

  // 클리핑 끝
  g.restoreState();
}

void PeakMeterComponent::timerCallback()
{
  if (idx == -1) return;

  // 1) AudioProcessor에서 raw 분석값 읽기 (0..1)
  float inputDb = processorProvider.getAnalysisData(idx);
  inputDb = juce::jlimit(kMeterMinDb, kMeterMaxDb, inputDb); // 안전 클램프

  // 2) raw 도메인에서 attack/decay 스무딩
  if (inputDb > displayedLevel)
    displayedLevel += attackCoeff * (inputDb - displayedLevel);
  else
    displayedLevel += decayCoeff  * (inputDb - displayedLevel);

  // 3) peak hold도 raw 도메인에서 유지
  if (showPeakHold)
  {
    const double dtMs = 1000.0 / (double)UI_TIMER_HZ;

    if (displayedLevel > peakHoldLevel)
    {
      peakHoldLevel = displayedLevel;
      peakHoldElapsedMs = 0.0;
    }
    else
    {
      peakHoldElapsedMs += dtMs;
      if (peakHoldElapsedMs >= peakHoldMs)
      {
        // 시간 기반 감소: 초당 40dB 감소 (프레임 환산)
        const float decPerFrameDb = 40.0f / (float)UI_TIMER_HZ;
        peakHoldLevel = juce::jmax(peakHoldLevel - decPerFrameDb, displayedLevel);
      }
    }
  }

  // 4) 렌더 직전 동일 스큐(0.3f) 적용 — 바와 홀드 모두 동일 스케일로
  smoothedLevel      = juce::jlimit(kMeterMinDb, kMeterMaxDb, displayedLevel);
  peakHoldShownLevel = showPeakHold
                       ? juce::jlimit(kMeterMinDb, kMeterMaxDb, peakHoldLevel)
                       : kMeterMinDb;

  repaint();
}
