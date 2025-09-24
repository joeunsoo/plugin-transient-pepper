#include "KnobComponent.h"
#include "../PluginEditor.h"

//==============================================================================
KnobComponent::KnobComponent() {
  
}

KnobComponent::~KnobComponent() = default;

void KnobComponent::init(
                         PluginEditor& editor,
                         const String& parameterID,
                         const String labelText)
{
  editorRef = &editor;
  
  rotarySlider.setColour(
                         juce::Slider::rotarySliderFillColourId,
                         juce::Colours::orange
                         );
  
  rotarySlider.setColour(
                         juce::Slider::rotarySliderOutlineColourId,
                         juce::Colours::blue
                         );

  addAndMakeVisible (rotarySlider);
  attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
  (
   editorRef->processorRef.state,
   parameterID,
   rotarySlider
   );
  
  label.setFont(editorRef->fontMedium);
  label.setText(labelText, juce::dontSendNotification);
  label.setJustificationType(juce::Justification::centred);
  addAndMakeVisible(label);
  
  tooltipLabel.setFont(editorRef->fontMedium);
  tooltipLabel.setText("", juce::dontSendNotification);
  tooltipLabel.setJustificationType(juce::Justification::centred);
  addAndMakeVisible(tooltipLabel);
  
  rotarySlider.onValueChange = [this, parameterID] {
    if (auto* param = editorRef->processorRef.state.getParameter(parameterID))
      tooltipLabel.setText(param->getCurrentValueAsText(), juce::dontSendNotification);
  };
}


void KnobComponent::paint(juce::Graphics& g)
{
  g.fillAll(juce::Colours::transparentBlack);
}

void KnobComponent::resized()
{
  auto area = getLocalBounds();
  rotarySlider.setBounds(area.removeFromTop(area.getHeight() - 10));

  area.setY(area.getY()-10);
  label.setBounds(area);
}

void KnobComponent::setColor(const String color) {
  rotarySlider.color = color;
}

void KnobComponent::setRingColor(const String color) {
  rotarySlider.ringColor = color;
}
