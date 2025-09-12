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
        dsp::ProcessSpec pspec{ sr, spec.maximumBlockSize, spec.numChannels };
        
        osc.initialise([](float x){ return std::sin(x); });
        osc.prepare(pspec);
        osc.setFrequency(10000.0f); // 10 kHz
    }

    float processSample(float trig)
    {
        if (trig > 0.0f)
        {
            return 0.3f * osc.processSample(0.0f); // input은 0으로 그냥 호출
        }
        return 0.0f;
    }

private:
    double sr = 44100.0;
    juce::dsp::Oscillator<float> osc;
};

//==============================================================================
// BitCrusher
class BitCrusher
{
  public:
  void prepare(const juce::dsp::ProcessSpec& spec)
  {
    step = 1.0f / 2.0f;
  }
  
  float processSample(float input)
  {
    return std::floor(input / step) * step * 1.0f;
  }
  
  private:
  float step = 1.0f / 2.0f;
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
    return 0.8f * rng.nextFloat();
  }
  
  private:
  juce::Random rng;
};
