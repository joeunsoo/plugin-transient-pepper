#include "ToggleButtonComponent.h"
#include "../PluginEditor.h"

//==============================================================================
ToggleButtonComponent::ToggleButtonComponent() {
  
}

ToggleButtonComponent::~ToggleButtonComponent() = default;

void ToggleButtonComponent::init(
                         PluginEditor& editor,
                         const String& parameterID,
                         const String labelText)
{
  editorRef = &editor;
  
  addAndMakeVisible (toggleButton);
  attachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>
  (
   editorRef->processorRef.state,
   parameterID,
   toggleButton
   );
  toggleButton.setButtonText(labelText);
}


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
