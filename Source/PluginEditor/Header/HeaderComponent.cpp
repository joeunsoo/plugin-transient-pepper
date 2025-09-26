#include "HeaderComponent.h"
#include "../PluginEditor.h"

//==============================================================================
HeaderComponent::HeaderComponent(PluginEditor& editor)
: editorRef(editor),// 참조 멤버 초기화
bypassComponent(editor), menuComponent(editor) 
{
  addAndMakeVisible(bypassComponent);
  
  addAndMakeVisible(logoLabel);
  logoLabel.setFont(editorRef.fontBold.withHeight(11.5f));
  logoLabel.setColour(juce::Label::textColourId, SECONDARY_RGB[6]);
  logoLabel.setText("Transient Pepper", juce::dontSendNotification);
  logoLabel.setJustificationType(juce::Justification::centredLeft);
  
  addAndMakeVisible(companyLabel);
  companyLabel.setFont(editorRef.fontBold.withHeight(10.0f));
  companyLabel.setText("JoEunsoo", juce::dontSendNotification);
  companyLabel.setJustificationType(juce::Justification::centredRight);
  
  addAndMakeVisible(menuComponent);
}

HeaderComponent::~HeaderComponent() = default;

void HeaderComponent::paint(juce::Graphics& g)
{
  g.fillAll(juce::Colours::transparentBlack);
}

void HeaderComponent::resized()
{
  auto area = getLocalBounds().reduced(5, 5);
  
  // 왼쪽 영역
  auto leftArea = area.removeFromLeft(area.getWidth() / 2);
  bypassComponent.setBounds(leftArea.removeFromLeft(30).reduced(5,5));
  logoLabel.setBounds(leftArea);
  
  // 오른쪽 영역
  auto rightArea = area; // 남은 절반
  companyLabel.setBounds(rightArea.removeFromLeft(rightArea.getWidth() - 30));
  
  menuComponent.setBounds(rightArea.reduced(3,3));
}
