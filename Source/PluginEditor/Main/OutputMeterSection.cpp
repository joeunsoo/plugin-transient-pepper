#include "OutputMeterSection.h"
#include "../../NamespaceParameterId.h"

//==============================================================================
OutputMeterSection::OutputMeterSection(Providers& pv)
: scaleProvider(pv.scale), processorProvider(pv.processor),
outputPeakMeter(pv.processor, 0, true),
outputMeterTick(pv.scale, false, false),
meterTickLabel(pv.scale, false, true)
{
  tickContainer.addAndMakeVisible(outputMeterTick);
  tickContainer.addAndMakeVisible(meterTickLabel);
  addAndMakeVisible (tickContainer);

  addAndMakeVisible(outputPeakMeter);
}

OutputMeterSection::~OutputMeterSection()
{
};

void OutputMeterSection::paint(juce::Graphics& g)
{
  g.fillAll(juce::Colours::transparentBlack);
}

void OutputMeterSection::resized()
{
  auto scale = scaleProvider.getScale();

  auto area = getLocalBounds();
  outputPeakMeter.setBounds(area);
  
  tickContainer.setBounds(getLocalBounds());

  juce::FlexBox tickBox;
  tickBox.flexDirection = juce::FlexBox::Direction::row;
  tickBox.justifyContent = FlexBox::JustifyContent::center;
  tickBox.alignItems = FlexBox::AlignItems::stretch;
  
  tickBox.items.add(FlexItem(outputMeterTick)
                    .withFlex(1.0f)
                    .withMargin({0, 0, 0, 18 * scale}));
  
  tickBox.items.add(FlexItem(meterTickLabel)
                    .withWidth(18.0f * scale)
                    .withFlex(0.0f, 0.0f));

  tickBox.performLayout(tickContainer.getLocalBounds());
}
