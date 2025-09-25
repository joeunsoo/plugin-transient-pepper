#include "DeactivateComponent.h"
#include "../../Define.h"
#include "../../NamespaceParameterId.h"
#include "../PluginEditor.h"

//==============================================================================
DeactivateComponent::DeactivateComponent() {
  addAndMakeVisible (flexContainer);
}

DeactivateComponent::~DeactivateComponent() = default;

void DeactivateComponent::init(PluginEditor& editor)
{
  editorRef = &editor;
}

void DeactivateComponent::resized()
{
  flexContainer.setBounds(getLocalBounds());
}

void DeactivateComponent::paint (juce::Graphics& g)
{
  // FlexContainer 배경색
  g.setColour(DARK_RGB[7]);
  g.fillRoundedRectangle(flexContainer.getBounds().toFloat(), UI_MODAL_BORDER_RADIUS);
}
