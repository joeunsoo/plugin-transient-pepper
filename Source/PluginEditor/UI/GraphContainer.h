#pragma once
#include <JuceHeader.h>
#include "../../Define.h"
#include "GraphComponent.h"

// Forward declaration
class PluginEditor;

class GraphContainer : public juce::Component
{
  public:
  GraphContainer();
  ~GraphContainer() override;
  
  void init(PluginEditor& editor);

  void paint(juce::Graphics& g) override;
  void resized() override;
  
  private:
  PluginEditor* editorRef = nullptr; // 포인터로 저장하면 forward declaration 가능

  GraphComponent inputLevelGraph { PRIMARY_DARK_RGB[9], PRIMARY_LIGHT_RGB[7] };
  GraphComponent envGraph { SECONDARY_DARK_RGB[2].withAlpha(0.3f), SECONDARY_LIGHT_RGB[7] };

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GraphContainer)
};
