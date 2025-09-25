#pragma once
#include <JuceHeader.h>
#include "PeakMeterComponent.h"

// Forward declaration
class PluginEditor;

class PeakMeterStereoComponent : public juce::Component
{
  public:
  PeakMeterStereoComponent();
  ~PeakMeterStereoComponent() override;
  
  void init(
            PluginEditor& editor,
            int index
            );
  
  void paint(juce::Graphics& g) override;
  void resized() override;

  private:
  PluginEditor* editorRef = nullptr; // 포인터로 저장하면 forward declaration 가능

  bool isStereo = false;

  PeakMeterComponent leftPeakMeter;
  PeakMeterComponent rightPeakMeter;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PeakMeterStereoComponent)
};
