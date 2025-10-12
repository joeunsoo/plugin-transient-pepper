#pragma once

#include <JuceHeader.h>
#include "../Provider/Providers.h"
#include "MenuLookAndFeel.h"

//==============================================================================
class MenuComponent : public juce::Component
{
  public:
  MenuComponent(Providers& pv);
  ~MenuComponent() override;
  
  void paint(juce::Graphics& g) override;
  void resized() override;
  
  //==============================================================================
  private:
  EditorProvider& editorProvider;
  const ScaleProvider& scaleProvider;
  ScaleController& scaleController;
  LicenseProvider& licenseProvider;

  MenuLookAndFeel menuLaF;

  juce::DrawableButton menuButton {
    "menuButton",
    juce::DrawableButton::ImageFitted
  };
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MenuComponent)
};
