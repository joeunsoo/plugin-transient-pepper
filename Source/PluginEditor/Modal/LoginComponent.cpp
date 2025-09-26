#include "LoginComponent.h"
#include "../../Define.h"
#include "../../NamespaceParameterId.h"
#include "../PluginEditor.h"

//==============================================================================
LoginComponent::LoginComponent() {
  addAndMakeVisible (flexContainer);
  
  flexContainer.addAndMakeVisible(pluginNameLabel);
  pluginNameLabel.setText ("Transient Pepper", juce::dontSendNotification);
  pluginNameLabel.setJustificationType (juce::Justification::centred);
  pluginNameLabel.setColour(juce::Label::textColourId, DARK_RGB[0]);
  
  flexContainer.addAndMakeVisible(trialComponent);
}

LoginComponent::~LoginComponent() = default;

void LoginComponent::init(PluginEditor& editor, ActivateModal& modal)
{
  editorRef = &editor;
  modalRef = &modal;
  
  pluginNameLabel.setFont(editorRef->fontBold.withHeight(UI_PLUGIN_NAME_FONT_HEIGHT));
  pluginNameLabel.setInterceptsMouseClicks(false, false);

  trialComponent.init(editor, modal);
}

void LoginComponent::resized()
{
  trialComponent.resized();

  flexContainer.setBounds(getLocalBounds());

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
  
  flexBox.items.add(FlexItem(trialComponent)
                    .withWidth(bounds.getWidth())
                    .withMinHeight(20.0f));
  
  flexBox.performLayout (flexContainer.getLocalBounds()); // [6]
}

void LoginComponent::paint (juce::Graphics& g)
{
  // FlexContainer 배경색
  g.setColour(DARK_RGB[7]);
  g.fillRoundedRectangle(flexContainer.getBounds().toFloat(), UI_MODAL_BORDER_RADIUS);
}
