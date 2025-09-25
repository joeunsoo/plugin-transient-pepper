#pragma once

#include <JuceHeader.h>

// Forward declaration
class PluginEditor;

class DeactivateComponent : public juce::Component
{
  public:
  DeactivateComponent();
  ~DeactivateComponent() override;

  void init(PluginEditor& editor);
  
  void resized() override;
  void paint(juce::Graphics& g) override;

  
  private:
  PluginEditor* editorRef = nullptr; // 포인터로 저장하면 forward declaration 가능

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeactivateComponent)
};
