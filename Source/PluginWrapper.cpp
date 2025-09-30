#include "PluginWrapper.h"
#include "PluginEditor/PluginEditor.h"

//==============================================================================
PluginWrapper::PluginWrapper()
    : PluginAudioProcessor ({})
{
  // PropertiesFile 옵션 설정
  juce::PropertiesFile::Options options;
  options.applicationName     = "preferences";
  options.filenameSuffix      = ".xml";
  options.folderName          = PREF_FOLDER_NAME; // macOS: ~/Library/Application Support/JoEunsoo/RustyTone.settings
  options.osxLibrarySubFolder = "Application Support";
  options.storageFormat       = juce::PropertiesFile::storeAsXML;
  
  // ApplicationProperties 객체를 통해 관리
  appProperties.setStorageParameters(options);
  
  // PropertiesFile 가져오기
  props = appProperties.getUserSettings();
  
  // 값 불러오기
  windowScale  = props->getIntValue("windowScale", 100);
  
  // 라이센스 검사
  bool activated = false;
  if (licenseManager.getActivate().length() > 0) {
    activated = true;
  }
  if (!licenseManager.isTrialExpired()) {
    activated = true;
  }

  setActivated(activated);
}

PluginWrapper::~PluginWrapper()
{
  props->setValue("windowScale", windowScale);
  props->saveIfNeeded();
}

AudioProcessorEditor* PluginWrapper::createEditor()
{
  return new PluginEditor (*this);
}
