#include "ActivateModal.h"
#include "../DefineUI.h"
#include "../../NamespaceParameterId.h"

//==============================================================================
ActivateModal::ActivateModal(const ScaleProvider& sp,
                             LicenseProvider& lp)
: scaleProvider(sp), licenseProvider(lp),
modalLaf(sp),
deactivateComponent(*this, sp, lp), loginComponent(*this, sp, lp)
{
  setInterceptsMouseClicks (true, true); // 뒤에 클릭 못 가게 막음
  setAlwaysOnTop (true);

  setLookAndFeel (&modalLaf);
  
  addAndMakeVisible (deactivateComponent);
  addAndMakeVisible (loginComponent);
}

ActivateModal::~ActivateModal() {
  setLookAndFeel(nullptr);
};


void ActivateModal::resized()
{
  auto scale = scaleProvider.getScale();

  if (licenseProvider.isActivate()) {
    deactivateComponent.setVisible(true);
    loginComponent.setVisible(false);
    deactivateComponent.setBounds(getLocalBounds().withSizeKeepingCentre(int(250 * scale), int(100 * scale)));
  } else {
    deactivateComponent.setVisible(false);
    loginComponent.setVisible(true);
    loginComponent.setBounds(getLocalBounds().withSizeKeepingCentre(int(250 * scale), int(220 * scale)));
  }
}

void ActivateModal::paint (juce::Graphics& g)
{
  // 반투명 배경
  g.fillAll (juce::Colours::black.withAlpha (0.5f));
}

void ActivateModal::mouseUp (const juce::MouseEvent&)
{
  if (licenseProvider.isActivate()) {
    close();
  }

  // 트라이얼 유효 유무 확인
  if (!licenseProvider.isTrialExpired()) {
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
