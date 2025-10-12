#pragma once

#include <JuceHeader.h>
#include "../Provider/LicenseProvider.h"

// Forward declaration
class ActivateModal;

class TrialComponent : public juce::Component
{
  public:
  TrialComponent(ActivateModal& modal,
                 LicenseProvider& lp);
  ~TrialComponent() override;

  void resized() override;
  void paint(juce::Graphics& g) override;

  
  private:
  ActivateModal& modalRef; // 포인터로 저장하면 forward declaration 가능
  LicenseProvider& licenseProvider;

  juce::TextButton trialButton;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TrialComponent)
};
