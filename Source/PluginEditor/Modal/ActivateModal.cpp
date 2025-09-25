#include "ActivateModal.h"
#include "../../Define.h"
#include "../../NamespaceParameterId.h"
#include "../PluginEditor.h"

//==============================================================================
ActivateModal::ActivateModal() {
  setInterceptsMouseClicks (true, true); // 뒤에 클릭 못 가게 막음
  setAlwaysOnTop (true);
}

ActivateModal::~ActivateModal() = default;

void ActivateModal::init(PluginEditor& editor)
{
  editorRef = &editor;
  deactivateComponent.init(editor);
  loginComponent.init(editor);
  
}

void ActivateModal::resized()
{
  if (editorRef->processorRef.licenseManager.isActivate()) {
    addAndMakeVisible (deactivateComponent);
    deactivateComponent.setBounds(getLocalBounds().withSizeKeepingCentre(250, 100));
  } else {
    addAndMakeVisible (loginComponent);
    loginComponent.setBounds(getLocalBounds().withSizeKeepingCentre(250, 200));
  }
}

void ActivateModal::paint (juce::Graphics& g)
{
  // 반투명 배경
  g.fillAll (juce::Colours::black.withAlpha (0.5f));
}

void ActivateModal::mouseUp (const juce::MouseEvent&)
{
  if (editorRef->processorRef.licenseManager.isActivate()) {
    close();
  }
}

void ActivateModal::showIn (juce::Component& parent)
{
  resized();
  parent.addAndMakeVisible (this);
  setBounds (parent.getLocalBounds());
  toFront (true); // 맨 위로
}

void ActivateModal::close()
{
  setVisible (false);
  if (auto* p = getParentComponent())
    p->removeChildComponent (this);
}
