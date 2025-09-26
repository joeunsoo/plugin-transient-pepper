#include "GraphContainer.h"
#include "../../Define.h"
#include "../../Utils.h"
#include "../PluginEditor.h"

GraphContainer::GraphContainer() { }
GraphContainer::~GraphContainer() = default;

void GraphContainer::init(PluginEditor& editor)
{
  editorRef = &editor;
  inputLevelGraph.init(editor,4);
  envGraph.init(editor,6);

  addAndMakeVisible(inputLevelGraph);
  addAndMakeVisible(envGraph);
}

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
  juce::Graphics g2(graphImage);
  g2.fillRoundedRectangle(bounds, UI_GRAPH_BORDER_RADIUS);
  
  juce::DropShadow ds(
                      juce::Colours::black.withAlpha(0.5f),
                      3,
                      {0, 2});

  ds.drawForImage(g, graphImage);  // 이제 2개 인자

  // 배경
  g.setColour(SECONDARY_DARK_RGB[9]);
  g.fillRoundedRectangle(bounds, UI_GRAPH_BORDER_RADIUS);
}
