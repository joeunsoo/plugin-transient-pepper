#pragma once

#include <JuceHeader.h>

// Forward declaration
class PluginEditor;

class AboutModal : public juce::Component
{
  public:
  AboutModal(PluginEditor& editor);
  ~AboutModal() override;

  void showIn(juce::Component& parent);
  void close();
  
  void resized() override;
  void paint(juce::Graphics& g) override;
  void mouseUp(const juce::MouseEvent& e) override;

  
  private:
  PluginEditor& editorRef; // 포인터로 저장하면 forward declaration 가능
  juce::Label pluginNameLabel, pluginVersionLabel, companyNameLabel;
  
  juce::Component flexContainer;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AboutModal)
};
