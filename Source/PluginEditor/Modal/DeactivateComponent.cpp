#include "DeactivateComponent.h"
#include "../DefineUI.h"
#include "../../NamespaceParameterId.h"
#include "../PluginEditor.h"

//==============================================================================
DeactivateComponent::DeactivateComponent(PluginEditor& editor, ActivateModal& modal)
: editorRef(editor), modalRef(modal)
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
  
  pluginNameLabel.setFont(editorRef.fontPretendardBold.withHeight(UI_PLUGIN_NAME_FONT_HEIGHT));
  pluginNameLabel.setInterceptsMouseClicks(false, false);
  
  accountEmailLabel.setFont(editorRef.fontPretendardMedium.withHeight(10.0f));
  accountEmailLabel.setInterceptsMouseClicks(false, false);
  
  deactivateButton.onClick = [this]()
  {
    editorRef.wrapperRef.licenseManager.setDeactivate();
    modalRef.resized();
  };

  resized();
}

DeactivateComponent::~DeactivateComponent() {
  deactivateButton.onClick = nullptr;
};

void DeactivateComponent::resized()
{
  auto accountEmail = editorRef.wrapperRef.licenseManager.getActivate();
  accountEmailLabel.setText (accountEmail, juce::dontSendNotification);

  auto bounds = getLocalBounds();
  flexContainer.setBounds(getLocalBounds());

  juce::FlexBox flexBox;
  flexBox.flexDirection = FlexBox::Direction::column;
  flexBox.justifyContent = juce::FlexBox::JustifyContent::center;
  flexBox.alignItems = juce::FlexBox::AlignItems::center;

  flexBox.items.add(FlexItem(pluginNameLabel)
                    .withWidth(bounds.getWidth())
                    .withMinHeight(UI_PLUGIN_NAME_FONT_HEIGHT)
                    .withMargin(FlexItem::Margin{0, 0, 8, 0}));
  
  flexBox.items.add(FlexItem(accountEmailLabel)
                    .withWidth(bounds.getWidth())
                    .withMinHeight(15.0f)
                    .withMargin(FlexItem::Margin{0, 0, 8, 0}));
  
  flexBox.items.add(FlexItem(deactivateButton)
                    .withWidth(80.0f)
                    .withMinHeight(20.0f));
  
  flexBox.performLayout (flexContainer.getLocalBounds()); // [6]
}

void DeactivateComponent::paint (juce::Graphics& g)
{
  // FlexContainer 배경색
  g.setColour(DARK_RGB_7);
  g.fillRoundedRectangle(flexContainer.getBounds().toFloat(), UI_MODAL_BORDER_RADIUS);
}
