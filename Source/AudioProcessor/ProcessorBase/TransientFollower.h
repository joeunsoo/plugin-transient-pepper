/*
 ==============================================================================
 
 TransientNoise.h
 Created: 8 Sep 2025 3:45:52pm
 Author:  JoEunsoo
 
 ==============================================================================
 */

#pragma once
#include <JuceHeader.h>
#include "../../Utils.h"

template <typename SampleType>
class TransientFollower
{
  public:
  void prepare(const juce::dsp::ProcessSpec& spec)
  {
    sampleRate = spec.sampleRate;
    
    fastAttack = calcCoeff(0.0040f, sampleRate); // 0.0020
    fastRelease = calcCoeff(0.00170f, sampleRate); // 0.0050
    slowAttack = calcCoeff(0.0200f, sampleRate);
    slowRelease = calcCoeff(0.1200f, sampleRate);
    
    fastEnv.resize(spec.numChannels, 0.0f);
    slowEnv.resize(spec.numChannels, 0.0f);
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

    SampleType commonGain = 3.0f;
    // Transient detection f-s
    SampleType diffM = fastEnv[ch] - slowEnv[ch];
    diffM *= 1.0f;
    diffM = processThreshold(diffM);
    diffM *= 5.0f + commonGain;

    // Transient detection f/s
    // SampleType diffR = (fastEnv[ch] / slowEnv[ch]) - 0.8f;
    // diffR = processThreshold(diffR);
    // diffR *= 5.0f + commonGain;

    // 높을수록 diffM이 많아짐
    SampleType diff;
    diff = diffM;

    

    SampleType result = diff;
    return result;
  }

  void setFastAttack(SampleType a) { fastAttack = calcCoeff(a, sampleRate); }
  void setFastRelease(SampleType r) { fastRelease = calcCoeff(r, sampleRate); }
  void setSlowAttack(SampleType a) { slowAttack = calcCoeff(a, sampleRate); }
  void setSlowRelease(SampleType r) { slowRelease = calcCoeff(r, sampleRate); }
  
  SampleType threshold = 0.3f;
  SampleType ratio = 1.5f;
  
  private:
  double sampleRate = 44100.0;
  
  SampleType fastAttack = 0.0f;
  SampleType fastRelease = 0.0f;
  SampleType slowAttack = 0.0f;
  SampleType slowRelease = 0.0f;
  
  std::vector<SampleType> fastEnv;
  std::vector<SampleType> slowEnv;
  
};
