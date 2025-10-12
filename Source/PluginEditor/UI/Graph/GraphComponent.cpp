#include "GraphComponent.h"
#include "../../DefineUI.h"
#include "../../../Utils.h"

GraphComponent::GraphComponent(const ScaleProvider& sp,
                               juce::Colour f,
                               juce::Colour s
                               )
: scaleProvider(sp),
fillColour(f), strokeColour(s)
{
}

GraphComponent::~GraphComponent() = default;

void GraphComponent::paint(juce::Graphics& g)
{
  auto scale = scaleProvider.getScale();
  auto bounds = getLocalBounds().toFloat();
  g.setColour(fillColour);
  
  juce::Path fillPath;
  juce::Path strokePath;
  
  if (!graphValues.empty())
  {
    // Path 시작
    fillPath.startNewSubPath(0, getHeight());
    strokePath.startNewSubPath(0, graphValues[0]);
    
    for (size_t i = 0; i < graphValues.size(); ++i)
    {
      fillPath.lineTo((float)i, graphValues[i]);
      strokePath.lineTo((float)i, graphValues[i]);
    }
    
    fillPath.lineTo((float)(graphValues.size() - 1), getHeight());
    fillPath.closeSubPath();
  }
  
  // 클리핑
  g.saveState();
  juce::Path clipPath;
  clipPath.addRoundedRectangle(bounds, UI_GRAPH_BORDER_RADIUS * scale);
  g.reduceClipRegion(clipPath); // clip 영역을 둥근 사각형으로 제한
  
  // 그리기
  g.fillPath(fillPath);
  g.setColour(strokeColour);
  g.strokePath(strokePath, juce::PathStrokeType(2.0f));
  
  // 클리핑
  g.restoreState();
}

void GraphComponent::updateGraph(float level1, float level2)
{
  auto scale = scaleProvider.getScale();

  float in1 = juce::jlimit(kMeterMinDb, kMeterMaxDb, level1);
  float in2 = juce::jlimit(kMeterMinDb, kMeterMaxDb, level2);
  
  float inputDb = (in1 + in2) * 0.5f;
  
  // 3) PeakMeterComponent와 동일한 attack/decay 스무딩
  if (inputDb > displayedLevel)
    displayedLevel += attackCoeff * (inputDb - displayedLevel);
  else
    displayedLevel += decayCoeff  * (inputDb - displayedLevel);
  
  // 4) 렌더용 0..1 스케일로 동일 스큐 매핑 (PeakMeterComponent와 동일한 skewedMap 사용)
  const float level01 = skewedMap(
                                  juce::jlimit(kMeterMinDb, kMeterMaxDb, displayedLevel),
                                  kMeterMinDb,
                                  kMeterMaxDb,
                                  0.0f,
                                  1.0f,
                                  1.0f // 동일 스큐 계수 사용 (PeakMeterComponent에서 1.0f로 호출)
                                  );
  
  // 5) 화면 Y 좌표로 변환 (아래로 갈수록 값이 커지지 않도록 뒤집기)
  const float height = (float)getHeight();
  const float y = height - level01 * height;
  
  constexpr float riseCoeffBase = 0.5f; // 상승 기본 속도
  constexpr float fallCoeffBase = 0.5f; // 하강 기본 속도

  // 반복 스텝은 scale을 반영해 정수로 확정 (최소 1)
  const int steps = juce::jmax(1, (int)std::round(movePixels * scale));

  for (int i = 1; i <= steps; ++i)
  {
      // 0..1 정규화된 진행도
      const float t = (float)i / (float)steps;

      const bool rising = (y < lastY); // 화면 좌표에서 y가 작아지면 레벨 상승
      const float base = rising ? riseCoeffBase : fallCoeffBase;

      // 속도에만 scale을 반영하고, 과도한 가속을 방지하기 위해 0..1로 클램프
      float coeff = juce::jlimit(0.0f, 1.0f, base * scale);

      // 한 스텝의 보간량
      const float interp = t * coeff;

      // 목표 y로 점진 이동 (상승/하강 동일 보간)
      lastY += (y - lastY) * interp;

      graphValues.push_back(lastY);
  }
  
  // 최대 width 유지
  const size_t maxSize = (size_t)juce::jmax(1, getWidth());
  while (graphValues.size() > maxSize)
    graphValues.erase(graphValues.begin());
}


void GraphComponent::resized()
{
  const float height = (float)getHeight();
  
  const int w = juce::jmax(1, getWidth());
  graphValues.clear();
  graphValues.reserve((size_t)w);
  for (int i = 0; i < w; ++i)
    graphValues.push_back(height);
  lastY = height;
}
