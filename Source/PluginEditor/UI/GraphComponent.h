#pragma once
#include <JuceHeader.h>

// Forward declaration
class PluginEditor;

class GraphComponent : public juce::Component,
private juce::Timer
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
  
  private:
  void timerCallback() override;
  
  PluginEditor& editorRef; // 포인터로 저장하면 forward declaration 가능
  
  int idx = -1;
  float level1 = 0.0f;
  float level2 = 0.0f;
  float lastY = 0.0f;
  
  bool isInit = false;
  juce::Image canvasImage, bufferImage;
  
  juce::Colour fillColour, strokeColour;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GraphComponent)
};
