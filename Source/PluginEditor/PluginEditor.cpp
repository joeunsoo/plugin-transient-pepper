#include "PluginEditor.h"
#include "../AudioProcessor/PluginAudioProcessor.h"

// 생성자 정의
PluginEditor::PluginEditor(PluginAudioProcessor& p)
: AudioProcessorEditor(&p), processorRef(p)
{
  setSize(1000, 500);
  
  auto* laf = new CustomLookAndFeel();
  rotarySlider.setLookAndFeel (laf);
  addAndMakeVisible (rotarySlider);
  rotarySlider.setValue (2.5);
  // addAndMakeVisible(flexDemo); // FlexBoxDemo를 Editor 안에 표시
}

// 소멸자
PluginEditor::~PluginEditor() = default;

void PluginEditor::paint(juce::Graphics& g)
{
  // g.fillAll(juce::Colours::black);
}

void PluginEditor::resized()
{
  // UI layout code
  rotarySlider.setBounds(50, 50, 100, 100);
  // rotarySlider  .setBounds (row.removeFromLeft (100).reduced (5));
}

void PluginEditor::setScale(int scale)
{
  processorRef.windowScale = scale;
  
  int width = 640;
  int height = 360;
  
  switch (processorRef.windowScale)
  {
    case 100:
      setSize(width, height);
      break;
    case 150:
      setSize(
              static_cast<int>(std::round(width * 1.5f)),
              static_cast<int>(std::round(height * 1.5f))
              );
      break;
    case 200:
      setSize(
              static_cast<int>(std::round(width * 2.0f)),
              static_cast<int>(std::round(height * 2.0f))
              );
      break;
    default:
      setSize(width, height);
  }
}
