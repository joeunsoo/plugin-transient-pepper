#pragma once

#include <JuceHeader.h>
#include "TrialComponent.h"
#include "../Provider/ScaleProvider.h"
#include "../Provider/LicenseProvider.h"

// Forward declaration
class ActivateModal;

class LoginComponent : public juce::Component,
private juce::TextEditor::Listener
{
  public:
  LoginComponent(ActivateModal& modal,
                 const ScaleProvider& sp,
                 LicenseProvider& lp);
  ~LoginComponent() override;
  
  void callActivate();
  
  void resized() override;
  void paint(juce::Graphics& g) override;

  
  private:
  void textEditorReturnKeyPressed(juce::TextEditor&) override
  {
      callActivate();
  }

  void textEditorTextChanged(juce::TextEditor&) override {}
  void textEditorEscapeKeyPressed(juce::TextEditor&) override {}
  void textEditorFocusLost(juce::TextEditor&) override {}

  ActivateModal& modalRef; // 포인터로 저장하면 forward declaration 가능
  const ScaleProvider& scaleProvider;
  LicenseProvider& licenseProvider;

  juce::Component flexContainer;
  juce::Label pluginNameLabel, emailLabel, passwordLabel, messageLabel;
  TextEditor emailEditor,
             passwordEditor  { "", (juce_wchar) 0x2022 };

  juce::HyperlinkButton forgotPasswordButton {
    "Forgot password?", {"https://joeunsoo.com/reset-password"}
  };

  juce::TextButton loginButton;

  TrialComponent trialComponent;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LoginComponent)
};
