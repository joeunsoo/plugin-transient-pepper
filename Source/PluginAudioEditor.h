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
  WebSliderRelay       inputGainSliderRelay    { "inputGainSlider" };
  WebSliderRelay       outputGainSliderRelay    { "outputGainSlider" };
  WebSliderRelay       dryWetSliderRelay    { "dryWetSlider" };
  WebToggleButtonRelay wetSoloToggleRelay      { "wetSoloToggle" };
  WebToggleButtonRelay linkChannelsToggleRelay      { "linkChannelsToggle" };
  
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
      .withOptionsFrom (inputGainSliderRelay)
      .withOptionsFrom (outputGainSliderRelay)
      .withOptionsFrom (dryWetSliderRelay)
      .withOptionsFrom (wetSoloToggleRelay)
      .withOptionsFrom (linkChannelsToggleRelay)
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
  WebSliderParameterAttachment       inputGainAttachment;
  WebSliderParameterAttachment       outputGainAttachment;
  WebSliderParameterAttachment       dryWetAttachment;
  WebToggleButtonParameterAttachment       wetSoloAttachment;
  WebToggleButtonParameterAttachment       linkChannelsAttachment;
  
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginAudioEditor)
};
