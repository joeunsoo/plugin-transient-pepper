#include "ActivateModal.h"
#include "../DefineUI.h"
#include "../../NamespaceParameterId.h"
#include "../PluginEditor.h"

//==============================================================================
ActivateModal::ActivateModal(PluginEditor& editor)
: editorRef(editor), deactivateComponent(editor, *this), loginComponent(editor, *this)  // 참조 멤버 초기화
{
  setInterceptsMouseClicks (true, true); // 뒤에 클릭 못 가게 막음
  setAlwaysOnTop (true);

  modalLaf.setFontRegular(editorRef.fontPretendardRegular);
  modalLaf.setFontMedium(editorRef.fontPretendardMedium);
  modalLaf.setFontSemiBold(editorRef.fontPretendardSemiBold);
  modalLaf.setFontBold(editorRef.fontPretendardBold);
  setLookAndFeel (&modalLaf);
  
  addAndMakeVisible (deactivateComponent);
  addAndMakeVisible (loginComponent);
}

ActivateModal::~ActivateModal() {
  setLookAndFeel(nullptr);
};


void ActivateModal::resized()
{
  if (editorRef.wrapperRef.licenseManager.isActivate()) {
    deactivateComponent.setVisible(true);
    loginComponent.setVisible(false);
    deactivateComponent.setBounds(getLocalBounds().withSizeKeepingCentre(250, 100));
  } else {
    deactivateComponent.setVisible(false);
    loginComponent.setVisible(true);
    loginComponent.setBounds(getLocalBounds().withSizeKeepingCentre(250, 220));
  }
}

void ActivateModal::paint (juce::Graphics& g)
{
  // 반투명 배경
  g.fillAll (juce::Colours::black.withAlpha (0.5f));
}

void ActivateModal::mouseUp (const juce::MouseEvent&)
{
  if (editorRef.wrapperRef.licenseManager.isActivate()) {
    close();
  }

  // 트라이얼 유효 유무 확인
  if (!editorRef.wrapperRef.licenseManager.isTrialExpired()) {
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
