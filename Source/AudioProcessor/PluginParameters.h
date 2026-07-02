#pragma once
#include "../NamespaceParameterId.h"

struct Parameters
{
  public:
    explicit Parameters(AudioProcessorValueTreeState::ParameterLayout &layout)
        : bypass(addToLayout<juce::AudioParameterBool>(layout, ID::bypass, "Bypass", false)),
          attack(addToLayout<juce::AudioParameterFloat>(
              layout,
              ID::attack,
              "Attack",
              juce::NormalisableRange<float>{0.001f, 0.1000f, 0.001f, 1.0f},
              0.0500f,
              juce::AudioParameterFloatAttributes()
                  .withLabel("ms")
                  .withCategory(juce::AudioProcessorParameter::genericParameter)
                  .withStringFromValueFunction([](float value, int) //
                                               { return msToString(value * 1000.0f); })
                  .withValueFromStringFunction([](const juce::String &text) //
                                               { return stringToMs(text); }))),

          release(addToLayout<juce::AudioParameterFloat>(
              layout,
              ID::release,
              "Release",
              juce::NormalisableRange<float>{0.001f, 0.1000f, 0.001f, 1.0f},
              0.0500f,
              juce::AudioParameterFloatAttributes()
                  .withLabel("ms")
                  .withCategory(juce::AudioProcessorParameter::genericParameter)
                  .withStringFromValueFunction([](float value, int) //
                                               { return msToString(value * 1000.0f); })
                  .withValueFromStringFunction([](const juce::String &text) //
                                               { return stringToMs(text); }))),

          threshold(
              addToLayout<juce::AudioParameterFloat>(layout,
                                                     ID::threshold,
                                                     "Threshold",
                                                     juce::NormalisableRange<float>{-40.0f, 0.0f, 0.1f, 1.0f},
                                                     -20.0f,
                                                     juce::AudioParameterFloatAttributes()
                                                         .withLabel("dB")
                                                         .withCategory(juce::AudioProcessorParameter::genericParameter)
                                                         .withStringFromValueFunction([](float value, int) //
                                                                                      { return dBToString(value); })
                                                         .withValueFromStringFunction([](const juce::String &text) //
                                                                                      { return stringToDB(text); }))),

          bpfPower(addToLayout<juce::AudioParameterBool>(layout, ID::bpfPower, "BPF On/Off", false)),
          bpfFrequency(
              addToLayout<juce::AudioParameterFloat>(layout,
                                                     ID::bpfFrequency,
                                                     "BPF Freq",
                                                     juce::NormalisableRange<float>{50.0f, 12000.0f, 0.1f, 0.27375f},
                                                     1000.0f,
                                                     juce::AudioParameterFloatAttributes()
                                                         .withLabel("Hz")
                                                         .withCategory(juce::AudioProcessorParameter::genericParameter)
                                                         .withStringFromValueFunction([](float value, int) //
                                                                                      { return hzToString(value); })
                                                         .withValueFromStringFunction([](const juce::String &text) //
                                                                                      { return stringToHz(text); }))),
          sidechainListen(
              addToLayout<juce::AudioParameterBool>(layout, ID::sidechainListen, "Sidechain Listen", false)),
          tilt(addToLayout<juce::AudioParameterFloat>(layout,
                                                      ID::tilt,
                                                      "Tone",
                                                      juce::NormalisableRange<float>{-12.0f, 12.0f, 0.1f, 1.0f},
                                                      0.0f,
                                                      juce::AudioParameterFloatAttributes()
                                                          .withLabel("dB")
                                                          .withCategory(juce::AudioProcessorParameter::genericParameter)
                                                          .withStringFromValueFunction([](float value, int) //
                                                                                       { return dBToString(value); })
                                                          .withValueFromStringFunction([](const juce::String &text) //
                                                                                       { return stringToDB(text); }))),
          midSide(addToLayout<juce::AudioParameterFloat>(
              layout,
              ID::midSide,
              "Mid/Side",
              juce::NormalisableRange<float>{0.0f, 100.0f, 0.1f, 1.0f},
              50.0f,
              juce::AudioParameterFloatAttributes()
                  .withLabel("%")
                  .withCategory(juce::AudioProcessorParameter::genericParameter)
                  .withStringFromValueFunction([](float value, int) //
                                               { return percentToString(value); })
                  .withValueFromStringFunction([](const juce::String &text) //
                                               { return stringToPercent(text); }))),
          noiseLevelGain(
              addToLayout<juce::AudioParameterFloat>(layout,
                                                     ID::noiseLevelGain,
                                                     "Noise Gain",
                                                     juce::NormalisableRange<float>{-24.0f, 24.0f, 0.1f, 1.0f},
                                                     0.0f,
                                                     juce::AudioParameterFloatAttributes()
                                                         .withLabel("dB")
                                                         .withCategory(juce::AudioProcessorParameter::genericParameter)
                                                         .withStringFromValueFunction([](float value, int) //
                                                                                      { return dBToString(value); })
                                                         .withValueFromStringFunction([](const juce::String &text) //
                                                                                      { return stringToDB(text); }))),

