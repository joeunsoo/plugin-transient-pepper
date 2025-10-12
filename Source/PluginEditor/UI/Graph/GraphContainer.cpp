#include "GraphContainer.h"
#include "../../DefineUI.h"
#include "../../../Utils.h"

GraphContainer::GraphContainer(const ScaleProvider& sp, ProcessorProvider& pp)
: scaleProvider(sp), processorProvider(pp),
inputLevelGraph (sp, DARK_RGB_9, DARK_RGB_2),
envGraph (sp, SECONDARY_DARK_RGB_2.withAlpha(0.3f), SECONDARY_LIGHT_RGB_7)
{
  addAndMakeVisible(inputLevelGraph);
  addAndMakeVisible(envGraph);
  
  startTimerHz(UI_TIMER_HZ); // 단일 타이머
}
GraphContainer::~GraphContainer() = default;

void GraphContainer::resized()
{
  auto scale = scaleProvider.getScale();

  auto areaOut = getLocalBounds();
  auto area = areaOut;
  area.removeFromTop(int(UI_GRAPH_PADDING_TOP * scale));
  area.removeFromLeft(int(UI_GRAPH_PADDING_LEFT * scale));
  area.removeFromBottom(int(UI_GRAPH_PADDING_BOTTOM * scale));
  area.removeFromRight(int(UI_GRAPH_PADDING_RIGHT * scale));
  inputLevelGraph.setBounds(area);
  envGraph.setBounds(area);
}

void GraphContainer::paint(juce::Graphics& g)
{
  auto scale = scaleProvider.getScale();

  auto boundsOut = getLocalBounds().toFloat();
  auto bounds = boundsOut;
  bounds.removeFromTop(int(UI_GRAPH_PADDING_TOP * scale));
  bounds.removeFromLeft(int(UI_GRAPH_PADDING_LEFT * scale));
  bounds.removeFromBottom(int(UI_GRAPH_PADDING_BOTTOM * scale));
  bounds.removeFromRight(int(UI_GRAPH_PADDING_RIGHT * scale));
  
  // Drop shadow
  juce::Image graphImage(
                          juce::Image::ARGB,
                          juce::roundToInt(boundsOut.getWidth()),
                          juce::roundToInt(boundsOut.getHeight()),
                          true);
  {
      juce::Graphics g2(graphImage);
      g2.fillRoundedRectangle(bounds, UI_GRAPH_BORDER_RADIUS * scale);
  }
  juce::DropShadow ds(
                      juce::Colours::black.withAlpha(0.5f),
                      int(3 * scale),
                      {0, int(2 * scale)});

  ds.drawForImage(g, graphImage);  // 이제 2개 인자

  // 배경
  g.setColour(SECONDARY_DARK_RGB_9);
  g.fillRoundedRectangle(bounds, int(UI_GRAPH_BORDER_RADIUS * scale));
}

void GraphContainer::timerCallback()
{
    // 모든 그래프 동기화 업데이트
    {
        float l1 = processorProvider.getAnalysisData(4);
        float l2 = processorProvider.getAnalysisData(5);
        inputLevelGraph.updateGraph(l1, l2);
    }

    {
        float l1 = processorProvider.getAnalysisData(6);
        float l2 = processorProvider.getAnalysisData(7);
        envGraph.updateGraph(l1, l2);
    }

    // 동시에 repaint
    inputLevelGraph.repaint();
    envGraph.repaint();
}
