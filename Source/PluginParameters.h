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
                                               NormalisableRange<float> { -60.0f, 0.0f, 0.1f, 1.0f },
                                               -30.0f,
                                               "dB",
                                               juce::AudioProcessorParameter::genericParameter,
                                               [](float value, int) { return dBToString(value); },
                                               [](const juce::String& text) { return StringToDB(text); }
                                               )),
  
  tilt (addToLayout<AudioParameterFloat> (layout,
                                                ID::tilt,
                                                "Tone",
                                                NormalisableRange<float> { -12.0f, 12.0f, 0.1f, 1.0f },
                                                0.0f,
                                                "dB",
                                                juce::AudioProcessorParameter::genericParameter,
                                                [](float value, int) { return dBToString(value); },
                                                [](const juce::String& text) { return StringToDB(text); }
                                                )),
  
  midSide (addToLayout<AudioParameterFloat> (layout,
                                                     ID::midSide,
                                                     "M/S mix",
                                                     NormalisableRange<float> { 0.0f, 100.0f, 0.1f, 1.0f },
                                                     50.0f,
                                                     "%",
                                                     juce::AudioProcessorParameter::genericParameter,
                                                     [](float value, int) { return percentToString(value); },
                                                     [](const juce::String& text) { return stringToPercent(text); }
                                                     )),
  
  emphasis (addToLayout<AudioParameterFloat> (layout,
                                              ID::emphasis,
                                              "Emphasis",
                                              NormalisableRange<float> { -24.0f, 24.0f, 0.1f, 1.0f },
                                              0.0f,
                                              "dB",
                                              juce::AudioProcessorParameter::genericParameter,
                                              [](float value, int) { return dBToString(value); },
                                              [](const juce::String& text) { return StringToDB(text); }
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
                                            )),
  wetSolo (addToLayout<AudioParameterBool> (layout, ID::wetSolo, "Wet Solo", false)),
  linkChannels (addToLayout<AudioParameterBool> (layout, ID::linkChannels, "Channel Link", false))
  {
  }
  
  AudioParameterBool&  bypass;
  AudioParameterFloat& attack;
  AudioParameterFloat& release;
  AudioParameterFloat& threshold;
  AudioParameterFloat& tilt;
  AudioParameterFloat& midSide;
  AudioParameterFloat& emphasis;
  AudioParameterFloat& inputGain;
  AudioParameterFloat& outputGain;
  AudioParameterFloat& dryWet;
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
