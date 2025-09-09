/*
 ==============================================================================
 
 PluginAudioProcessorEditor.h
 Created: 31 Aug 2025 10:18:34pm
 Author:  JoEunsoo
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>
#include "DemoUtilities.h"
#include "PluginAudioProcessor.h"

extern const String localDevServerAddress;

std::optional<WebBrowserComponent::Resource> getResource (const String& url);

//==============================================================================
struct SinglePageBrowser : WebBrowserComponent
{
  using WebBrowserComponent::WebBrowserComponent;
  
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
  
  int getControlParameterIndex (Component&) override
  {
    return controlParameterIndexReceiver.getControlParameterIndex();
  }
  
  void timerCallback() override {
    static constexpr size_t numFramesBuffered = 5;

    SpinLock::ScopedLockType lock { processorRef.peakDataLock };

    Array<var> frame;

    for (size_t i = 0; i < processorRef.spectrumData.size(); ++i)
        frame.add (processorRef.spectrumData[i]);

    spectrumDataFrames.push_back (std::move (frame));

    while (spectrumDataFrames.size() > numFramesBuffered)
        spectrumDataFrames.pop_front();

    static int64 callbackCounter = 0;

    if (   spectrumDataFrames.size() == numFramesBuffered
        && callbackCounter++ % (int64) numFramesBuffered)
    {
        webComponent.emitEventIfBrowserIsVisible ("spectrumData", var{});
    }
  }
  
  void setScale(int scale);
  
  private:
  PluginAudioProcessor& processorRef;
  
  WebToggleButtonRelay bypassToggleRelay      { "bypassToggle" };
  WebSliderRelay       tiltSliderRelay    { "tiltSlider" };
  WebSliderRelay       midSideSliderRelay    { "midSideSlider" };
  WebSliderRelay       emphasisSliderRelay    { "emphasisSlider" };
  WebSliderRelay       thresholdSliderRelay    { "thresholdSlider" };
  WebSliderRelay       attackSliderRelay    { "attackSlider" };
  WebSliderRelay       releaseSliderRelay    { "releaseSlider" };
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
      .withOptionsFrom (tiltSliderRelay)
      .withOptionsFrom (midSideSliderRelay)
      .withOptionsFrom (emphasisSliderRelay)
      .withOptionsFrom (thresholdSliderRelay)
      .withOptionsFrom (attackSliderRelay)
      .withOptionsFrom (releaseSliderRelay)
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
      .withNativeFunction ("setWindowScale", [this](auto& var, auto complete) {
        setScale(var[0]);
      })
      .withNativeFunction ("getWindowScale", [this](auto& var, auto complete) {
        complete (juce::String(processorRef.windowScale));
      })
      .withNativeFunction ("sayHello", [this](auto& var, auto complete) {
        juce::String value = juce::String(processorRef.outputGain.getGainDecibels());
        complete ("outputGain value is " + value);
        // complete ("Hello " + var[0].toString());
      })
      .withNativeFunction ("visitWebsite", [](auto& var, auto complete) {
        const URL newUrl = URL (var[0].toString());
        if (newUrl.isWellFormed())
          newUrl.launchInDefaultBrowser();
        complete ("done");
      })
      .withResourceProvider ([this] (const auto& url) {
        return getResource (url);
      },
                             URL { localDevServerAddress }.getOrigin()) };
  
  WebToggleButtonParameterAttachment bypassAttachment;
  WebSliderParameterAttachment       tiltAttachment;
  WebSliderParameterAttachment       midSideAttachment;
  WebSliderParameterAttachment       emphasisAttachment;
  WebSliderParameterAttachment       thresholdAttachment;
  WebSliderParameterAttachment       attackAttachment;
  WebSliderParameterAttachment       releaseAttachment;
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
  std::deque<Array<var>> spectrumDataFrames;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginAudioEditor)
};
