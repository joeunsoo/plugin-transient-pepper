#include "GraphComponent.h"
#include "../../Define.h"
#include "../../Utils.h"
#include "../PluginEditor.h"

GraphComponent::GraphComponent(
                               juce::Colour f,
                               juce::Colour s,
                               PluginEditor& editor,
                               int index
                             )
: editorRef(editor), idx(index), fillColour(f), strokeColour(s)
{
  startTimerHz(UI_TIMER_HZ); // 초당 갱신 프레임
}

GraphComponent::~GraphComponent() = default;

void GraphComponent::paint(juce::Graphics& g)
{
  auto bounds = getLocalBounds().toFloat();
  int width = static_cast<int>(bounds.getWidth());
  int height = static_cast<int>(bounds.getHeight());
  
  if (!isInit) {
    canvasImage = juce::Image(juce::Image::ARGB, width, height, true);
    bufferImage = juce::Image(juce::Image::ARGB, width, height, true);
    lastY = height;
    
    isInit = true;
  }
  
  // 2) 이전 프레임 buffer 복사 (스크롤 처리)
  bufferImage.clear(juce::Rectangle<int>(0, 0, width, height));
  juce::Graphics bufG(bufferImage);
  
  int movePixels = 5;
  bufG.drawImage(canvasImage,
                 0, 0, width - movePixels, height,
                 movePixels, 0, width - movePixels, height,
                 false); // alpha 무시
  
  // 오른쪽 새 영역은 투명
  bufG.setColour(juce::Colours::transparentBlack);
  bufG.fillRect(juce::Rectangle<int>(
                                     (width - movePixels),
                                     0,
                                     (movePixels),
                                     (height)
                                     ));
  
  // 3) 새로운 값 계산
  float newValue = (level1 + level2) / 2.0f;
  float skewValue = applySkew(newValue, 0.0f, 1.0f, 0.15f);
  float y = height - skewValue * height;
  
  // 5) Path 생성 (fill + stroke)
  float cpX = width - movePixels - 0.5f;
  float cpY = (lastY + y) / 2.0f;
  
  // fill용 Path (아래쪽 영역)
  juce::Path fillPath;
  fillPath.startNewSubPath(width - movePixels - 1, lastY);
  fillPath.quadraticTo(cpX, cpY, width - 1, y);
  fillPath.lineTo(width - 1, height);
  fillPath.lineTo(width - movePixels - 1, height);
  fillPath.closeSubPath();
  
  bufG.setColour(fillColour); // 아래쪽 채우기
  bufG.fillPath(fillPath);
  
  // stroke용 Path (위쪽 선)
  juce::Path strokePath;
  strokePath.startNewSubPath(width - movePixels - 1, lastY);
  strokePath.quadraticTo(cpX, cpY, width - 1, y);
  bufG.setColour(strokeColour); // 위쪽 밝은 선
  bufG.strokePath(strokePath, juce::PathStrokeType(2.0f));
  
  lastY = y;
  // 6) canvasImage에 buffer 복사
  canvasImage = bufferImage.createCopy();
  
  // 클리핑
  g.saveState();
  juce::Path clipPath;
  clipPath.addRoundedRectangle(bounds, UI_GRAPH_BORDER_RADIUS);
  g.reduceClipRegion(clipPath); // clip 영역을 둥근 사각형으로 제한
  
  
  // 7) 화면에 그리기 (alpha 무시)
  g.drawImage(canvasImage,
              0, 0, width, height,
              0, 0, canvasImage.getWidth(), canvasImage.getHeight(),
              false);
  
  // 클리핑 끝
  g.restoreState();
}

void GraphComponent::timerCallback()
{
  if (idx != -1) {
    level1 = editorRef.processorRef.analysisData[static_cast<size_t>(idx)];
    level2 = editorRef.processorRef.analysisData[static_cast<size_t>(idx+1)];
    repaint();
  }
}
