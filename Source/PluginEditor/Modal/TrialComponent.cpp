#include "TrialComponent.h"
#include "ActivateModal.h"
#include "../DefineUI.h"
#include "../../NamespaceParameterId.h"

//==============================================================================
TrialComponent::TrialComponent(ActivateModal& modal,
                               LicenseProvider& lp)
: modalRef(modal), licenseProvider(lp)
{
  addAndMakeVisible(trialButton);
  trialButton.setColour(juce::TextButton::buttonColourId, DARK_RGB_8);
  trialButton.setColour(juce::TextButton::textColourOffId, DARK_RGB_0);
  trialButton.setColour(juce::ComboBox::outlineColourId, DARK_RGB_8);

  trialButton.onClick = [this]()
  {
    if (!licenseProvider.getTrial()) {
      // 트라이얼 자체를 시작안한상태 였음
      licenseProvider.startTrial();
    }

    modalRef.resized();
    if (!licenseProvider.isTrialExpired()) {
      modalRef.close();
    }
  };
}

TrialComponent::~TrialComponent()
{
  trialButton.onClick = nullptr;
};

void TrialComponent::resized()
{

  bool isTrialExpired = licenseProvider.isTrialExpired();
  int64 trialTimestamp = licenseProvider.getTrial();
  int trialDays = licenseProvider.getTrialDays();

  String buttonText = "Start Trial (30 days)";

  if (trialTimestamp > 0 && isTrialExpired) {
    buttonText = "Trial Ended";
  } else if (trialTimestamp > 0) {
    buttonText = "Continue Trial (" + juce::String(trialDays) + " days remaining)";
  }

  trialButton.setButtonText(buttonText);
  trialButton.setBounds(getLocalBounds());
}

void TrialComponent::paint (juce::Graphics& g)
{
  g.fillAll(juce::Colours::transparentBlack);
}
