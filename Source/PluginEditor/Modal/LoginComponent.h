#pragma once

#include <JuceHeader.h>

// Forward declaration
class PluginEditor;

class LoginComponent : public juce::Component
{
  public:
  LoginComponent();
  ~LoginComponent() override;

  void init(PluginEditor& editor);
  
  void resized() override;
  void paint(juce::Graphics& g) override;

  
  private:
  PluginEditor* editorRef = nullptr; // 포인터로 저장하면 forward declaration 가능

  juce::Component flexContainer;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LoginComponent)
};
