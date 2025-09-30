#pragma once

#include <JuceHeader.h>
#include "AudioProcessor/PluginAudioProcessor.h"
#include "LicenseManager.h"

class PluginWrapper  : public PluginAudioProcessor
{
  public:
  //==============================================================================
  PluginWrapper();
  ~PluginWrapper();
  //==============================================================================
  bool hasEditor() const override               { return true; }
  AudioProcessorEditor* createEditor() override;
  //==============================================================================

  LicenseManager licenseManager;
  int windowScale;
  
  private:
  //==============================================================================
  juce::ApplicationProperties appProperties;
  juce::PropertiesFile* props = nullptr; // 소유권은 ApplicationProperties가 관리

};

