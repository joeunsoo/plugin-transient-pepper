#include "TrialComponent.h"
#include "../../Define.h"
#include "../../NamespaceParameterId.h"
#include "../PluginEditor.h"

//==============================================================================
TrialComponent::TrialComponent(PluginEditor& editor, ActivateModal& modal)
: editorRef(editor), modalRef(modal)
{
  addAndMakeVisible(trialButton);
  trialButton.setColour(juce::TextButton::buttonColourId, DARK_RGB[8]);
  trialButton.setColour(juce::TextButton::textColourOffId, DARK_RGB[0]);
  trialButton.setColour(juce::ComboBox::outlineColourId, DARK_RGB[8]);

  trialButton.onClick = [this]()
  {
    if (!editorRef.processorRef.licenseManager.getTrial()) {
      // 트라이얼 자체를 시작안한상태 였음
      editorRef.processorRef.licenseManager.startTrial();
    }

    modalRef.resized();
    if (!editorRef.processorRef.licenseManager.isTrialExpired()) {
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

  bool isTrialExpired = editorRef.processorRef.licenseManager.isTrialExpired();
  int64 trialTimestamp = editorRef.processorRef.licenseManager.getTrial();
  int trialDays = editorRef.processorRef.licenseManager.getTrialDays();

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
