#include "DetectorComponent.h"
#include "../PluginEditor.h"
#include "../LookAndFeelDemo.h"

//==============================================================================
DetectorComponent::DetectorComponent() {
  addAndMakeVisible(label);
  label.setText("testest", juce::dontSendNotification);
  label.setBounds(10, 10, 100, 30);
}

void DetectorComponent::setEditorRef(PluginEditor& editor)
{
  editorRef = &editor;
  const Font fontBold { FontOptions { editorRef->pretendardBoldTypeface } };

  auto* laf = new CustomLookAndFeel();
  rotarySlider.setLookAndFeel (laf);
  addAndMakeVisible (rotarySlider);
  rotarySlider.setValue (2.5);
  
  addAndMakeVisible(logoLabel);
  logoLabel.setFont(fontBold);
  logoLabel.setText("Transient Pepper", juce::dontSendNotification);
  logoLabel.setJustificationType(juce::Justification::centredLeft);

}

DetectorComponent::~DetectorComponent() = default;

void DetectorComponent::paint(juce::Graphics& g)
{
  g.fillAll(juce::Colour(SECONDARY_DARK_RGB[5]));
}

void DetectorComponent::resized()
{
  auto area = getLocalBounds().reduced(10);
  logoLabel.setBounds (20, 20, 100, 30);
  rotarySlider.setBounds(50, 50, 100, 100);
}
