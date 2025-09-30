#pragma once

#include <JuceHeader.h>

// Forward declaration
class PluginEditor;
class ActivateModal;

class DeactivateComponent : public juce::Component
{
  public:
  DeactivateComponent(PluginEditor& editor, ActivateModal& modal);
  ~DeactivateComponent() override;
  
  void resized() override;
  void paint(juce::Graphics& g) override;

  
  private:
  PluginEditor& editorRef; // 포인터로 저장하면 forward declaration 가능
  ActivateModal& modalRef; // 포인터로 저장하면 forward declaration 가능

  juce::Component flexContainer;
  juce::Label pluginNameLabel, accountEmailLabel;
  juce::TextButton deactivateButton;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeactivateComponent)
};
