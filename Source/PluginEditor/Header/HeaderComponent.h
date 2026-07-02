#pragma once

#include "../Provider/Providers.h"
#include "BypassComponent.h"
#include "MenuComponent.h"
#include <JuceHeader.h>

//==============================================================================
class HeaderComponent : public juce::Component
{
  public:
    explicit HeaderComponent(Providers &pv);
    ~HeaderComponent() override;

    void paint(juce::Graphics &g) override;
    void resized() override;

    //==============================================================================
  private:
    const ScaleProvider &scaleProvider;

    BypassComponent bypassComponent;
    juce::Label logoLabel;

    juce::Label companyLabel;
    MenuComponent menuComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HeaderComponent)
};
