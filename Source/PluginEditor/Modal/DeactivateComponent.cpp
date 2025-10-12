#include "DeactivateComponent.h"
#include "ActivateModal.h"
#include "../DefineUI.h"
#include "../../NamespaceParameterId.h"

//==============================================================================
DeactivateComponent::DeactivateComponent(ActivateModal& modal,
                                         const ScaleProvider& sp,
                                         LicenseProvider& lp)
: modalRef(modal), scaleProvider(sp), licenseProvider(lp)
{
  addAndMakeVisible (flexContainer);
  
  flexContainer.addAndMakeVisible(pluginNameLabel);
  pluginNameLabel.setText (PLUGIN_NAME, juce::dontSendNotification);
  pluginNameLabel.setJustificationType (juce::Justification::centred);
  pluginNameLabel.setColour(juce::Label::textColourId, DARK_RGB_0);
  
  flexContainer.addAndMakeVisible(accountEmailLabel);
  accountEmailLabel.setJustificationType (juce::Justification::centred);
  accountEmailLabel.setColour(juce::Label::textColourId, DARK_RGB_0);
  
  flexContainer.addAndMakeVisible(deactivateButton);
  deactivateButton.setButtonText("Deactivate");
  deactivateButton.setColour(juce::TextButton::buttonColourId, DARK_RGB_5);
  deactivateButton.setColour(juce::TextButton::textColourOffId, DARK_RGB_0);
  deactivateButton.setColour(juce::ComboBox::outlineColourId, DARK_RGB_5);
  
  pluginNameLabel.setInterceptsMouseClicks(false, false);
  
  accountEmailLabel.setInterceptsMouseClicks(false, false);
  
  deactivateButton.onClick = [this]()
  {
    licenseProvider.setDeactivate();
    modalRef.resized();
  };
}

DeactivateComponent::~DeactivateComponent() {
  deactivateButton.onClick = nullptr;
};

void DeactivateComponent::resized()
{
  auto scale = scaleProvider.getScale();

  pluginNameLabel.setFont(FONT_PRETENDARD_BOLD.withHeight(UI_PLUGIN_NAME_FONT_HEIGHT * scale));
  accountEmailLabel.setFont(FONT_PRETENDARD_MEDIUM.withHeight(10.0f * scale));

  auto accountEmail = licenseProvider.getActivate();
  accountEmailLabel.setText (accountEmail, juce::dontSendNotification);

  auto bounds = getLocalBounds();
  flexContainer.setBounds(getLocalBounds());

  juce::FlexBox flexBox;
  flexBox.flexDirection = FlexBox::Direction::column;
  flexBox.justifyContent = juce::FlexBox::JustifyContent::center;
  flexBox.alignItems = juce::FlexBox::AlignItems::center;

  flexBox.items.add(FlexItem(pluginNameLabel)
                    .withWidth(bounds.getWidth())
                    .withMinHeight(UI_PLUGIN_NAME_FONT_HEIGHT * scale)
                    .withMargin(FlexItem::Margin{0, 0, 8 * scale, 0}));
  
  flexBox.items.add(FlexItem(accountEmailLabel)
                    .withWidth(bounds.getWidth())
                    .withMinHeight(15.0f * scale)
                    .withMargin(FlexItem::Margin{0, 0, 8 * scale, 0}));
  
  flexBox.items.add(FlexItem(deactivateButton)
                    .withWidth(80.0f * scale)
                    .withMinHeight(20.0f * scale));
  
  flexBox.performLayout (flexContainer.getLocalBounds()); // [6]
}

void DeactivateComponent::paint (juce::Graphics& g)
{
  auto scale = scaleProvider.getScale();

  // FlexContainer 배경색
  g.setColour(DARK_RGB_7);
  g.fillRoundedRectangle(flexContainer.getBounds().toFloat(), UI_MODAL_BORDER_RADIUS * scale);
}
