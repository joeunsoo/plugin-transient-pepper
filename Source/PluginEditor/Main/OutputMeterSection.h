#pragma once

#include <JuceHeader.h>
#include "../Provider/Providers.h"
#include "../Provider/ScaleProvider.h"
#include "../Provider/ProcessorProvider.h"
#include "../UI/PeakMeter/PeakMeterStereoComponent.h"
#include "../UI/PeakMeter/MeterTickLabel.h"

//==============================================================================
class OutputMeterSection : public juce::Component
{
  public:
  OutputMeterSection(Providers& pv);
  ~OutputMeterSection() override;
  
  void paint(juce::Graphics& g) override;
  void resized() override;

  //==============================================================================
  private:
  const ScaleProvider& scaleProvider;
  //==============================================================================

  PeakMeterStereoComponent outputPeakMeter;
  MeterTickLabel outputMeterTick, meterTickLabel;

  juce::Component tickContainer;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OutputMeterSection)
};
