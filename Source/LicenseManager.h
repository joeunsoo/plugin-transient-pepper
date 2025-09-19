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
    options.applicationName     = "com.joeunsoo";
    options.filenameSuffix      = "plist";
    options.osxLibrarySubFolder = "Preferences";
    options.storageFormat       = juce::PropertiesFile::storeAsBinary;
    
    propertiesFile = std::make_unique<juce::PropertiesFile>(options);
  }
  
  String getActivate()
  {
    if (propertiesFile == nullptr) return {};
    
    auto encId = encryptString("TransientPepperLicence");
    juce::String value = propertiesFile->getValue(encId, ""); // 기본값 10
    
    if (value.isEmpty()) return {};
    return decryptString(value);
  }
  
  void setActivate(String email)
  {
    if (propertiesFile == nullptr) return;
    
    auto encId = encryptString("TransientPepperLicence");
    auto encEmail = encryptString(email);
    propertiesFile->setValue(encId, encEmail);
    propertiesFile->saveIfNeeded();
  }
  
  void setDeactivate()
  {
    if (propertiesFile == nullptr) return;
    
    auto encId = encryptString("TransientPepperLicence");
    propertiesFile->setValue(encId, "");
    propertiesFile->saveIfNeeded();
  }
  
  int64 getTrial()
  {
    if (propertiesFile == nullptr) return 0;
    
    auto encId = encryptString("TransientPepperTrial");
    juce::String enc = propertiesFile->getValue(encId, "");
    
    if (enc.isEmpty()) return 0;
    juce::String decrypted = decryptString(enc);
    return decrypted.getLargeIntValue();
  }
  
  int64 startTrial()
  {
    if (propertiesFile == nullptr)
      return 0;
    
    int64 timestamp = juce::Time::getCurrentTime().toMilliseconds(); // 1970 기준 ms
    
    auto encId = encryptString("TransientPepperTrial");
    auto enc = encryptString(juce::String(timestamp));
    
    propertiesFile->setValue(encId, enc);
    propertiesFile->setValue("TransientPepper", timestamp);
    propertiesFile->saveIfNeeded();
    return timestamp;
  }
  
  bool isTrialExpired()
  {
      int64 startTime = getTrial(); // 복호화된 트라이얼 시작 timestamp
      if (startTime == 0)
          return true; // 트라이얼이 시작되지 않았으면 만료로 간주

      int64 now = juce::Time::getCurrentTime().toMilliseconds();
      const int64 THIRTY_DAYS_MS = int64(30) * 24 * 60 * 60 * 1000; // 30일을 ms로

      return (now - startTime) > THIRTY_DAYS_MS;
  }

  private:
  
  // ---------------- XOR + Base64 ----------------
  juce::String encryptString(const juce::String& text)
  {
      juce::MemoryBlock mb(text.getNumBytesAsUTF8());
      const char* src = text.toRawUTF8();

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconversion"  // 경고 종류
      for (int i = 0; i < mb.getSize(); ++i)
          mb[i] = src[i] ^ secretKey[i % secretKey.length()];
#pragma clang diagnostic pop

      return juce::Base64::toBase64(mb.getData(), mb.getSize());
  }

  juce::MemoryBlock base64Decode(const juce::String& text)
  {
      juce::MemoryOutputStream out;
      juce::Base64::convertFromBase64(out, text);
      return out.getMemoryBlock();
  }

  juce::String decryptString(const juce::String& base64Text)
  {
      juce::MemoryBlock block = base64Decode(base64Text);
      juce::MemoryBlock out(block.getSize());

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconversion"  // 경고 종류
      for (int i = 0; i < block.getSize(); ++i)
          out[i] = block[i] ^ secretKey[i % secretKey.length()];
#pragma clang diagnostic pop

      return juce::String::fromUTF8((const char*)out.getData(), (int)out.getSize());
  }
  
  std::unique_ptr<juce::PropertiesFile> propertiesFile;
  
  const juce::String secretKey = "f9a3d7b2e8c14f6a9d3e7b1c5a8f0d2e";
};
