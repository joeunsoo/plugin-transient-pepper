#pragma once
#include <JuceHeader.h>

// Forward declaration
class PluginEditor;

class GraphComponent : public juce::Component
{
  public:
  GraphComponent(
                 juce::Colour f,
                 juce::Colour s,
                 PluginEditor& editor,
                 int index
                 );
  ~GraphComponent() override;
  
  
  
  void paint(juce::Graphics& g) override;
  void updateGraph (float level1, float level2);
  
  private:
  
  PluginEditor& editorRef; // 포인터로 저장하면 forward declaration 가능
  
  int idx = -1;
  float lastY = 0.0f;
  int movePixels = 4;
  
  bool isInit = false;
  bool isGraphInit = false;

  juce::Colour fillColour, strokeColour;

  std::vector<float> graphValues; // x축 값 순서대로 저장
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GraphComponent)
};
