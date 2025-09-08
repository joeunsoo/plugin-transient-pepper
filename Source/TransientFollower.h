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
    
    fastAttack = calcCoeff(0.0020f);
    fastRelease = calcCoeff(0.0175f);
    slowAttack = calcCoeff(0.0200f);
    slowRelease = calcCoeff(0.1000f);
    tAttack = calcCoeff(0.01f);
    tRelease = calcCoeff(0.01f);
    
    prevEnv.resize(numChannels, 0.0f);
    fastEnv.resize(numChannels, 0.0f);
    slowEnv.resize(numChannels, 0.0f);
    transient.resize(numChannels, 0.0f);
    transientEnv.resize(numChannels, 0.0f);
  }
  
  void reset()
  {
    std::fill(prevEnv.begin(), prevEnv.end(), 0.0f);
    std::fill(fastEnv.begin(), fastEnv.end(), 0.0f);
    std::fill(slowEnv.begin(), slowEnv.end(), 0.0f);
    std::fill(transient.begin(), transient.end(), 0.0f);
    std::fill(transientEnv.begin(), transientEnv.end(), 0.0f);
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
    diff = diff > 0 ? diff : 0.0f;

    diff = diff > threshold ? (diff - threshold) : 0.0f; // 트레숄드

    // Transient envelope
    if (diff > transientEnv[channel])
      transientEnv[channel] = tAttack * (transientEnv[channel] - diff) + diff;
    else
      transientEnv[channel] = tRelease * (transientEnv[channel] - diff) + diff;

    

    return transientEnv[channel];
  }
  
  void setFastAttack(SampleType a) { fastAttack = calcCoeff(a); }
  void setFastRelease(SampleType r) { fastRelease = calcCoeff(r); }
  void setSlowAttack(SampleType a) { slowAttack = calcCoeff(a); }
  void setSlowRelease(SampleType r) { slowRelease = calcCoeff(r); }
  void setTAttack(SampleType a) { tAttack = calcCoeff(a); }
  void setTRelease(SampleType r) { tRelease = calcCoeff(r); }
  void setThreshold(SampleType t) { threshold = t; }
  
  private:
  double sampleRate = 44100.0;
  int numChannels = 2;
  
  SampleType fastAttack = 0.0f;
  SampleType fastRelease = 0.0f;
  SampleType slowAttack = 0.0f;
  SampleType slowRelease = 0.0f;
  SampleType tAttack = 0.0f;
  SampleType tRelease = 0.0f;
  SampleType threshold = 0.03f;
  
  std::vector<SampleType> fastEnv;
  std::vector<SampleType> slowEnv;
  std::vector<SampleType> prevEnv;
  std::vector<SampleType> transient;
  std::vector<SampleType> transientEnv;
  
  
  float calcCoeff(SampleType timeInSeconds)
  {
    return static_cast<SampleType>(std::exp(-1.0f / (timeInSeconds * (SampleType)sampleRate)));
  }
};
