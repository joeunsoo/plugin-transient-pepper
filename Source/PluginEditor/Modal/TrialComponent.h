#pragma once

#include <JuceHeader.h>

// Forward declaration
class PluginEditor;
class ActivateModal;

class TrialComponent : public juce::Component
{
  public:
  TrialComponent();
  ~TrialComponent() override;

  void init(PluginEditor& editor, ActivateModal& modal);
  
  void resized() override;
  void paint(juce::Graphics& g) override;

  
  private:
  PluginEditor* editorRef = nullptr; // 포인터로 저장하면 forward declaration 가능
  ActivateModal* modalRef = nullptr; // 포인터로 저장하면 forward declaration 가능

  juce::TextButton trialButton;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TrialComponent)
};
