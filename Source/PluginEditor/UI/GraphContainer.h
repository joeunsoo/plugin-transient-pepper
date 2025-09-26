#pragma once
#include <JuceHeader.h>
#include "../../Define.h"
#include "GraphComponent.h"

// Forward declaration
class PluginEditor;

class GraphContainer : public juce::Component
{
  public:
  GraphContainer(PluginEditor& editor);
  ~GraphContainer() override;

  void paint(juce::Graphics& g) override;
  void resized() override;

  private:
  PluginEditor& editorRef; // 포인터로 저장하면 forward declaration 가능

  GraphComponent inputLevelGraph, envGraph;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GraphContainer)
};
