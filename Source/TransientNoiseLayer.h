/*
 ==============================================================================
 
 TransientNoiseLayer.h
 Created: 12 Sep 2025 1:36:31am
 Author:  JoEunsoo
 
 ==============================================================================
 */

#pragma once
#include <JuceHeader.h>

//==============================================================================
// HFClick
class HFClick
{
  public:
  void prepare(const juce::dsp::ProcessSpec& spec)
  {
    sr = spec.sampleRate;
    phase = 0;
    osc.initialise([](float x) { return std::sin(x); });
    dsp::ProcessSpec pspec{ sr, spec.maximumBlockSize, spec.numChannels };
    osc.prepare(pspec);
  }
  
  float processSample(int channel, float trig)
  {
    if (trig > 0.0f)
    {
      float value = 0.3f * osc.processSample(phase);
      phase += 2.0f * juce::MathConstants<float>::pi * 10000.0f / sr; // 10kHz
      return value;
    }
    else
    {
      return 0.0f;
    }
  }
  
  private:
  double sr = 44100.0;
  float phase = 0.0f;
  juce::dsp::Oscillator<float> osc;
};

//==============================================================================
// TransientResonator
class TransientResonator
{
  public:
  void prepare(const juce::dsp::ProcessSpec& spec)
  {
    dsp::ProcessSpec pspec = spec;
    filter.reset();
    filter.prepare(pspec);
    filter.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
    filter.setCutoffFrequency(2000.0f);
    filter.setResonance(1.0f);
  }
  
  float processSample(int channel, float input)
  {
    return filter.processSample(channel, input);
  }
  
  private:
  juce::dsp::StateVariableTPTFilter<float> filter;
};

//==============================================================================
// BitCrusher
class BitCrusher
{
  public:
  void prepare(const juce::dsp::ProcessSpec& spec)
  {
    step = 1.0f / 8.0f;
  }
  
  float processSample(float input)
  {
    return std::floor(input / step) * step;
  }
  
  private:
  float step = 1.0f / 8.0f;
};

//==============================================================================
// AirLayer
class AirLayer
{
  public:
  void prepare(const juce::dsp::ProcessSpec& spec)
  {
    //rng.setSeedRandomly();
    rng.setSeed(juce::Random::getSystemRandom().nextInt());
  }
  
  float processSample()
  {
    return 0.05f * rng.nextFloat();
    // return (rng.nextFloat() * 2.0f - 1.0f);
  }
  
  private:
  juce::Random rng;
};
