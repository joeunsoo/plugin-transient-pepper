#pragma once

#include <JuceHeader.h>
#include "TrialComponent.h"

// Forward declaration
class PluginEditor;
class ActivateModal;

class LoginComponent : public juce::Component
{
  public:
  LoginComponent();
  ~LoginComponent() override;

  void init(PluginEditor& editor, ActivateModal& modal);
  
  void resized() override;
  void paint(juce::Graphics& g) override;

  
  private:
  PluginEditor* editorRef = nullptr; // 포인터로 저장하면 forward declaration 가능
  ActivateModal* modalRef = nullptr; // 포인터로 저장하면 forward declaration 가능

  juce::Component flexContainer;
  juce::Label pluginNameLabel, emailLabel, passwordLabel;
  TextEditor emailEditor,
             passwordEditor  { "", (juce_wchar) 0x2022 };

  juce::HyperlinkButton forgotPasswordButton {
    "Forgot password?", {"https://joeunsoo.com/reset-password"}
  };

  juce::TextButton loginButton;

  TrialComponent trialComponent;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LoginComponent)
};