          outputGain(addToLayout<juce::AudioParameterFloat>(
              layout,
              ID::outputGain,
              "Output Gain",
              juce::NormalisableRange<float>{-24.0f, 24.0f, 0.1f, 1.0f},
              0.0f,
              juce::AudioParameterFloatAttributes()
                  .withLabel("dB")
                  .withCategory(juce::AudioProcessorParameter::genericParameter)
                  .withStringFromValueFunction([](float value, int) //
                                               { return dBToString(value); })
                  .withValueFromStringFunction([](const juce::String &text) //
                                               { return stringToDB(text); }))),

          dryWet(addToLayout<juce::AudioParameterFloat>(
              layout,
              ID::dryWet,
              "Dry/Wet",
              juce::NormalisableRange<float>{0.0f, 100.0f, 0.1f, 1.0f},
              50.0f,
              juce::AudioParameterFloatAttributes()
                  .withLabel("%")
                  .withCategory(juce::AudioProcessorParameter::genericParameter)
                  .withStringFromValueFunction([](float value, int) //
                                               { return percentToString(value); })
                  .withValueFromStringFunction([](const juce::String &text) //
                                               { return stringToPercent(text); }))),

          wetSolo(addToLayout<juce::AudioParameterBool>(layout, ID::wetSolo, "Wet Solo", false)),
          linkChannels(addToLayout<juce::AudioParameterBool>(layout, ID::linkChannels, "Channels Link", true))
    {
    }

    juce::AudioParameterBool &bypass;

    juce::AudioParameterFloat &attack;
    juce::AudioParameterFloat &release;

    juce::AudioParameterFloat &threshold;

    juce::AudioParameterBool &bpfPower;
    juce::AudioParameterFloat &bpfFrequency;
    juce::AudioParameterBool &sidechainListen;

    juce::AudioParameterFloat &tilt;
    juce::AudioParameterFloat &midSide;

    juce::AudioParameterFloat &noiseLevelGain;
    juce::AudioParameterFloat &outputGain;
    juce::AudioParameterFloat &dryWet;

    juce::AudioParameterBool &wetSolo;
    juce::AudioParameterBool &linkChannels;

  private:
    template <typename Param> static void add(AudioProcessorParameterGroup &group, std::unique_ptr<Param> param)
    {
        group.addChild(std::move(param));
    }

    template <typename Param>
    static void add(AudioProcessorValueTreeState::ParameterLayout &group, std::unique_ptr<Param> param)
    {
        group.add(std::move(param));
    }

    template <typename Param, typename Group, typename... Ts> static Param &addToLayout(Group &layout, Ts &&...ts)
    {
        auto param = std::make_unique<Param>(std::forward<Ts>(ts)...);
        auto &ref = *param;
        add(layout, std::move(param));
        return ref;
    }

    //==============================================================================

    static juce::String hzToString(float value)
    {
        return juce::String(value, 1) + " Hz"; // << 표시될 문자열
    }
    static float stringToHz(const juce::String &text)
    {
        return text.dropLastCharacters(3).getFloatValue(); // "12 %" → 12
    }

    static juce::String msToString(float value)
    {
        return juce::String(value, 0) + " ms"; // << 표시될 문자열
    }
    static float stringToMs(const juce::String &text)
    {
        return text.dropLastCharacters(3).getFloatValue(); // "12 ms" → 12
    }

    static juce::String percentToString(float value)
    {
        return juce::String(value, 1) + " %"; // << 표시될 문자열
    }
    static float stringToPercent(const juce::String &text)
    {
        return text.dropLastCharacters(2).getFloatValue(); // "12 %" → 12
    }

    static juce::String dBToString(float value)
    {
        return juce::String(value, 1) + " dB"; // << 표시될 문자열
    }
    static float stringToDB(const juce::String &text)
    {
        return text.dropLastCharacters(3).getFloatValue(); // "12 dB" → 12
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Parameters)
};
