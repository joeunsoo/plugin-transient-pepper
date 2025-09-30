#pragma once

#include <JuceHeader.h>
#include "MenuLookAndFeel.h"

// Forward declaration
class PluginEditor;

//==============================================================================
class MenuComponent : public juce::Component
{
  public:
  MenuComponent(PluginEditor& editor);
  ~MenuComponent() override;
  
  void paint(juce::Graphics& g) override;
  void resized() override;
  
  //==============================================================================
  private:
  PluginEditor& editorRef; // 포인터로 저장하면 forward declaration 가능

  MenuLookAndFeel menuLaF;

  juce::DrawableButton menuButton {
    "menuButton",
    juce::DrawableButton::ImageFitted
  };
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MenuComponent)
};
