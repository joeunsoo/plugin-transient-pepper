/*
  ==============================================================================

    Utils.h
    Created: 12 Sep 2025 2:13:43pm
    Author:  JoEunsoo

  ==============================================================================
*/

#pragma once

inline float decibelToLinear(float db)
{
  float linear;
  
  if (db > -144.0f)  // effectively minus infinity
    linear = pow(10.0f, db / 20.0f);
  else
    linear = 0.0f;
  
  return linear;
}

inline float calcCoeff(float timeInSeconds, double sampleRate)
{
  return static_cast<float>(std::exp(-1.0f / (timeInSeconds * (float)sampleRate)));
}

inline float skewedMap(float value, float inMin, float inMax, float outMin, float outMax, float skew)
{
    float t = (value - inMin) / (inMax - inMin);  // normalize 0~1
    t = std::pow(t, skew);                        // skew 적용
    return outMin + t * (outMax - outMin);        // map to output
}
