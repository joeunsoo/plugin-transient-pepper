#include "ActivateModal.h"
#include "../../Define.h"
#include "../../NamespaceParameterId.h"
#include "../PluginEditor.h"

//==============================================================================
ActivateModal::ActivateModal() {
  setInterceptsMouseClicks (true, true); // 뒤에 클릭 못 가게 막음
  setAlwaysOnTop (true);
}

ActivateModal::~ActivateModal() {
  setLookAndFeel(nullptr);
};

void ActivateModal::init(PluginEditor& editor)
{
  editorRef = &editor;

  modalLaf.setFontRegular(editorRef->fontRegular);
  modalLaf.setFontMedium(editorRef->fontMedium);
  modalLaf.setFontSemiBold(editorRef->fontSemiBold);
  modalLaf.setFontBold(editorRef->fontBold);
  setLookAndFeel (&modalLaf);

  deactivateComponent.init(editor, *this);
  loginComponent.init(editor, *this);
  
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

  // 트라이얼 유효 유무 확인
  if (!editorRef->processorRef.licenseManager.isTrialExpired()) {
    close();
  }
}

void ActivateModal::showIn (juce::Component& parent)
{
  resized();
  parent.addAndMakeVisible (this);
  setBounds (parent.getLocalBounds());
  toFront (true); // 맨 위로
  
  loginComponent.resized();
}

void ActivateModal::close()
{
  setVisible (false);
  if (auto* p = getParentComponent())
    p->removeChildComponent (this);
}
