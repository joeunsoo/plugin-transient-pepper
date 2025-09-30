#include "GraphContainer.h"
#include "../DefineUI.h"
#include "../../Utils.h"
#include "../PluginEditor.h"

GraphContainer::GraphContainer(PluginEditor& editor)
: editorRef(editor),
inputLevelGraph (PRIMARY_DARK_RGB[9], PRIMARY_LIGHT_RGB[7], editor, 4),
envGraph (SECONDARY_DARK_RGB[2].withAlpha(0.3f), SECONDARY_LIGHT_RGB[7], editor, 6)
{
  addAndMakeVisible(inputLevelGraph);
  addAndMakeVisible(envGraph);
  
  startTimerHz(UI_TIMER_HZ); // 단일 타이머
}
GraphContainer::~GraphContainer() = default;

void GraphContainer::resized()
{
  auto areaOut = getLocalBounds();
  auto area = areaOut;
  area.removeFromTop(UI_GRAPH_PADDING_TOP);
  area.removeFromLeft(UI_GRAPH_PADDING_LEFT);
  area.removeFromBottom(UI_GRAPH_PADDING_BOTTOM);
  area.removeFromRight(UI_GRAPH_PADDING_RIGHT);
  inputLevelGraph.setBounds(area);
  envGraph.setBounds(area);
}

void GraphContainer::paint(juce::Graphics& g)
{
  auto boundsOut = getLocalBounds().toFloat();
  auto bounds = boundsOut;
  bounds.removeFromTop(UI_GRAPH_PADDING_TOP);
  bounds.removeFromLeft(UI_GRAPH_PADDING_LEFT);
  bounds.removeFromBottom(UI_GRAPH_PADDING_BOTTOM);
  bounds.removeFromRight(UI_GRAPH_PADDING_RIGHT);
  
  // Drop shadow
  juce::Image graphImage(
                          juce::Image::ARGB,
                          juce::roundToInt(boundsOut.getWidth()),
                          juce::roundToInt(boundsOut.getHeight()),
                          true);
  {
      juce::Graphics g2(graphImage);
      g2.fillRoundedRectangle(bounds, UI_GRAPH_BORDER_RADIUS);
  }
  juce::DropShadow ds(
                      juce::Colours::black.withAlpha(0.5f),
                      3,
                      {0, 2});

  ds.drawForImage(g, graphImage);  // 이제 2개 인자

  // 배경
  g.setColour(SECONDARY_DARK_RGB[9]);
  g.fillRoundedRectangle(bounds, UI_GRAPH_BORDER_RADIUS);
}

void GraphContainer::timerCallback()
{
    // 모든 그래프 동기화 업데이트
    {
        float l1 = editorRef.processorRef.analysisData[4];
        float l2 = editorRef.processorRef.analysisData[5];
        inputLevelGraph.updateGraph(l1, l2);
    }

    {
        float l1 = editorRef.processorRef.analysisData[6];
        float l2 = editorRef.processorRef.analysisData[7];
        envGraph.updateGraph(l1, l2);
    }

    // 동시에 repaint
    inputLevelGraph.repaint();
    envGraph.repaint();
}
