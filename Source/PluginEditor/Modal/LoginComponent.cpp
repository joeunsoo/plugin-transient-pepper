#include "LoginComponent.h"
#include "../../Define.h"
#include "../../NamespaceParameterId.h"
#include "../PluginEditor.h"

//==============================================================================
LoginComponent::LoginComponent() {
  addAndMakeVisible (flexContainer);
}

LoginComponent::~LoginComponent() = default;

void LoginComponent::init(PluginEditor& editor)
{
  editorRef = &editor;
}

void LoginComponent::resized()
{
  flexContainer.setBounds(getLocalBounds());
}

void LoginComponent::paint (juce::Graphics& g)
{
  // FlexContainer 배경색
  g.setColour(DARK_RGB[7]);
  g.fillRoundedRectangle(flexContainer.getBounds().toFloat(), UI_MODAL_BORDER_RADIUS);
}
