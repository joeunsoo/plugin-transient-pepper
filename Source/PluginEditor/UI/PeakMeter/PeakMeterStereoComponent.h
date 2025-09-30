#pragma once
#include <JuceHeader.h>
#include "PeakMeterComponent.h"

// Forward declaration
class PluginEditor;

class PeakMeterStereoComponent : public juce::Component
{
  public:
  PeakMeterStereoComponent(
                           PluginEditor& editor,
                           int index
                           );
  ~PeakMeterStereoComponent() override;
  
  void paint(juce::Graphics& g) override;
  void resized() override;

  private:
  PluginEditor& editorRef; // 포인터로 저장하면 forward declaration 가능

  bool isStereo = false;

  PeakMeterComponent leftPeakMeter, rightPeakMeter;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PeakMeterStereoComponent)
};
