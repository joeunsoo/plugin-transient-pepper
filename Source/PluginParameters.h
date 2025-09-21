/*
 ==============================================================================
 
 PluginParameters.h
 Created: 8 Sep 2025 6:33:58pm
 Author:  JoEunsoo
 
 ==============================================================================
 */

#pragma once
#include "NamespaceParameterId.h"


struct Parameters {
  public:
  explicit Parameters (AudioProcessorValueTreeState::ParameterLayout& layout)
  :
  bypass (addToLayout<AudioParameterBool> (layout, ID::bypass, "Bypass", false)),
#if ADVANCED
  generatorType (addToLayout<AudioParameterChoice> (layout,
                                                 ID::generatorType,
                                                 "Noise type",
                                                 StringArray { "Air", "Bitcrush" },
                                                 0)),
#endif
  attack (addToLayout<AudioParameterFloat> (layout,
                                            ID::attack,
                                            "Attack",
                                            NormalisableRange<float> { 0.001f, 0.1000f, 0.001f, 1.0f },
                                            0.0500f,
                                            "ms",
                                            juce::AudioProcessorParameter::genericParameter,
                                            [](float value, int) { return msToString(value * 1000.0f); },
                                            [](const juce::String& text) { return stringToMs(text); }
                                            )),
  
  release (addToLayout<AudioParameterFloat> (layout,
                                             ID::release,
                                             "Release",
                                             NormalisableRange<float> { 0.001f, 0.1000f, 0.001f, 1.0f },
                                             0.0500f,
                                             "ms",
                                             juce::AudioProcessorParameter::genericParameter,
                                             [](float value, int) { return msToString(value * 1000.0f); },
                                             [](const juce::String& text) { return stringToMs(text); }
                                             )),
  
  threshold (addToLayout<AudioParameterFloat> (layout,
                                               ID::threshold,
                                               "Threshold",
                                               NormalisableRange<float> { -40.0f, 0.0f, 0.1f, 1.0f },
                                               -20.0f,
                                               "dB",
                                               juce::AudioProcessorParameter::genericParameter,
                                               [](float value, int) { return dBToString(value); },
                                               [](const juce::String& text) { return stringToDB(text); }
                                               )),
  
  bpfPower (addToLayout<AudioParameterBool> (layout, ID::bpfPower, "BPF On/Off", false)),
  bpfFrequency (addToLayout<AudioParameterFloat> (layout,
                                                  ID::bpfFrequency,
                                                  "BPF Freq",
                                                  NormalisableRange<float> { 50.0f, 12000.0f, 0.1f, 0.27375f },
                                                  1000.0f,
                                                  "Hz",
                                                  juce::AudioProcessorParameter::genericParameter,
                                                  [](float value, int) { return hzToString(value); },
                                                  [](const juce::String& text) { return stringToHz(text); }
                                                  )),
  sidechainListen (addToLayout<AudioParameterBool> (layout, ID::sidechainListen, "Sidechain Listen", false)),
  tilt (addToLayout<AudioParameterFloat> (layout,
                                          ID::tilt,
                                          "Tone",
                                          NormalisableRange<float> { -12.0f, 12.0f, 0.1f, 1.0f },
                                          0.0f,
                                          "dB",
                                          juce::AudioProcessorParameter::genericParameter,
                                          [](float value, int) { return dBToString(value); },
                                          [](const juce::String& text) { return stringToDB(text); }
                                          )),
  
  midSide (addToLayout<AudioParameterFloat> (layout,
                                             ID::midSide,
                                             "Mid/Side",
                                             NormalisableRange<float> { 0.0f, 100.0f, 0.1f, 1.0f },
                                             50.0f,
                                             "%",
                                             juce::AudioProcessorParameter::genericParameter,
                                             [](float value, int) { return percentToString(value); },
                                             [](const juce::String& text) { return stringToPercent(text); }
                                             )),
  noiseLevelGain (addToLayout<AudioParameterFloat> (layout,
                                                    ID::noiseLevelGain,
                                                    "Noise Gain",
                                                    NormalisableRange<float> { -24.0f, 24.0f, 0.1f, 1.0f },
                                                    0.0f,
                                                    "dB",
                                                    juce::AudioProcessorParameter::genericParameter,
                                                    [](float value, int) { return dBToString(value); },
                                                    [](const juce::String& text) { return stringToDB(text); }
                                                    )),
  
  outputGain (addToLayout<AudioParameterFloat> (layout,
                                                ID::outputGain,
                                                "Output Gain",
                                                NormalisableRange<float> { -24.0f, 24.0f, 0.1f, 1.0f },
                                                0.0f,
                                                "dB",
                                                juce::AudioProcessorParameter::genericParameter,
                                                [](float value, int) { return dBToString(value); },
                                                [](const juce::String& text) { return stringToDB(text); }
                                                )),
  
