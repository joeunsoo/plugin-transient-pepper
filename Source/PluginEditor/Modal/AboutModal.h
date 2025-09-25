#pragma once

#include <JuceHeader.h>

// Forward declaration
class PluginEditor;

class AboutModal : public juce::Component
{
  public:
  AboutModal();
  ~AboutModal() override;

  void init(PluginEditor& editor);
  
  void showIn(juce::Component& parent);
  void close();
  
  FlexItem flexItemSetting(juce::Component& child);
  void resized() override;
  void paint(juce::Graphics& g) override;
  void mouseUp(const juce::MouseEvent& e) override;

  
  private:
  PluginEditor* editorRef = nullptr; // 포인터로 저장하면 forward declaration 가능
  juce::Label pluginNameLabel, pluginVersionLabel, companyNameLabel;
  
  juce::Component flexContainer;
  
  void disableAllChildrenMouse();
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AboutModal)
};
