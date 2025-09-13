/*
 ==============================================================================
 
 LicenseActivate.h
 Created: 13 Sep 2025 11:43:07am
 Author:  JoEunsoo
 
 ==============================================================================
 */

#pragma once
#include <JuceHeader.h>

class LicenseManager
{
  public:
  LicenseManager()
  {
    juce::PropertiesFile::Options options;
    options.applicationName     = "JoEunsoo";
    options.filenameSuffix      = "plist";
    options.osxLibrarySubFolder = "Preferences";
    options.storageFormat       = juce::PropertiesFile::storeAsBinary;
  
    propertiesFile = std::make_unique<juce::PropertiesFile>(options);
  }
  
  String getActivate()
  {
    if (propertiesFile == nullptr) return {};
    juce::String value = propertiesFile->getValue("TransientPepper", ""); // 기본값 10
    
    return value;
  }
  void setActivate(String email)
  {
    if (propertiesFile == nullptr) return;

    propertiesFile->setValue("TransientPepper", email);
    propertiesFile->saveIfNeeded();
  }
  
  void setDeactivate()
  {
    if (propertiesFile == nullptr) return;

    propertiesFile->setValue("TransientPepper", "");
    propertiesFile->saveIfNeeded();
  }
  
  private:
  std::unique_ptr<juce::PropertiesFile> propertiesFile;
  
  const juce::String secretKey = "f9a3d7b2e8c14f6a9d3e7b1c5a8f0d2e";
};
