#pragma once

#include <JuceHeader.h>
#include "MenuComponent.h"
#include "BypassComponent.h"

// Forward declaration
class PluginEditor;

//==============================================================================
class HeaderComponent : public juce::Component
{
  public:
  explicit HeaderComponent(PluginEditor& editor);
  ~HeaderComponent() override;
  
  void paint(juce::Graphics& g) override;
  void resized() override;
  
  //==============================================================================
  private:
  PluginEditor& editorRef; // 포인터로 저장하면 forward declaration 가능

  BypassComponent bypassComponent;
  juce::Label logoLabel;
  
  juce::Label companyLabel;
  MenuComponent menuComponent;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HeaderComponent)
};
