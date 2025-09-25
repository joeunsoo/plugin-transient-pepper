#include "DeactivateComponent.h"
#include "../../Define.h"
#include "../../NamespaceParameterId.h"
#include "../PluginEditor.h"

//==============================================================================
DeactivateComponent::DeactivateComponent() {
  addAndMakeVisible (flexContainer);
  
  flexContainer.addAndMakeVisible(pluginNameLabel);
  pluginNameLabel.setText ("Transient Pepper", juce::dontSendNotification);
  pluginNameLabel.setJustificationType (juce::Justification::centred);
  pluginNameLabel.setColour(juce::Label::textColourId, DARK_RGB[0]);
  
  flexContainer.addAndMakeVisible(accountEmailLabel);
  accountEmailLabel.setJustificationType (juce::Justification::centred);
  accountEmailLabel.setColour(juce::Label::textColourId, DARK_RGB[0]);
  
  flexContainer.addAndMakeVisible(deactivateButton);
  
  deactivateButton.setButtonText("Deactivate");
  deactivateButton.setColour(juce::TextButton::buttonColourId, PRIMARY_DARK_RGB[4]);
  deactivateButton.setColour(juce::TextButton::textColourOffId, DARK_RGB[0]);
  deactivateButton.setColour(juce::ComboBox::outlineColourId, PRIMARY_DARK_RGB[4]);
  
}

DeactivateComponent::~DeactivateComponent() = default;

void DeactivateComponent::init(PluginEditor& editor, ActivateModal& modal)
{
  editorRef = &editor;
  modalRef = &modal;

  pluginNameLabel.setFont(editorRef->fontBold.withHeight(UI_PLUGIN_NAME_FONT_HEIGHT));
  pluginNameLabel.setInterceptsMouseClicks(false, false);
  
  auto accountEmail = editorRef->processorRef.licenseManager.getActivate();
  accountEmailLabel.setText (accountEmail, juce::dontSendNotification);
  accountEmailLabel.setFont(editorRef->fontMedium.withHeight(10.0f));
  accountEmailLabel.setInterceptsMouseClicks(false, false);
  
  deactivateButton.onClick = [this]()
  {
    editorRef->processorRef.licenseManager.setDeactivate();
    modalRef->resized();
  };
}

void DeactivateComponent::resized()
{
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
  g.setColour(DARK_RGB[7]);
  g.fillRoundedRectangle(flexContainer.getBounds().toFloat(), UI_MODAL_BORDER_RADIUS);
}
