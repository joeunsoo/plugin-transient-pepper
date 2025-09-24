#pragma once

#include <JuceHeader.h>
#include "../LookAndFeel/MenuLookAndFeel.h"

// Forward declaration
class PluginEditor;

//==============================================================================
class MenuComponent : public juce::Component
{
  public:
  MenuComponent();
  ~MenuComponent() override;
  
  void setEditorRef(PluginEditor& editor);
  
  void paint(juce::Graphics& g) override;
  void resized() override;
  
  //==============================================================================
  private:
  PluginEditor* editorRef = nullptr; // 포인터로 저장하면 forward declaration 가능
  
  MenuLookAndFeel menuLnF;
  juce::DrawableButton menuButton {
    "menuButton",
    juce::DrawableButton::ImageFitted
  };
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MenuComponent)
};
