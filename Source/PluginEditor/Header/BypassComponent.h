#pragma once

#include <JuceHeader.h>

// Forward declaration
class PluginEditor;

//==============================================================================
class BypassComponent : public juce::ToggleButton
{
  public:
  BypassComponent(PluginEditor& editor);
  ~BypassComponent();
  
  void resized() override {};
  
  //==============================================================================
  protected:
  bool hitTest(int x, int y) override;
  void paintButton(juce::Graphics& g, bool isMouseOver, bool isMouseDown) override;
  
  //==============================================================================
  private:
  PluginEditor& editorRef; // 포인터로 저장하면 forward declaration 가능
  
  std::unique_ptr<juce::Drawable> normalSvg, overSvg, downSvg;
  std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> bypassAttachment;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BypassComponent)
};
