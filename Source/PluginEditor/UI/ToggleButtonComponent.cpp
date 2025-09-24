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
  const Font fontMedium { FontOptions { editorRef->pretendardMediumTypeface } };
  const Font fontBold { FontOptions { editorRef->pretendardBoldTypeface } };
  
  label.setFont(fontMedium);
  label.setText(labelText, juce::dontSendNotification);
  label.setJustificationType(juce::Justification::centred);
  addAndMakeVisible(label);
  
}


void ToggleButtonComponent::paint(juce::Graphics& g)
{
  g.fillAll(juce::Colours::transparentBlack);
}

void ToggleButtonComponent::resized()
{
  auto area = getLocalBounds();
  label.setBounds(area);
  
}
