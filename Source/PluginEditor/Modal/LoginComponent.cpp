#include "LoginComponent.h"
#include "../../Define.h"
#include "../../NamespaceParameterId.h"
#include "../PluginEditor.h"

//==============================================================================
LoginComponent::LoginComponent() {
  
}

LoginComponent::~LoginComponent() = default;

void LoginComponent::init(PluginEditor& editor)
{
  editorRef = &editor;
}

void LoginComponent::resized()
{
  
}

void LoginComponent::paint (juce::Graphics& g)
{
  g.fillAll (juce::Colours::transparentBlack);
  
}
