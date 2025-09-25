#include "DeactivateComponent.h"
#include "../../Define.h"
#include "../../NamespaceParameterId.h"
#include "../PluginEditor.h"

//==============================================================================
DeactivateComponent::DeactivateComponent() {
  
}

DeactivateComponent::~DeactivateComponent() = default;

void DeactivateComponent::init(PluginEditor& editor)
{
  editorRef = &editor;
}

void DeactivateComponent::resized()
{
  
}

void DeactivateComponent::paint (juce::Graphics& g)
{
  g.fillAll (juce::Colours::transparentBlack);
  
}
