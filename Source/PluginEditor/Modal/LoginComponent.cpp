#include "LoginComponent.h"
#include "../../Define.h"
#include "../../NamespaceParameterId.h"
#include "../PluginEditor.h"

//==============================================================================
LoginComponent::LoginComponent(PluginEditor& editor, ActivateModal& modal)
: editorRef(editor), modalRef(modal), trialComponent(editor, modal)
{
  addAndMakeVisible (flexContainer);
  
  flexContainer.addAndMakeVisible(pluginNameLabel);
  pluginNameLabel.setText ("Transient Pepper", juce::dontSendNotification);
  pluginNameLabel.setJustificationType (juce::Justification::centred);
  pluginNameLabel.setColour(juce::Label::textColourId, DARK_RGB[0]);
  
  flexContainer.addAndMakeVisible(emailLabel);
  emailLabel.setText ("Email", juce::dontSendNotification);
  emailLabel.setJustificationType (juce::Justification::centredLeft);
  emailLabel.setColour(juce::Label::textColourId, DARK_RGB[0]);
  
  flexContainer.addAndMakeVisible(passwordLabel);
  passwordLabel.setText ("Password", juce::dontSendNotification);
  passwordLabel.setJustificationType (juce::Justification::centredLeft);
  passwordLabel.setColour(juce::Label::textColourId, DARK_RGB[0]);
  
  flexContainer.addAndMakeVisible(emailEditor);
  flexContainer.addAndMakeVisible(passwordEditor);
  flexContainer.addAndMakeVisible(messageLabel);
  
  flexContainer.addAndMakeVisible(forgotPasswordButton);
  flexContainer.addAndMakeVisible(trialComponent);

  addAndMakeVisible(loginButton);
  loginButton.setColour(juce::TextButton::buttonColourId, PRIMARY_DARK_RGB[4]);
  loginButton.setColour(juce::TextButton::textColourOffId, DARK_RGB[0]);
  loginButton.setColour(juce::ComboBox::outlineColourId, DARK_RGB[2]);
  loginButton.setButtonText("Sign in");
  
  loginButton.onClick = [this]() { callActivate(); };
  emailEditor.addListener(this);
  passwordEditor.addListener(this);
  
  juce::Colour backgroundColourId = DARK_RGB[6];
  juce::Colour outlineColourId = DARK_RGB[5];
  juce::Colour focusedOutlineColourId = DARK_RGB[4];

  pluginNameLabel.setFont(editorRef.fontBold.withHeight(UI_PLUGIN_NAME_FONT_HEIGHT));

  emailLabel.setFont(editorRef.fontRegular.withHeight(UI_MODAL_TEXT_EDITOR_LABEL_FONT_HEIGHT));
  passwordLabel.setFont(editorRef.fontRegular.withHeight(UI_MODAL_TEXT_EDITOR_LABEL_FONT_HEIGHT));

  forgotPasswordButton.setFont(editorRef.fontRegular.withHeight(UI_MODAL_TEXT_LABEL_FONT_HEIGHT), false);
  forgotPasswordButton.setJustificationType (juce::Justification::right);
  forgotPasswordButton.setColour(juce::HyperlinkButton::textColourId, DARK_RGB[1]);

  messageLabel.setFont(editorRef.fontRegular.withHeight(UI_MODAL_TEXT_LABEL_FONT_HEIGHT));
  messageLabel.setJustificationType (juce::Justification::centred);
  messageLabel.setColour(juce::Label::textColourId, SECONDARY_RGB[6]);

  emailEditor.setFont(editorRef.fontRegular.withHeight(UI_MODAL_TEXT_EDITOR_FONT_HEIGHT));
  emailEditor.setJustification(juce::Justification::centredLeft);
  emailEditor.setColour (juce::TextEditor::backgroundColourId, backgroundColourId);
  emailEditor.setColour (juce::TextEditor::outlineColourId, outlineColourId);
  emailEditor.setColour (juce::TextEditor::focusedOutlineColourId, focusedOutlineColourId);
  emailEditor.setColour(juce::CaretComponent::caretColourId, DARK_RGB[0]);

  passwordEditor.setFont(editorRef.fontRegular.withHeight(UI_MODAL_TEXT_EDITOR_FONT_HEIGHT));
  passwordEditor.setJustification(juce::Justification::centredLeft);
  passwordEditor.setColour (juce::TextEditor::backgroundColourId, backgroundColourId);
  passwordEditor.setColour (juce::TextEditor::outlineColourId, outlineColourId);
  passwordEditor.setColour (juce::TextEditor::focusedOutlineColourId, focusedOutlineColourId);
  passwordEditor.setColour(juce::CaretComponent::caretColourId, DARK_RGB[0]);
}

