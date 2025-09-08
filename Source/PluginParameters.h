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
  
  attack (addToLayout<AudioParameterFloat> (layout,
                                            ID::attack,
                                            "Attack",
                                            NormalisableRange<float> { 0.001f, 0.1000f, 0.001f, 1.0f },
                                            0.0500f,
                                            "ms",
                                            juce::AudioProcessorParameter::genericParameter,
                                            [](float value, int) { return msToString(value * 1000.0f); },
                                            [](const juce::String& text) { return StringToMs(text); }
                                            )),
  
  release (addToLayout<AudioParameterFloat> (layout,
                                             ID::release,
                                             "Release",
                                             NormalisableRange<float> { 0.001f, 0.1000f, 0.001f, 1.0f },
                                             0.0500f,
                                             "ms",
                                             juce::AudioProcessorParameter::genericParameter,
                                             [](float value, int) { return msToString(value * 1000.0f); },
                                             [](const juce::String& text) { return StringToMs(text); }
                                             )),
  
  threshold (addToLayout<AudioParameterFloat> (layout,
                                               ID::threshold,
                                               "Threshold",
                                               NormalisableRange<float> { 0.0001f, 0.1000f, 0.0001f, 1.0f },
                                               0.0500f,
                                               "",
                                               juce::AudioProcessorParameter::genericParameter
                                               )),
  
  noiseLevel (addToLayout<AudioParameterFloat> (layout,
                                                ID::noiseLevel,
                                                "Ratio",
                                                NormalisableRange<float> { 1.0f, 20.0f, 0.1f, 1.0f },
                                                2.0f,
                                                "",
                                                juce::AudioProcessorParameter::genericParameter
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
                                            50.0f,
                                            "%",
                                            juce::AudioProcessorParameter::genericParameter,
                                            [](float value, int) { return percentToString(value); },
                                            [](const juce::String& text) { return stringToPercent(text); }
                                            ))
  {
  }
  
  AudioParameterBool&  bypass;
  AudioParameterFloat& attack;
  AudioParameterFloat& release;
  AudioParameterFloat& threshold;
  AudioParameterFloat& noiseLevel;
  AudioParameterFloat& transientAmount;
  AudioParameterFloat& emphasis;
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
  
  //==============================================================================

  static String msToString (float value) {
    return juce::String(value, 0) + " ms"; // << 표시될 문자열
  }
  static float StringToMs (const juce::String& text) {
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
  static float StringToDB (const juce::String& text) {
    return text.dropLastCharacters(3).getFloatValue(); // "12 dB" → 12
  }
};
