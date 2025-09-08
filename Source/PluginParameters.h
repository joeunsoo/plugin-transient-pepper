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
  master (addToLayout<AudioParameterBool> (layout, ID::master, "Master On/Off", true)),

  noiseLevel (addToLayout<AudioParameterFloat> (layout,
                                                     ID::noiseLevel,
                                                     "Noise Level",
                                                     NormalisableRange<float> { 0.0f, 400.0f, 0.1f, 1.0f },
                                                     200.0f,
                                                     "%",
                                                     juce::AudioProcessorParameter::genericParameter,
                                                     [](float value, int) { return percentToString(value); },
                                                     [](const juce::String& text) { return stringToPercent(text); }
                                                     )),

  transientAmount (addToLayout<AudioParameterFloat> (layout,
                                                     ID::transientAmount,
                                                     "-",
                                                     NormalisableRange<float> { 0.0001f, 0.1000f, 0.0001f, 1.0f },
                                                     0.0500f,
                                                     "",
                                                     juce::AudioProcessorParameter::genericParameter
                                                     )),

  emphasis (addToLayout<AudioParameterFloat> (layout,
                                              ID::emphasis,
                                              "-",
                                              NormalisableRange<float> { 0.0001f, 0.1000f, 0.0001f, 1.0f },
                                              0.0500f,
                                              "",
                                              juce::AudioProcessorParameter::genericParameter
                                              )),

  threshold (addToLayout<AudioParameterFloat> (layout,
                                          ID::threshold,
                                          "Threshold",
                                          NormalisableRange<float> { 0.0001f, 0.1000f, 0.0001f, 1.0f },
                                          0.0500f,
                                          "",
                                          juce::AudioProcessorParameter::genericParameter
                                          )),

  attack (addToLayout<AudioParameterFloat> (layout,
                                                     ID::attack,
                                                     "Attack",
                                            NormalisableRange<float> { 0.0001f, 0.1000f, 0.0001f, 1.0f },
                                            0.0500f,
                                            "",
                                            juce::AudioProcessorParameter::genericParameter
                                                     )),

  release (addToLayout<AudioParameterFloat> (layout,
                                              ID::release,
                                              "Release",
                                             NormalisableRange<float> { 0.0001f, 0.1000f, 0.0001f, 1.0f },
                                             0.0500f,
                                             "",
                                             juce::AudioProcessorParameter::genericParameter
                                              )),

  inputGain (addToLayout<AudioParameterFloat> (layout,
                                               ID::inputGain,
                                               "Input Gain",
                                               NormalisableRange<float> { -24.0f, 24.0f, 0.1f, 1.0f },
                                               0.0f,
                                               "dB",
                                               juce::AudioProcessorParameter::genericParameter,
                                               [](float value, int) { return dBToString(value); },
                                               [](const juce::String& text) { return StringToDB(text); }
                                               )),

  outputGain (addToLayout<AudioParameterFloat> (layout,
                                                ID::outputGain,
                                                "Output Gain",
                                                NormalisableRange<float> { -24.0f, 24.0f, 0.1f, 1.0f },
                                                0.0f,
                                                "dB",
                                                juce::AudioProcessorParameter::genericParameter,
                                                [](float value, int) { return dBToString(value); },
                                                [](const juce::String& text) { return StringToDB(text); }
                                                )),

  dryWet (addToLayout<AudioParameterFloat> (layout,
                                            ID::dryWet,
                                            "Dry/Wet",
                                            NormalisableRange<float> { 0.0f, 100.0f, 0.1f, 1.0f },
                                            100.0f,
                                            "%",
                                            juce::AudioProcessorParameter::genericParameter,
                                            [](float value, int) { return percentToString(value); },
                                            [](const juce::String& text) { return stringToPercent(text); }
                                            ))
  {
  }
  
  AudioParameterBool&  master;
  AudioParameterFloat& noiseLevel;
  AudioParameterFloat& transientAmount;
  AudioParameterFloat& emphasis;
  AudioParameterFloat& threshold;
  AudioParameterFloat& attack;
  AudioParameterFloat& release;
  AudioParameterFloat& inputGain;
  AudioParameterFloat& outputGain;
  AudioParameterFloat& dryWet;
  
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
  
  static String percentToString (float value) {
    return juce::String(value, 1) + " %"; // << 표시될 문자열
  }
  static float stringToPercent (const juce::String& text) {
    return text.dropLastCharacters(2).getFloatValue(); // "12 %" → 12
  }
  
  static String dBToString (float value) {
    return juce::String(value, 1) + " dB";  // << 표시될 문자열
  }
  static float StringToDB (const juce::String& text) {
    return text.dropLastCharacters(3).getFloatValue(); // "12 dB" → 12
  }
};
