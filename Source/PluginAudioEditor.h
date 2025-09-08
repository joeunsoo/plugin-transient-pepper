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
    WebSliderRelay       saturationDriveSliderRelay    { "saturationDriveSlider" };
    WebSliderRelay       emphasisSliderRelay    { "emphasisSlider" };
    WebSliderRelay       tiltSliderRelay    { "tiltSlider" };
    WebSliderRelay       inputGainSliderRelay    { "inputGainSlider" };
    WebSliderRelay       outputGainSliderRelay    { "outputGainSlider" };
    WebSliderRelay       dryWetSliderRelay    { "dryWetSlider" };
    
    WebControlParameterIndexReceiver controlParameterIndexReceiver;
    
    SinglePageBrowser webComponent { WebBrowserComponent::Options{}
            .withBackend (WebBrowserComponent::Options::Backend::webview2)
            .withWinWebView2Options (WebBrowserComponent::Options::WinWebView2{}
                                     .withUserDataFolder (File::getSpecialLocation (File::SpecialLocationType::tempDirectory)))
            .withNativeIntegrationEnabled()
            .withOptionsFrom (bypassToggleRelay)
            .withOptionsFrom (saturationDriveSliderRelay)
            .withOptionsFrom (emphasisSliderRelay)
            .withOptionsFrom (tiltSliderRelay)
            .withOptionsFrom (inputGainSliderRelay)
            .withOptionsFrom (outputGainSliderRelay)
            .withOptionsFrom (dryWetSliderRelay)
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
    WebSliderParameterAttachment       saturationDriveAttachment;
    WebSliderParameterAttachment       emphasisAttachment;
    WebSliderParameterAttachment       tiltAttachment;
    WebSliderParameterAttachment       inputGainAttachment;
    WebSliderParameterAttachment       outputGainAttachment;
    WebSliderParameterAttachment       dryWetAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginAudioEditor)
};
