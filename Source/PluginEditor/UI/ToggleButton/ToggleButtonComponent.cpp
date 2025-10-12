#include "ToggleButtonComponent.h"

//==============================================================================
ToggleButtonComponent::ToggleButtonComponent(
                                             const ScaleProvider& sp,
                                             ProcessorProvider& pp,
                                             const String& parameterID,
                                             const String labelText)
: toggleButton(sp)
{
  addAndMakeVisible (toggleButton);
  
  attachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>
  (
   pp.state(),
   parameterID,
   toggleButton
   );
  toggleButton.setButtonText(labelText);
}

ToggleButtonComponent::~ToggleButtonComponent()
{
  attachment.reset();
};

void ToggleButtonComponent::paint(juce::Graphics& g)
{
  g.fillAll(juce::Colours::transparentBlack);
}

void ToggleButtonComponent::resized()
{
  auto area = getLocalBounds();
  toggleButton.setBounds(area);
}

void ToggleButtonComponent::setSvgDrawable(std::unique_ptr<Drawable> svgDrawable)
{
  toggleButton.setSvgDrawable(std::move(svgDrawable));
}

void ToggleButtonComponent::setButtonText(const String labelText)
{
  toggleButton.setButtonText(labelText);
}