LoginComponent::~LoginComponent() = default;

void LoginComponent::callActivate()
{
  auto email = emailEditor.getText();
  auto password = passwordEditor.getText();
  auto result = editorRef.processorRef.licenseManager.sendActivationRequest(email,password);

  if (result.first == 201) {
    editorRef.processorRef.licenseManager.setActivate(email);
    emailEditor.setText("");
    passwordEditor.setText("");
    messageLabel.setText("", juce::dontSendNotification);
    modalRef.resized();
    modalRef.close();
  } else {
    messageLabel.setText(result.second, juce::dontSendNotification);
  }
}

void LoginComponent::resized()
{
  trialComponent.resized();
  emailEditor.setText("");
  passwordEditor.setText("");
  messageLabel.setText("", juce::dontSendNotification);

  flexContainer.setBounds(getLocalBounds());

  auto bounds = getLocalBounds().reduced(30, 10);
  flexContainer.setBounds(getLocalBounds());

  juce::FlexBox flexBox;
  flexBox.flexDirection = FlexBox::Direction::column;
  flexBox.justifyContent = juce::FlexBox::JustifyContent::center;
  flexBox.alignItems = juce::FlexBox::AlignItems::center;

  flexBox.items.add(FlexItem(pluginNameLabel)
                    .withWidth(bounds.getWidth())
                    .withMinHeight(UI_PLUGIN_NAME_FONT_HEIGHT)
                    .withMargin(FlexItem::Margin{0, 0, 8, 0}));
  
  flexBox.items.add(FlexItem(emailLabel)
                    .withWidth(bounds.getWidth())
                    .withMinHeight(UI_MODAL_TEXT_EDITOR_LABEL_HEIGHT)
                    .withMargin(FlexItem::Margin{0, 0, 2, 0}));
  flexBox.items.add(FlexItem(emailEditor)
                    .withWidth(bounds.getWidth())
                    .withMinHeight(UI_MODAL_TEXT_EDITOR_HEIGHT)
                    .withMargin(FlexItem::Margin{0, 0, 8, 0}));
  
  flexBox.items.add(FlexItem(passwordLabel)
                    .withWidth(bounds.getWidth())
                    .withMinHeight(UI_MODAL_TEXT_EDITOR_LABEL_HEIGHT)
                    .withMargin(FlexItem::Margin{0, 0, 2, 0}));
  flexBox.items.add(FlexItem(passwordEditor)
                    .withWidth(bounds.getWidth())
                    .withMinHeight(UI_MODAL_TEXT_EDITOR_HEIGHT)
                    .withMargin(FlexItem::Margin{0, 0, 8, 0}));

  flexBox.items.add(FlexItem(forgotPasswordButton)
                    .withWidth(bounds.getWidth())
                    .withMinHeight(UI_MODAL_TEXT_LABEL_HEIGHT)
                    .withMargin(FlexItem::Margin{0, 0, 8, 0}));

  flexBox.items.add(FlexItem(messageLabel)
                    .withWidth(bounds.getWidth())
                    .withMinHeight(UI_MODAL_TEXT_LABEL_HEIGHT)
                    .withMargin(FlexItem::Margin{0, 0, 8, 0}));
  
  flexBox.items.add(FlexItem(loginButton)
                    .withWidth(bounds.getWidth())
                    .withMinHeight(20.0f)
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
