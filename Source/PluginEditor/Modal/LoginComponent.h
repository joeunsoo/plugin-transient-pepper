#pragma once

#include <JuceHeader.h>
#include "TrialComponent.h"

// Forward declaration
class PluginEditor;
class ActivateModal;

class LoginComponent : public juce::Component,
private juce::TextEditor::Listener
{
  public:
  LoginComponent(PluginEditor& editor, ActivateModal& modal);
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

  PluginEditor& editorRef; // 포인터로 저장하면 forward declaration 가능
  ActivateModal& modalRef; // 포인터로 저장하면 forward declaration 가능

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
