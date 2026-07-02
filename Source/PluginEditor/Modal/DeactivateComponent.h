#pragma once

#include "../Provider/LicenseProvider.h"
#include "../Provider/ScaleProvider.h"
#include <JuceHeader.h>

// Forward declaration
class ActivateModal;

class DeactivateComponent : public juce::Component {
public:
  DeactivateComponent(ActivateModal &modal, const ScaleProvider &sp, LicenseProvider &lp);
  ~DeactivateComponent() override;

  void resized() override;
  void paint(juce::Graphics &g) override;

private:
  ActivateModal &modalRef; // 포인터로 저장하면 forward declaration 가능
  const ScaleProvider &scaleProvider;
  LicenseProvider &licenseProvider;

  juce::Component flexContainer;
  juce::Label pluginNameLabel, accountEmailLabel;
  juce::TextButton deactivateButton;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeactivateComponent)
};
