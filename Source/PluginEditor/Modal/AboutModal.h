#pragma once

#include <JuceHeader.h>
#include "../Provider/ScaleProvider.h"

class AboutModal : public juce::Component
{
  public:
  AboutModal(const ScaleProvider& sp);
  ~AboutModal() override;

  void showIn(juce::Component& parent);
  void close();
  
  void resized() override;
  void paint(juce::Graphics& g) override;
  void mouseUp(const juce::MouseEvent& e) override;

  
  private:
  const ScaleProvider& scaleProvider;
  juce::Label pluginNameLabel, pluginVersionLabel, companyNameLabel;
  
  juce::Component flexContainer;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AboutModal)
};
