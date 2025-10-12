#pragma once

#include <JuceHeader.h>
#include "../Provider/Providers.h"
#include "MenuComponent.h"
#include "BypassComponent.h"

//==============================================================================
class HeaderComponent : public juce::Component
{
  public:
  explicit HeaderComponent(Providers& pv);
  ~HeaderComponent() override;
  
  void paint(juce::Graphics& g) override;
  void resized() override;
  
  //==============================================================================
  private:
  const ScaleProvider& scaleProvider;

  BypassComponent bypassComponent;
  juce::Label logoLabel;
  
  juce::Label companyLabel;
  MenuComponent menuComponent;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HeaderComponent)
};
