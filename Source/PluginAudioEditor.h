/*
 ==============================================================================
 
 PluginAudioProcessorEditor.h
 Created: 31 Aug 2025 10:18:34pm
 Author:  JoEunsoo
 
 ==============================================================================
 */

#pragma once

#if JUCE_WINDOWS
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>  // HWND, SendMessage 등 정의
#endif

#include <JuceHeader.h>
#include "DemoUtilities.h"
#include "PluginAudioProcessor.h"

extern const String localDevServerAddress;

std::optional<WebBrowserComponent::Resource> getResource (const String& url);

//==============================================================================
struct SinglePageBrowser : WebBrowserComponent
{
  using WebBrowserComponent::WebBrowserComponent;

  SinglePageBrowser()
  {
      setWantsKeyboardFocus(false); // 포커스 받지 않음
  }
  bool keyPressed(const KeyPress& key) override
  {
      return false; // 항상 무시
  }

  // Prevent page loads from navigating away from our single page web app
  bool pageAboutToLoad (const String& newURL) override;
  
};

//==============================================================================
class PluginAudioEditor  : public AudioProcessorEditor, private Timer
{
  public:
  explicit PluginAudioEditor (PluginAudioProcessor&);
  
  std::optional<WebBrowserComponent::Resource> getResource (const String& url);
  
  //==============================================================================
  void paint (Graphics&) override;
  void resized() override;

  bool keyPressed(const KeyPress& key) override
  {
      return false; // 항상 무시
  }

  int getControlParameterIndex (Component&) override
  {
    return controlParameterIndexReceiver.getControlParameterIndex();
  }
  
  void timerCallback() override {
    static constexpr size_t numFramesBuffered = 5;

    SpinLock::ScopedLockType lock { processorRef.peakDataLock };

    Array<var> frame;

    for (size_t i = 0; i < processorRef.analysisData.size(); ++i)
        frame.add (processorRef.analysisData[i]);

    analysisDataFrames.push_back (std::move (frame));

    while (analysisDataFrames.size() > numFramesBuffered)
      analysisDataFrames.pop_front();

    static int64 callbackCounter = 0;

    if (   analysisDataFrames.size() == numFramesBuffered
        && callbackCounter++ % (int64) numFramesBuffered)
    {
        webComponent.emitEventIfBrowserIsVisible ("analysisData", var{});
    }
  }
  
  void setScale(int scale);
  
  private:
  PluginAudioProcessor& processorRef;
  
  WebToggleButtonRelay bypassToggleRelay      { "bypassToggle" };
#if ADVANCED
  WebComboBoxRelay     generatorTypeComboRelay { "generatorTypeCombo" };
#endif
  WebSliderRelay       attackSliderRelay    { "attackSlider" };
  WebSliderRelay       releaseSliderRelay    { "releaseSlider" };

  WebSliderRelay       thresholdSliderRelay    { "thresholdSlider" };

  WebToggleButtonRelay bpfPowerToggleRelay      { "bpfPowerToggle" };
  WebSliderRelay       bpfFrequencySliderRelay    { "bpfFrequencySlider" };
  WebToggleButtonRelay sidechainListenToggleRelay      { "sidechainListenToggle" };

  WebSliderRelay       tiltSliderRelay    { "tiltSlider" };
  WebSliderRelay       midSideSliderRelay    { "midSideSlider" };

  WebSliderRelay       noiseLevelGainSliderRelay    { "noiseLevelGainSlider" };
  WebSliderRelay       outputGainSliderRelay    { "outputGainSlider" };
  WebSliderRelay       dryWetSliderRelay    { "dryWetSlider" };
  WebToggleButtonRelay wetSoloToggleRelay      { "wetSoloToggle" };
  WebToggleButtonRelay linkChannelsToggleRelay      { "linkChannelsToggle" };
#if ADVANCED
  WebSliderRelay       fastAttackSliderRelay    { "fastAttackSlider" };
  WebSliderRelay       fastReleaseSliderRelay    { "fastReleaseSlider" };
  WebSliderRelay       slowAttackSliderRelay    { "slowAttackSlider" };
  WebSliderRelay       slowReleaseSliderRelay    { "slowReleaseSlider" };
#endif
  WebControlParameterIndexReceiver controlParameterIndexReceiver;
  
