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
// AirLayer
class AirLayer
{
  public:
  AirLayer() = default;
  void prepare()
  {
    //rng.setSeedRandomly();
    rng.setSeed(seedValue);
  }
  void reset()
  {
    rng.setSeed(seedValue);
  }
  
  
  float processSample()
  {
    return 0.8f * rng.nextFloat();
  }
  
  private:
  juce::Random rng;
  int seedValue = 20250912;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AirLayer)
};

//==============================================================================
// BitCrusher
class BitCrusher
{
  public:
  BitCrusher() = default;
  void prepare()
  {
    step = 1.0f / 2.0f;
  }
  
  float processSample(float input)
  {
    return std::floor(input / step) * step * 1.0f;
  }
  
  private:
  float step = 1.0f / 2.0f;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BitCrusher)
};
