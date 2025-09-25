#include "HeaderComponent.h"
#include "../PluginEditor.h"

//==============================================================================
HeaderComponent::HeaderComponent() {
  
}

HeaderComponent::~HeaderComponent() = default;

void HeaderComponent::init(PluginEditor& editor)
{
  editorRef = &editor;

  // 왼쪽 버튼과 텍스트
  addAndMakeVisible(bypassComponent);
  bypassComponent.init(editor);
  
  
  addAndMakeVisible(logoLabel);
  logoLabel.setFont(editorRef->fontBold);
  logoLabel.setColour(juce::Label::textColourId, SECONDARY_RGB[6]);
  logoLabel.setText("Transient Pepper", juce::dontSendNotification);
  logoLabel.setJustificationType(juce::Justification::centredLeft);
  
  addAndMakeVisible(companyLabel);
  companyLabel.setFont(editorRef->fontBold);
  companyLabel.setText("JoEunsoo", juce::dontSendNotification);
  companyLabel.setJustificationType(juce::Justification::centredRight);
  
  addAndMakeVisible(menuComponent);
  menuComponent.init(editor);
}

void HeaderComponent::paint(juce::Graphics& g)
{
  g.fillAll(juce::Colours::transparentBlack);
}

void HeaderComponent::resized()
{
  auto area = getLocalBounds().reduced(5, 10);
  
  // 왼쪽 영역
  auto leftArea = area.removeFromLeft(area.getWidth() / 2);
  bypassComponent.setBounds(leftArea.removeFromLeft(30));
  logoLabel.setBounds(leftArea);
  
  // 오른쪽 영역
  auto rightArea = area; // 남은 절반
  companyLabel.setBounds(rightArea.removeFromLeft(rightArea.getWidth() - 30));
  
  menuComponent.setBounds(rightArea);
}
