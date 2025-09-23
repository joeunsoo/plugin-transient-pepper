#include "HeaderComponent.h"
#include "../PluginEditor.h"

//==============================================================================
HeaderComponent::HeaderComponent()
{
  // 왼쪽 버튼과 텍스트
  addAndMakeVisible(leftButton);
  leftButton.setButtonText("Left Button");
  
  addAndMakeVisible(leftLabel);
  leftLabel.setText("Transient Pepper", juce::dontSendNotification);
  leftLabel.setJustificationType(juce::Justification::centredLeft);
  
  // 오른쪽 버튼과 텍스트
  addAndMakeVisible(rightLabel);
  rightLabel.setText("JoEunsoo", juce::dontSendNotification);
  rightLabel.setJustificationType(juce::Justification::centredRight);
  
  addAndMakeVisible(rightButton);
  rightButton.setButtonText("Right Button");
  
  
  scale100Button.onClick = [this] { editorRef->setScale(100); };
  addAndMakeVisible(scale100Button);
  
  scale150Button.onClick = [this] { editorRef->setScale(150); };
  addAndMakeVisible(scale150Button);
  
  scale200Button.onClick = [this] { editorRef->setScale(200); };
  addAndMakeVisible(scale200Button);
  
}

HeaderComponent::~HeaderComponent() = default;

void HeaderComponent::paint(juce::Graphics& g)
{
  g.fillAll(juce::Colours::darkgrey);
}

void HeaderComponent::resized()
{
  auto area = getLocalBounds().reduced(10);
  
  // 왼쪽 영역
  auto leftArea = area.removeFromLeft(area.getWidth() / 2);
  leftButton.setBounds(leftArea.removeFromLeft(100).reduced(5));
  leftLabel.setBounds(leftArea.reduced(5));
  
  // 오른쪽 영역
  auto rightArea = area; // 남은 절반
  rightLabel.setBounds(rightArea.removeFromLeft(rightArea.getWidth() - 100).reduced(5));
  rightButton.setBounds(rightArea.reduced(5));
  
  scale100Button.setBounds (20, 20, 100, 30);
  scale150Button.setBounds (120, 20, 100, 30);
  scale200Button.setBounds (220, 20, 100, 30);
}
