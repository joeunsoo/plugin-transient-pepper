#include "TrialComponent.h"
#include "../../Define.h"
#include "../../NamespaceParameterId.h"
#include "../PluginEditor.h"

//==============================================================================
TrialComponent::TrialComponent() {
}

TrialComponent::~TrialComponent() = default;

void TrialComponent::init(PluginEditor& editor, ActivateModal& modal)
{
  editorRef = &editor;
  modalRef = &modal;
  
  addAndMakeVisible(trialButton);
  trialButton.setColour(juce::TextButton::buttonColourId, PRIMARY_DARK_RGB[4]);
  trialButton.setColour(juce::TextButton::textColourOffId, DARK_RGB[0]);
  trialButton.setColour(juce::ComboBox::outlineColourId, PRIMARY_DARK_RGB[4]);

  trialButton.onClick = [this]()
  {
    if (!editorRef->processorRef.licenseManager.getTrial()) {
      // 트라이얼 자체를 시작안한상태 였음
      editorRef->processorRef.licenseManager.startTrial();
    }

    modalRef->resized();
    if (!editorRef->processorRef.licenseManager.isTrialExpired()) {
      modalRef->close();
    }
  };
}

void TrialComponent::resized()
{
  bool isTrialExpired = editorRef->processorRef.licenseManager.isTrialExpired();
  int64 trialTimestamp = editorRef->processorRef.licenseManager.getTrial();
  String buttonText = "Start Trial (30 days)";

  if (trialTimestamp > 0 && isTrialExpired) {
    buttonText = "Trial Ended";
  } else if (trialTimestamp > 0) {
    buttonText = "Continue Trial (${trialDays} days remaining)";
  }
  trialButton.setButtonText(buttonText);

  trialButton.setBounds(getLocalBounds());
}

void TrialComponent::paint (juce::Graphics& g)
{
  g.fillAll(juce::Colours::transparentBlack);
}
