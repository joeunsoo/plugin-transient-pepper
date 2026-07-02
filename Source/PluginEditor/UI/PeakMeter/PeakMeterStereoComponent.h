#pragma once
#include "../../Provider/ProcessorProvider.h"
#include "PeakMeterComponent.h"
#include <JuceHeader.h>

class PeakMeterStereoComponent : public juce::Component {
public:
  PeakMeterStereoComponent(ProcessorProvider &pp, int index, bool usePeakHold);
  ~PeakMeterStereoComponent() override;

  void paint(juce::Graphics &g) override;
  void resized() override;

private:
  bool isStereo = false;

  PeakMeterComponent leftPeakMeter, rightPeakMeter;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PeakMeterStereoComponent)
};
