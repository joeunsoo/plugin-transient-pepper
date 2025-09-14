/*
 ==============================================================================
 
 TransientNoise.h
 Created: 8 Sep 2025 3:45:52pm
 Author:  JoEunsoo
 
 ==============================================================================
 */

#pragma once
#include <JuceHeader.h>
#include "Utils.h"

template <typename SampleType>
class TransientFollower
{
  public:
  void prepare(const juce::dsp::ProcessSpec& spec)
  {
    sampleRate = spec.sampleRate;
    numChannels = spec.numChannels;
    
    fastAttack = calcCoeff(0.0050f, sampleRate); // 0.0020
    fastRelease = calcCoeff(0.00170f, sampleRate); // 0.0050
    slowAttack = calcCoeff(0.0200f, sampleRate);
    slowRelease = calcCoeff(0.1200f, sampleRate);
    
    fastEnv.resize(numChannels, 0.0f);
    slowEnv.resize(numChannels, 0.0f);
  }
  
  void reset()
  {
    std::fill(fastEnv.begin(), fastEnv.end(), 0.0f);
    std::fill(slowEnv.begin(), slowEnv.end(), 0.0f);
  }
  
  SampleType processSample(SampleType inputSample, size_t channel)
  {
    SampleType x = std::abs(inputSample);
    
    // Fast envelope
    if (x > fastEnv[channel])
      fastEnv[channel] = fastAttack * (fastEnv[channel] - x) + x;
    else
      fastEnv[channel] = fastRelease * (fastEnv[channel] - x) + x;
    
    // Slow envelope
    if (x > slowEnv[channel])
      slowEnv[channel] = slowAttack * (slowEnv[channel] - x) + x;
    else
      slowEnv[channel] = slowRelease * (slowEnv[channel] - x) + x;
    
    // Transient detection
    SampleType diff = fastEnv[channel] - slowEnv[channel];
    
    return diff;
    // return transientEnv[channel];
  }
  
  void setFastAttack(SampleType a) { fastAttack = calcCoeff(a, sampleRate); }
  void setFastRelease(SampleType r) { fastRelease = calcCoeff(r, sampleRate); }
  void setSlowAttack(SampleType a) { slowAttack = calcCoeff(a, sampleRate); }
  void setSlowRelease(SampleType r) { slowRelease = calcCoeff(r, sampleRate); }
  
  private:
  double sampleRate = 44100.0;
  int numChannels = 2;
  
  SampleType fastAttack = 0.0f;
  SampleType fastRelease = 0.0f;
  SampleType slowAttack = 0.0f;
  SampleType slowRelease = 0.0f;
  
  std::vector<SampleType> fastEnv;
  std::vector<SampleType> slowEnv;
  std::vector<SampleType> lpfState;
  
};
