/*
 ==============================================================================
 
 TransientNoise.h
 Created: 8 Sep 2025 3:45:52pm
 Author:  JoEunsoo
 
 ==============================================================================
 */

#pragma once
#include <JuceHeader.h>

template <typename SampleType>
struct TransientFollower
{
  void setAttack(SampleType a) { attack = a; alphaAttack = std::exp(-1.0f / (attack * sampleRate)); }
  void setRelease(SampleType r) { release = r; alphaRelease = std::exp(-1.0f / (release * sampleRate)); }
  
  void prepare(const juce::dsp::ProcessSpec& spec)
  {
    sampleRate = spec.sampleRate;
  }
  
  float processSample(SampleType input, SampleType env)
  {
    float rectified = std::abs(input);
    if (rectified > env) {
      env = alphaAttack * env + (1.0f - alphaAttack) * rectified;
    } else {
      env = alphaRelease * env + (1.0f - alphaRelease) * rectified;
    }
    return env;
  }
  
  SampleType attack = 0.01f;
  SampleType release = 0.1f;
  SampleType alphaAttack = 0.99977f;
  SampleType alphaRelease = 0.9989f;
  
  double sampleRate = 44100.0;
};
