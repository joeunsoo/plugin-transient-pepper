#pragma once

#include "AudioProcessor/PluginAudioProcessor.h"
#include "LicenseManager.h"
#include <JuceHeader.h>

class PluginWrapper : public PluginAudioProcessor {
public:
  //==============================================================================
  PluginWrapper();
  ~PluginWrapper() override;
  //==============================================================================
  bool hasEditor() const override { return true; }
  AudioProcessorEditor *createEditor() override;
  //==============================================================================

  LicenseManager licenseManager;
  int windowScale;

private:
  //==============================================================================
  juce::ApplicationProperties appProperties;
  juce::PropertiesFile *props = nullptr; // 소유권은 ApplicationProperties가 관리
};