  SinglePageBrowser webComponent { WebBrowserComponent::Options{}
      .withBackend (WebBrowserComponent::Options::Backend::webview2)
      .withWinWebView2Options (WebBrowserComponent::Options::WinWebView2{}
                               .withUserDataFolder (File::getSpecialLocation (File::SpecialLocationType::tempDirectory)))
      .withNativeIntegrationEnabled()
      .withOptionsFrom (bypassToggleRelay)
#if ADVANCED
      .withOptionsFrom (generatorTypeComboRelay)
#endif
      .withOptionsFrom (attackSliderRelay)
      .withOptionsFrom (releaseSliderRelay)

      .withOptionsFrom (thresholdSliderRelay)
      .withOptionsFrom (bpfPowerToggleRelay)
      .withOptionsFrom (bpfFrequencySliderRelay)
      .withOptionsFrom (sidechainListenToggleRelay)

      .withOptionsFrom (tiltSliderRelay)
      .withOptionsFrom (midSideSliderRelay)

      .withOptionsFrom (noiseLevelGainSliderRelay)
      .withOptionsFrom (outputGainSliderRelay)
      .withOptionsFrom (dryWetSliderRelay)
      .withOptionsFrom (wetSoloToggleRelay)
      .withOptionsFrom (linkChannelsToggleRelay)
#if ADVANCED
    .withOptionsFrom (fastAttackSliderRelay)
    .withOptionsFrom (fastReleaseSliderRelay)
    .withOptionsFrom (slowAttackSliderRelay)
    .withOptionsFrom (slowReleaseSliderRelay)
#endif
      .withOptionsFrom (controlParameterIndexReceiver)
      .withNativeFunction ("isDebug", [](auto& var /*unused*/, auto complete) {
#if DEBUG
        complete(true);
#else
        complete(false);
#endif
      })
      .withNativeFunction ("setWindowScale", [this](auto& var, auto complete /*unused*/) {
        setScale(var[0]);
      })
      .withNativeFunction ("getWindowScale", [this](auto& var /*unused*/, auto complete) {
        complete (juce::String(processorRef.windowScale));
      })
      .withNativeFunction ("getActivate", [this](auto& var /*unused*/, auto complete) {
        juce::String activate = juce::String(processorRef.licenseManager.getActivate());
        int64 trial = processorRef.licenseManager.getTrial();
        auto obj = new juce::DynamicObject();
        obj->setProperty("activate", activate);
        obj->setProperty("trial", trial);
        complete (obj);
      })
      .withNativeFunction ("setActivate", [this](auto& var, auto complete) {
        processorRef.licenseManager.setActivate(var[0].toString());
        processorRef.activated = true;
        complete ("done");
      })
      .withNativeFunction ("setDeactivate", [this](auto& var /*unused*/, auto complete) {
        processorRef.licenseManager.setDeactivate();
        processorRef.activated = false;
        complete ("done");
      })
      .withNativeFunction ("startTrial", [this](auto& var /*unused*/, auto complete) {
        int64 value = processorRef.licenseManager.startTrial();
        processorRef.activated = true;
        complete (value);
      })
      .withNativeFunction ("getTrial", [this](auto& var /*unused*/, auto complete) {
        int64 value = processorRef.licenseManager.getTrial();
        complete (value);
      })
      .withNativeFunction ("visitWebsite", [](auto& var, auto complete) {
        const URL newUrl = URL (var[0].toString());
        if (newUrl.isWellFormed())
          newUrl.launchInDefaultBrowser();
        complete ("done");
      })
      .withNativeFunction ("pressSpace", [](auto& var /*unused*/, auto complete /*unused*/) {
         // DBG(1);
      })
      .withResourceProvider ([this] (const auto& url) {
        return getResource (url);
      },
                             URL { localDevServerAddress }.getOrigin()) };
  
  WebToggleButtonParameterAttachment bypassAttachment;
#if ADVANCED
  WebComboBoxParameterAttachment       generatorTypeAttachment;
#endif
  WebSliderParameterAttachment       attackAttachment;
  WebSliderParameterAttachment       releaseAttachment;

  WebSliderParameterAttachment       thresholdAttachment;
  WebToggleButtonParameterAttachment       bpfPowerAttachment;
  WebSliderParameterAttachment       bpfFrequencyAttachment;
  WebToggleButtonParameterAttachment       sidechainListenAttachment;

  WebSliderParameterAttachment       tiltAttachment;
  WebSliderParameterAttachment       midSideAttachment;

  WebSliderParameterAttachment       noiseLevelGainAttachment;
  WebSliderParameterAttachment       outputGainAttachment;
  WebSliderParameterAttachment       dryWetAttachment;
  WebToggleButtonParameterAttachment       wetSoloAttachment;
  WebToggleButtonParameterAttachment       linkChannelsAttachment;
  
#if ADVANCED
  WebSliderParameterAttachment       fastAttackAttachment;
  WebSliderParameterAttachment       fastReleaseAttachment;
  WebSliderParameterAttachment       slowAttackAttachment;
  WebSliderParameterAttachment       slowReleaseAttachment;
#endif
  std::deque<Array<var>> analysisDataFrames;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginAudioEditor)
};
