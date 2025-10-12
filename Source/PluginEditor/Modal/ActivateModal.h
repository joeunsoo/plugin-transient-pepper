#pragma once

#include <JuceHeader.h>
#include "../Provider/ScaleProvider.h"
#include "../Provider/LicenseProvider.h"
#include "DeactivateComponent.h"
#include "LoginComponent.h"
#include "ModalLookAndFeel.h"

// Forward declaration
class PluginEditor;

class ActivateModal : public juce::Component
{
  public:
  ActivateModal(const ScaleProvider& sp,
                LicenseProvider& lp);
  ~ActivateModal() override;

  void showIn(juce::Component& parent);
  void close();
  
  void resized() override;
  void paint(juce::Graphics& g) override;
  void mouseUp(const juce::MouseEvent& e) override;

  
  private:
  const ScaleProvider& scaleProvider;
  LicenseProvider& licenseProvider;

  ModalLookAndFeel modalLaf;

  DeactivateComponent deactivateComponent;
  LoginComponent loginComponent;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ActivateModal)
};
