#pragma once
#include <JuceHeader.h>
#include "../../Provider/ScaleProvider.h"
#include "../../Provider/ProcessorProvider.h"
#include "PeakMeterStereoComponent.h"
#include "FaderComponent.h"
#include "FaderLookAndFeel.h"

class PeakMeterStereoFaderLabel : public juce::Component
{
  public:
  PeakMeterStereoFaderLabel(const ScaleProvider& sp,
                            ProcessorProvider& pp,
                            int index,
                            bool usePeakHold,
                            const String& parameterID,
                            const String labelText
                            );
  ~PeakMeterStereoFaderLabel() override;
  
  void paint(juce::Graphics& g) override;
  void resized() override;
  
  void setSliderAlpha(float alpha) {
    verticalSlider.setAlpha(alpha);
  }
  
  
  private:
  const ScaleProvider& scaleProvider;
  ProcessorProvider& processorProvider;
  FaderLookAndFeel faderLaf;
  FaderComponent verticalSlider;

  String parameterID;
  
  PeakMeterStereoComponent peakMeter;
  juce::Label label;
  juce::Component flexContainer;
  
  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PeakMeterStereoFaderLabel)
};
