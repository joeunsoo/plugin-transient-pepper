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
  SampleType processThreshold(SampleType inputSample) {
    SampleType diff = inputSample;
    // Threshold, Ratio
    diff = diff > 0.0f ? diff : 0.0f; // 0 아래 0.0f
    if (diff < threshold)
      diff = 0.0f; // Threshold 아래 0.0f
    else
      diff = threshold + ((diff - threshold) / ratio); // 트레숄드 보다 높은건 Ratio 적용
    diff = juce::jlimit(0.0f, 1.0f, diff); // 안전하게 제한 // 0아래 절삭
    

    return diff;
  }

  SampleType processSample(SampleType inputSample, size_t ch)
  {
    SampleType x = std::fabs(inputSample);

    // Fast envelope
    if (x > fastEnv[ch])
      fastEnv[ch] = fastAttack * (fastEnv[ch] - x) + x;
    else
      fastEnv[ch] = fastRelease * (fastEnv[ch] - x) + x;
    
    // Slow envelope
    if (x > slowEnv[ch])
      slowEnv[ch] = slowAttack * (slowEnv[ch] - x) + x;
    else
      slowEnv[ch] = slowRelease * (slowEnv[ch] - x) + x;
    
    SampleType thresholdGain = skewedMap(threshold, 0.0f, 1.0f, 20.0f, 10.0f, 0.23f);

    // Transient detection f-s
    SampleType diff = fastEnv[ch] - slowEnv[ch];
    diff = processThreshold(diff) * 1.2f;
    
    // Transient detection f/s
    SampleType diffR = fastEnv[ch] / slowEnv[ch];
    diffR = (diffR - 0.8f) * 0.05f * (1-threshold);
    diffR = processThreshold(diffR) * threshold;

    SampleType result = ((diff * 0.8f)+(diffR * 0.2f)) * thresholdGain;
    return result;
  }

  void setFastAttack(SampleType a) { fastAttack = calcCoeff(a, sampleRate); }
  void setFastRelease(SampleType r) { fastRelease = calcCoeff(r, sampleRate); }
  void setSlowAttack(SampleType a) { slowAttack = calcCoeff(a, sampleRate); }
  void setSlowRelease(SampleType r) { slowRelease = calcCoeff(r, sampleRate); }
  
  SampleType threshold = 0.03f;
  SampleType ratio = 2.0f;
  
  private:
  double sampleRate = 44100.0;
  int numChannels = 2;
  
  SampleType fastAttack = 0.0f;
  SampleType fastRelease = 0.0f;
  SampleType slowAttack = 0.0f;
  SampleType slowRelease = 0.0f;
  
  std::vector<SampleType> fastEnv;
  std::vector<SampleType> slowEnv;
  
};
