#include "HeaderComponent.h"
#include "../PluginEditor.h"

//==============================================================================
HeaderComponent::HeaderComponent() {
  
}

HeaderComponent::~HeaderComponent() = default;

void HeaderComponent::setEditorRef(PluginEditor& editor)
{
  editorRef = &editor;
  const Font fontMedium { FontOptions { editorRef->pretendardMediumTypeface } };
  const Font fontSemiBold { FontOptions { editorRef->pretendardSemiBoldTypeface } };
  const Font fontBold { FontOptions { editorRef->pretendardBoldTypeface } };

  // 왼쪽 버튼과 텍스트
  addAndMakeVisible(leftButton);
  leftButton.setButtonText("Left Button");
  
  
  addAndMakeVisible(logoLabel);
  logoLabel.setFont(fontBold);
  logoLabel.setText("Transient Pepper", juce::dontSendNotification);
  logoLabel.setJustificationType(juce::Justification::centredLeft);
  
  addAndMakeVisible(companyLabel);
  companyLabel.setFont(fontBold);
  companyLabel.setText("JoEunsoo", juce::dontSendNotification);
  companyLabel.setJustificationType(juce::Justification::centredRight);
  
  addAndMakeVisible(menuComponent);
  menuComponent.setEditorRef(editor);

}

void HeaderComponent::paint(juce::Graphics& g)
{
  // g.fillAll(juce::Colours::darkgrey);
}

void HeaderComponent::resized()
{
  auto area = getLocalBounds().reduced(10);
  
  // 왼쪽 영역
  auto leftArea = area.removeFromLeft(area.getWidth() / 2);
  leftButton.setBounds(leftArea.removeFromLeft(100).reduced(5));
  logoLabel.setBounds(leftArea.reduced(5));
  
  // 오른쪽 영역
  auto rightArea = area; // 남은 절반
  companyLabel.setBounds(rightArea.removeFromLeft(rightArea.getWidth() - 100).reduced(5));
  
  menuComponent.setBounds(rightArea.reduced(5));
}
