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
class TransientFollower
{
  public:
  void prepare(const juce::dsp::ProcessSpec& spec)
  {
    sampleRate = spec.sampleRate;
    numChannels = spec.numChannels;
    
    attackCoeff = calcCoeff(0.01f);
    releaseCoeff = calcCoeff(0.1f);
    threshold = 0.1f;
    
    prevEnv.resize(numChannels, 0.0f);
    env.resize(numChannels, 0.0f);
    transient.resize(numChannels, 0.0f);
  }
  
  void reset()
  {
    std::fill(prevEnv.begin(), prevEnv.end(), 0.0f);
    std::fill(env.begin(), env.end(), 0.0f);
    std::fill(transient.begin(), transient.end(), 0.0f);
  }
  
  SampleType processSample(SampleType inputSample, size_t ch)
  {
    SampleType x = std::abs(inputSample);
    
    // Envelope follower
    if (x > env[ch])
      env[ch] = attackCoeff * (env[ch] - x) + x;
    else
      env[ch] = releaseCoeff * (env[ch] - x) + x;
    
    // Difference / transient detection
    SampleType diff = env[ch] - prevEnv[ch];
    
    // Threshold detection
    transient[ch] = diff > threshold ? 1.0f : 0.0f;
    
    prevEnv[ch] = env[ch];
    return env[ch];
  }
  
  void setAttack(SampleType a) { attackCoeff = calcCoeff(a); }
  void setRelease(SampleType r) { releaseCoeff = calcCoeff(r); }
  void setThreshold(SampleType t) { threshold = t; }
  
  private:
  double sampleRate = 44100.0;
  int numChannels = 2;
  
  SampleType attackCoeff = 0.01f;
  SampleType releaseCoeff = 0.1f;
  SampleType threshold = 0.01f; // 트랜지언트 감도
  
  std::vector<SampleType> env;
  std::vector<SampleType> prevEnv;
  std::vector<SampleType> transient;
  
  
  float calcCoeff(SampleType timeInSeconds)
  {
    return static_cast<SampleType>(std::exp(-1.0f / (timeInSeconds * (SampleType)sampleRate)));
  }
};
