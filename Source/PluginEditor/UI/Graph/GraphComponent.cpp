#include "GraphComponent.h"
#include "../../DefineUI.h"
#include "../../../Utils.h"
#include "../../PluginEditor.h"

GraphComponent::GraphComponent(
                               juce::Colour f,
                               juce::Colour s,
                               PluginEditor& editor,
                               int index
                               )
: editorRef(editor), idx(index), fillColour(f), strokeColour(s)
{
}

GraphComponent::~GraphComponent() = default;

void GraphComponent::paint(juce::Graphics& g)
{
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
    clipPath.addRoundedRectangle(bounds, UI_GRAPH_BORDER_RADIUS);
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
    float newValue = (level1 + level2) / 2.0f;
    float skewValue = applySkew(newValue, 0.0f, 1.0f, 0.15f);
    float y = getHeight() - skewValue * getHeight();

    if (!isGraphInit)
    {
        // 초기 그래프 채우기
        int w = getWidth();
        graphValues.clear();
        for (int i = 0; i < w; ++i)
            graphValues.push_back(y); // 같은 값으로 초기 채움
        lastY = y;
        isGraphInit = true;
        return; // 첫 프레임에서만 초기화
    }

    // 이후 기존 코드: 상승 즉시, 하강 보간
    for (int i = 1; i <= movePixels; ++i)
    {
        float t = (float)i / movePixels;

        if (y < lastY) // 상승
            lastY = y;
        else           // 하강 보간
            lastY += (y - lastY) * t * 0.5f;

        graphValues.push_back(lastY);
    }

    // 최대 width 유지
    while (graphValues.size() > static_cast<std::vector<float>::size_type>(getWidth()))
        graphValues.erase(graphValues.begin());
}
