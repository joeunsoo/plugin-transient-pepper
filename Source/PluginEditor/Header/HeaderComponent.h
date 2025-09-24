#pragma once

#include <JuceHeader.h>
#include "MenuComponent.h"
#include "BypassComponent.h"
#include "../LookAndFeel/HeaderLookAndFeel.h"

// Forward declaration
class PluginEditor;

//==============================================================================
class HeaderComponent : public juce::Component
{
  public:
  HeaderComponent();
  ~HeaderComponent() override;

  void setEditorRef(PluginEditor& editor);
  
  void paint(juce::Graphics& g) override;
  void resized() override;
  
  //==============================================================================
  private:
  PluginEditor* editorRef = nullptr; // 포인터로 저장하면 forward declaration 가능
  HeaderLookAndFeel headerLnF;

  BypassComponent bypassComponent;
  juce::Label logoLabel;
  
  juce::Label companyLabel;
  MenuComponent menuComponent;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HeaderComponent)
};
