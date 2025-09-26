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
  
  void sendActivationRequest(String userEmail,String userPassword)
  {
    juce::URL url ("http://localhost:3000/api/productActivation");
    
    juce::DynamicObject::Ptr jsonObj = new juce::DynamicObject();
    jsonObj->setProperty ("userEmail", userEmail);
    jsonObj->setProperty ("userPassword", userPassword);
    jsonObj->setProperty ("productCode", PLUGIN_CODE);

    juce::var jsonVar = juce::var (jsonObj.get());
    juce::String postData = juce::JSON::toString (jsonVar);
    url = url.withPOSTData (postData);

    StringPairArray responseHeaders;
    int statusCode = 0;
    
    auto responseStream =
    url.createInputStream (URL::InputStreamOptions (URL::ParameterHandling::inAddress)
                           .withConnectionTimeoutMs (10000)
                           .withResponseHeaders (&responseHeaders)
                           .withStatusCode (&statusCode)
                           .withExtraHeaders ("Content-Type: application/json\r\n")); // 또는 application/json
    
    if (responseStream != nullptr)
    {
      juce::String response = responseStream->readEntireStreamAsString();
      
      // JSON 파싱
      juce::var json = juce::JSON::parse (response);
      if (json.isObject())
      {
        auto& obj = *json.getDynamicObject();
        return obj;

        // 예: "status" 필드 읽기
        juce::String status = obj.getProperty ("status").toString();
        juce::String message = obj.getProperty ("message").toString();
        DBG ("status: " << status << ", message: " << message);
      }
      else
      {
        juce::DynamicObject::Ptr errorNoJSON = new juce::DynamicObject();
        jsonObj->setProperty ("status", 500);
        jsonObj->setProperty ("message", "Failed to parse JSON or not an object");

        return errorNoJSON;
      }
    }
    else
    {
      juce::DynamicObject::Ptr errorNull = new juce::DynamicObject();
      jsonObj->setProperty ("status", 500);
      jsonObj->setProperty ("message", "Response stream is null — request failed or timeout");

      return errorNull;
    }
  }
  
  String getActivate()
  {
    if (propertiesFile == nullptr) return {};
    
    auto encId = encryptString("TransientPepperLicence");
    juce::String value = propertiesFile->getValue(encId, ""); // 기본값 10
    
    if (value.isEmpty()) return {};
    return decryptString(value);
  }
  
  bool isActivate()
  {
    if (getActivate().length() > 0) {
      return true;
    }
    return false;
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
  
  int getTrialDays()
  {
    int64 trialTimestamp = getTrial();
    int64 nowMs = juce::Time::getCurrentTime().toMilliseconds(); // 현재 시간
    
    // trial 기간 (예: 30일)
    constexpr int trialPeriodDays = 30;
    
    // 경과 일수 계산
    int64 elapsedDays = (nowMs - trialTimestamp) / (1000 * 60 * 60 * 24);
    
    // 남은 일수
    int64 remainingDays = trialPeriodDays - elapsedDays;
    if (remainingDays < 0)
      remainingDays = 0; // 음수 방지
    
    return (int) remainingDays;
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
  
  // 트라이얼 유효 유무 확인,
  // 트라이얼 시작되지 않은 경우에도 true
  // 종료시간 지나면 true
  // 트라이얼 시작하고 종료시간 안지나면 false
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
  juce::String encryptString(const juce::String& text)
  {
    return text;
  }
  juce::String decryptString(const juce::String& base64Text)
  {
    return base64Text;
  }
  
  /*
   // ---------------- XOR + Base64 ----------------
   
   juce::MemoryBlock base64Decode(const juce::String& text)
   {
   juce::MemoryOutputStream out;
   juce::Base64::convertFromBase64(out, text);
   return out.getMemoryBlock();
   }
   
   juce::String encryptString(const juce::String& text)
   {
   juce::MemoryBlock mb(text.getNumBytesAsUTF8());
   const char* src = text.toRawUTF8();
   
   #pragma clang diagnostic push
   #pragma clang diagnostic ignored "-Wconversion"  // 경고 종류
   #pragma clang diagnostic ignored "-Wsign-conversion"
   #pragma clang diagnostic ignored "-Wsign-compare"
   for (int i = 0; i < mb.getSize(); ++i)
   mb[i] = src[i] ^ secretKey[i % secretKey.length()];
   #pragma clang diagnostic  pop
   
   return juce::Base64::toBase64(mb.getData(), mb.getSize());
   }
   
   juce::String decryptString(const juce::String& base64Text)
   {
   juce::MemoryBlock block = base64Decode(base64Text);
   juce::MemoryBlock out(block.getSize());
   
   #pragma clang diagnostic push
   #pragma clang diagnostic ignored "-Wconversion"  // 경고 종류
   #pragma clang diagnostic ignored "-Wsign-conversion"
   #pragma clang diagnostic ignored "-Wsign-compare"
   for (int i = 0; i < block.getSize(); ++i)
   out[i] = block[i] ^ secretKey[i % secretKey.length()];
   #pragma clang diagnostic pop
   
   return juce::String::fromUTF8((const char*)out.getData(), (int)out.getSize());
   }
   */
  
  std::unique_ptr<juce::PropertiesFile> propertiesFile;
  
  const juce::String secretKey = "f9a3d7b2e8c14f6a9d3e7b1c5a8f0d2e";
};
