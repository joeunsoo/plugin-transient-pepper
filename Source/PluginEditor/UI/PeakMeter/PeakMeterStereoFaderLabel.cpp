#include "PeakMeterStereoFaderLabel.h"

PeakMeterStereoFaderLabel::PeakMeterStereoFaderLabel(const ScaleProvider& sp,
                                                     ProcessorProvider& pp,
                                                     int index,
                                                     bool usePeakHold,
                                                     const String& paramID,
                                                     const String labelText
                                                     )
: scaleProvider(sp),
processorProvider(pp),
peakMeter(pp, index, usePeakHold)
{
  parameterID = paramID;
  attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
  (
   processorProvider.state(),
   paramID,
   verticalSlider
   );
  
  auto* param = processorProvider.state().getParameter(parameterID);
  jassert(param != nullptr);
  auto range = param->getNormalisableRange(); // NormalisableRange<double>
  verticalSlider.setRange(range.start, range.end, range.interval); // -12..12 dB 등
  
  label.setText(labelText, juce::dontSendNotification);
  label.setJustificationType(juce::Justification::centred);
  label.setColour(juce::Label::textColourId, UI_METER_LABEL_COLOUR);
  
  addAndMakeVisible(label);
  addAndMakeVisible(peakMeter);
  addAndMakeVisible(verticalSlider);
  
  faderLaf.setScaleProvider(&sp);
  setLookAndFeel(&faderLaf);
}

PeakMeterStereoFaderLabel::~PeakMeterStereoFaderLabel()
{
  setLookAndFeel(nullptr);
};

void PeakMeterStereoFaderLabel::paint(juce::Graphics& g)
{
  g.fillAll(juce::Colours::transparentBlack);
}

void PeakMeterStereoFaderLabel::resized()
{
  auto scale = scaleProvider.getScale();

  label.setFont(FONT_PRETENDARD_REGULAR.withHeight(UI_METER_LABEL_FONT_HEIGHT * scale));
  
  auto area = getLocalBounds();
  if (area.isEmpty()) return;
  
  auto labelArea = area.removeFromTop(int(18 * scale));
  label.setBounds(labelArea);
  
  peakMeter.setBounds(area);
  
  auto sliderBounds = area;
  sliderBounds.removeFromTop(int(UI_METER_PADDING_TOP * scale));
  sliderBounds.removeFromLeft(int(UI_METER_PADDING_LEFT * scale));
  sliderBounds.removeFromBottom(int(UI_METER_PADDING_BOTTOM * scale));
  sliderBounds.removeFromRight(int(UI_METER_PADDING_RIGHT * scale));
  verticalSlider.setBounds(sliderBounds.reduced(int(2.0f * scale),0.0f));
  
  verticalSlider.setMouseDragSensitivity(juce::jmax(1, sliderBounds.getHeight()));

}
