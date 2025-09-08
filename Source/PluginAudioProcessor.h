/*
 ==============================================================================
 
 PluginAudioProcessor.h
 Created: 31 Aug 2025 10:22:01pm
 Author:  JoEunsoo
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>
#include "NamespaceParameterId.h"
#include "AntiAliasingFilter.h"
#include "DcOffsetFilter.h"
#include "Saturation.h"
#include "TiltEQ.h"

//==============================================================================
class PluginAudioProcessor  : public AudioProcessor
{
    public:
    //==============================================================================
    PluginAudioProcessor (AudioProcessorValueTreeState::ParameterLayout layout);
    ~PluginAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override {}
    
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
    
    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;
    using AudioProcessor::processBlock;
    
    //==============================================================================
    const String getName() const override        { return JucePlugin_Name; }
    
    bool acceptsMidi() const override            { return false; }
    bool producesMidi() const override           { return false; }
    bool isMidiEffect() const override           { return false; }
    double getTailLengthSeconds() const override { return 0.0; }
    
    //==============================================================================
    int getNumPrograms() override                        { return 1; }
    int getCurrentProgram() override                     { return 0; }
    void setCurrentProgram (int) override                {}
    const String getProgramName (int) override           { return {}; }
    void changeProgramName (int, const String&) override {}
    
    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    struct Parameters
    {
        public:
        explicit Parameters (AudioProcessorValueTreeState::ParameterLayout& layout)
        :
        bypass (addToLayout<AudioParameterBool> (layout, ID::bypass, "Bypass", false)),
        saturationDrive (addToLayout<AudioParameterFloat> (layout,
                                                           ID::saturationDrive,
                                                           "Saturation Drive",
                                                           NormalisableRange<float> { 0.0f, 100.0f, 1.0f, 1.0f },
                                                           50.0f,
                                                           "%",
                                                           juce::AudioProcessorParameter::genericParameter,
                                                           [](float value, int) {
            return juce::String(value, 1) + " %";  // << 표시될 문자열
        },
                                                           [](const juce::String& text) {
            return text.dropLastCharacters(2).getFloatValue(); // "12 %" → 12
        }
                                                           )),
        emphasis (addToLayout<AudioParameterFloat> (layout,
                                                    ID::emphasis,
                                                    "Emphasis",
                                                    NormalisableRange<float> { -12.0f, 12.0f, 0.5f, 1.0f },
                                                    0.0f,
                                                    "dB",
                                                    juce::AudioProcessorParameter::genericParameter,
                                                    [](float value, int) {
            return juce::String(value, 1) + " dB";  // << 표시될 문자열
        },
                                                    [](const juce::String& text) {
            return text.dropLastCharacters(3).getFloatValue(); // "12 dB" → 12
        }
                                                    )),
        tilt (addToLayout<AudioParameterFloat> (layout,
                                                ID::tilt,
                                                "Tone/Tilt",
                                                NormalisableRange<float> { -12.0f, 12.0f, 0.5f, 1.0f },
                                                0.0f,
                                                "dB",
                                                juce::AudioProcessorParameter::genericParameter,
                                                [](float value, int) {
            return juce::String(value, 1) + " dB";  // << 표시될 문자열
        },
                                                [](const juce::String& text) {
            return text.dropLastCharacters(3).getFloatValue(); // "12 dB" → 12
        }
                                                )),
        inputGain (addToLayout<AudioParameterFloat> (layout,
                                                     ID::inputGain,
                                                     "Input Gain",
                                                     NormalisableRange<float> { -24.0f, 24.0f, 0.5f, 1.0f },
                                                     0.0f,
                                                     "dB",
                                                     juce::AudioProcessorParameter::genericParameter,
                                                     [](float value, int) {
            return juce::String(value, 1) + " dB";  // << 표시될 문자열
        },
                                                     [](const juce::String& text) {
            return text.dropLastCharacters(3).getFloatValue(); // "12 dB" → 12
        }
                                                     )),
        outputGain (addToLayout<AudioParameterFloat> (layout,
                                                      ID::outputGain,
                                                      "Output Gain",
                                                      NormalisableRange<float> { -24.0f, 24.0f, 0.5f, 1.0f },
                                                      0.0f,
                                                      "dB",
                                                      juce::AudioProcessorParameter::genericParameter,
                                                      [](float value, int) {
            return juce::String(value, 1) + " dB";  // << 표시될 문자열
        },
                                                      [](const juce::String& text) {
            return text.dropLastCharacters(3).getFloatValue(); // "12 dB" → 12
        }
                                                      )),
        dryWet (addToLayout<AudioParameterFloat> (layout,
                                                  ID::dryWet,
                                                  "Dry/Wet",
                                                  NormalisableRange<float> { 0.0f, 100.0f, 1.0f, 1.0f },
                                                  100.0f,
                                                  "%",
                                                  juce::AudioProcessorParameter::genericParameter,
                                                  [](float value, int) {
            return juce::String(value, 1) + " %";  // << 표시될 문자열
        },
                                                  [](const juce::String& text) {
            return text.dropLastCharacters(2).getFloatValue(); // "12 %" → 12
        }
                                                  ))
        {
        }
        
        AudioParameterBool&   bypass;
        AudioParameterFloat& saturationDrive;
        AudioParameterFloat& emphasis;
        AudioParameterFloat& tilt;
        AudioParameterFloat& inputGain;
        AudioParameterFloat& outputGain;
        AudioParameterFloat& dryWet;
        
        private:
        template <typename Param>
        static void add (AudioProcessorParameterGroup& group, std::unique_ptr<Param> param)
        {
            group.addChild (std::move (param));
        }
        
        template <typename Param>
        static void add (AudioProcessorValueTreeState::ParameterLayout& group, std::unique_ptr<Param> param)
        {
            group.add (std::move (param));
        }
        
        template <typename Param, typename Group, typename... Ts>
        static Param& addToLayout (Group& layout, Ts&&... ts)
        {
            auto param = std::make_unique<Param> (std::forward<Ts> (ts)...);
            auto& ref = *param;
            add (layout, std::move (param));
            return ref;
        }
    };
    
    double sampleRate = 44100.0;
    
    Parameters parameters;
    AudioProcessorValueTreeState state;
    
    SaturationProcessor<float> saturation;
    dsp::Gain<float> inputGain;
    dsp::Gain<float> outputGain;
    
    TiltEQProcessor<float> tiltEQ;
    
    TiltEQProcessor<float> preEQ;
    TiltEQProcessor<float> postEQ;
    
    DcOffsetFilter<float> dcBlocker;
    AntiAliasingFilter antiAliasingFilter;
    
    juce::dsp::DryWetMixer<float> dryWetMixer;
    
    int windowScale;

    private:
    juce::ApplicationProperties appProperties;
    juce::PropertiesFile* props = nullptr; // 소유권은 ApplicationProperties가 관리

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginAudioProcessor)
    
};
