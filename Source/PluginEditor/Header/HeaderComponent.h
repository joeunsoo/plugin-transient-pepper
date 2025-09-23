#pragma once

#include <JuceHeader.h>

// Forward declaration
class PluginEditor;

//==============================================================================
class HeaderComponent : public juce::Component
{
  public:
  HeaderComponent();
  ~HeaderComponent() override;
  
  void paint(juce::Graphics& g) override;
  void resized() override;
  
  void setEditorRef(PluginEditor& editor) { editorRef = &editor; }
  //==============================================================================
  private:
  PluginEditor* editorRef = nullptr; // 포인터로 저장하면 forward declaration 가능
  
  juce::TextButton leftButton;
  juce::Label leftLabel;
  
  juce::Label rightLabel;
  juce::TextButton rightButton;
  
  juce::TextButton scale100Button { "100%" };
  juce::TextButton scale150Button { "150%" };
  juce::TextButton scale200Button { "200%" };
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HeaderComponent)
};