  dryWet (addToLayout<AudioParameterFloat> (layout,
                                            ID::dryWet,
                                            "Dry/Wet",
                                            NormalisableRange<float> { 0.0f, 100.0f, 0.1f, 1.0f },
                                            50.0f,
                                            "%",
                                            juce::AudioProcessorParameter::genericParameter,
                                            [](float value, int) { return percentToString(value); },
                                            [](const juce::String& text) { return stringToPercent(text); }
                                            )),
  
#if ADVANCED
  fastAttack (addToLayout<AudioParameterFloat> (layout,
                                                ID::fastAttack,
                                                "Fast Attack",
                                                NormalisableRange<float> { 0.001f, 0.1000f, 0.001f, 1.0f },
                                                0.0050f,
                                                "",
                                                juce::AudioProcessorParameter::genericParameter
                                                )),
  
  fastRelease (addToLayout<AudioParameterFloat> (layout,
                                                 ID::fastRelease,
                                                 "Fast Release",
                                                 NormalisableRange<float> { 0.001f, 0.1000f, 0.001f, 1.0f },
                                                 0.0170f,
                                                 "",
                                                 juce::AudioProcessorParameter::genericParameter
                                                 )),
  
  slowAttack (addToLayout<AudioParameterFloat> (layout,
                                                ID::slowAttack,
                                                "Slow Attack",
                                                NormalisableRange<float> { 0.001f, 0.1000f, 0.001f, 1.0f },
                                                0.0200f,
                                                "",
                                                juce::AudioProcessorParameter::genericParameter
                                                )),
  
  slowRelease (addToLayout<AudioParameterFloat> (layout,
                                                 ID::slowRelease,
                                                 "Slow Release",
                                                 NormalisableRange<float> { 0.001f, 0.2000f, 0.001f, 1.0f },
                                                 0.1000f,
                                                 "",
                                                 juce::AudioProcessorParameter::genericParameter
                                                 )),
#endif
  
  wetSolo (addToLayout<AudioParameterBool> (layout, ID::wetSolo, "Wet Solo", false)),
  linkChannels (addToLayout<AudioParameterBool> (layout, ID::linkChannels, "Channels Link", true))
  
  {
  }
  
  AudioParameterBool&  bypass;
#if ADVANCED
  AudioParameterChoice& generatorType;
#endif
  AudioParameterFloat& attack;
  AudioParameterFloat& release;
  
  AudioParameterFloat& threshold;
  
  AudioParameterBool& bpfPower;
  AudioParameterFloat& bpfFrequency;
  AudioParameterBool& sidechainListen;
  
  AudioParameterFloat& tilt;
  AudioParameterFloat& midSide;
  
  AudioParameterFloat& noiseLevelGain;
  AudioParameterFloat& outputGain;
  AudioParameterFloat& dryWet;
  
#if ADVANCED
  AudioParameterFloat& fastAttack;
  AudioParameterFloat& fastRelease;
  AudioParameterFloat& slowAttack;
  AudioParameterFloat& slowRelease;
#endif
  
  AudioParameterBool& wetSolo;
  AudioParameterBool& linkChannels;
  
  private:
  template <typename Param>
  static void add (AudioProcessorParameterGroup& group, std::unique_ptr<Param> param) {
    group.addChild (std::move (param));
  }
  
  template <typename Param>
  static void add (AudioProcessorValueTreeState::ParameterLayout& group, std::unique_ptr<Param> param) {
    group.add (std::move (param));
  }
  
  template <typename Param, typename Group, typename... Ts>
  static Param& addToLayout (Group& layout, Ts&&... ts) {
    auto param = std::make_unique<Param> (std::forward<Ts> (ts)...);
    auto& ref = *param;
    add (layout, std::move (param));
    return ref;
  }
  
  //==============================================================================
  
  static String hzToString (float value) {
    return juce::String(value, 1) + " Hz"; // << 표시될 문자열
  }
  static float stringToHz (const juce::String& text) {
    return text.dropLastCharacters(3).getFloatValue(); // "12 %" → 12
  }
  
  static String msToString (float value) {
    return juce::String(value, 0) + " ms"; // << 표시될 문자열
  }
  static float stringToMs (const juce::String& text) {
    return text.dropLastCharacters(3).getFloatValue(); // "12 ms" → 12
  }
  
  static String percentToString (float value) {
    return juce::String(value, 1) + " %"; // << 표시될 문자열
  }
  static float stringToPercent (const juce::String& text) {
    return text.dropLastCharacters(2).getFloatValue(); // "12 %" → 12
  }
  
  static String dBToString (float value) {
    return juce::String(value, 1) + " dB";  // << 표시될 문자열
  }
  static float stringToDB (const juce::String& text) {
    return text.dropLastCharacters(3).getFloatValue(); // "12 dB" → 12
  }
};
