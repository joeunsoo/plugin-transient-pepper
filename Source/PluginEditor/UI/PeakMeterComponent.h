#pragma once
#include <JuceHeader.h>

// Forward declaration
class PluginEditor;

class PeakMeterComponent : public juce::Component,
private juce::Timer
{
  public:
  PeakMeterComponent(
                     PluginEditor& editor,
                     int index
                     );
  ~PeakMeterComponent() override;
  
  
  void setLevel(float newLevel);
  
  void paint(juce::Graphics& g) override;
  
  private:
  void timerCallback() override;

  PluginEditor& editorRef; // 포인터로 저장하면 forward declaration 가능
  
  int idx = -1;
  float level = 0.0f;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PeakMeterComponent)
};
