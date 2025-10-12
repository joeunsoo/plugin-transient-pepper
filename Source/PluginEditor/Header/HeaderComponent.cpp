#include "HeaderComponent.h"

//==============================================================================
HeaderComponent::HeaderComponent(Providers& pv)
: scaleProvider(pv.scale),
bypassComponent(pv.processor),
menuComponent(pv)
{
  addAndMakeVisible(bypassComponent);
  
  addAndMakeVisible(logoLabel);
  logoLabel.setColour(juce::Label::textColourId, UI_HEADER_MAIN);
  logoLabel.setText(PLUGIN_NAME, juce::dontSendNotification);
  logoLabel.setJustificationType(juce::Justification::centredLeft);
  
  addAndMakeVisible(companyLabel);
  companyLabel.setText(COMPANY_NAME, juce::dontSendNotification);
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
  auto scale = scaleProvider.getScale();

  logoLabel.setFont(FONT_PRETENDARD_BOLD.withHeight(11.5f * scale));
  companyLabel.setFont(FONT_PRETENDARD_BOLD.withHeight(10.0f * scale));
  
  auto area = getLocalBounds().reduced(int (5 * scale), int(5 * scale));
  
  // 왼쪽 영역
  auto leftArea = area.removeFromLeft(area.getWidth() / 2);
  bypassComponent.setBounds(leftArea.removeFromLeft(int(30 * scale)).reduced(int (5 * scale), int(5 * scale)));
  logoLabel.setBounds(leftArea);
  
  // 오른쪽 영역
  auto rightArea = area; // 남은 절반
  companyLabel.setBounds(rightArea.removeFromLeft(rightArea.getWidth() - int(30 * scale)));
  
  menuComponent.setBounds(rightArea.reduced(int (3 * scale), int(3 * scale)));
}
