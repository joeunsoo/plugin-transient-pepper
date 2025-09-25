/*
  ==============================================================================

    Utils.h
    Created: 12 Sep 2025 2:13:43pm
    Author:  JoEunsoo

  ==============================================================================
*/

#pragma once
#include <cmath>
#include <algorithm> // std::clamp

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

inline float skewedMapFromMid(float value, float inMin, float inMax, float outMin, float outMax, float mid)
{
    // mid 기준으로 skew 계산
    float skew = std::log(0.5f) / std::log((mid - inMin) / (inMax - inMin));

    // value 정규화 0~1
    float t = (value - inMin) / (inMax - inMin);
    t = std::pow(t, skew); // skew 적용

    return outMin + t * (outMax - outMin); // 출력 범위 매핑
}

inline float applySkew(float value, float inMin, float inMax, float mid)
{
    // 입력 값 0~1로 정규화
    float normalized = (value - inMin) / (inMax - inMin);

    // mid 기준으로 skew 계산
    float skewFactor = std::log(0.5f) / std::log((mid - inMin) / (inMax - inMin));

    // skew 적용 후 다시 출력 범위로 매핑
    float result = inMin + std::pow(normalized, skewFactor) * (inMax - inMin);

    // 안전하게 clamp
    return std::clamp(result, inMin, inMax);
}
