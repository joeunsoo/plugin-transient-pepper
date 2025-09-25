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
#include "TransientFollower.h"
#include "TiltEQ.h"
#include "BandPassFilter.h"
#include "TransientNoiseLayer.h"

template <typename SampleType>
class TransientNoiseProcessor : public juce::dsp::ProcessorBase
{
  public:
  TransientNoiseProcessor() {}
  ~TransientNoiseProcessor() override {}
  
  void prepare(const juce::dsp::ProcessSpec& spec) override
  {
    sampleRate = spec.sampleRate;
    const auto numChannels = spec.numChannels;
    
    sidechainBPF.prepare(spec);
    sidechainBPF.reset();
    sidechainBPF.setFrequency(sidechainBPFFreq);
    sidechainBPFGain.prepare(spec);
    sidechainBPFGain.reset();
    
    transientFollower.prepare(spec);
    
    bitCrusher.prepare();
    airLayer.prepare();

    attack = calcCoeff(0.01f, sampleRate);
    release = calcCoeff(0.01f, sampleRate);
    shapeEnv.resize(numChannels, 0.0f);

    envBuffer.setSize((int)spec.numChannels, (int)spec.maximumBlockSize);
    envBlock = juce::dsp::AudioBlock<SampleType>(envBuffer);
  }
  
  void reset() override
  {
    std::fill(shapeEnv.begin(), shapeEnv.end(), 0.0f);
    airLayer.reset();
  }
  
  void process(const juce::dsp::ProcessContextReplacing<SampleType>& context) override
  {
    auto& inputBlock = context.getInputBlock();
    auto& outputBlock = context.getOutputBlock();
    
    const auto numSamples = inputBlock.getNumSamples();
    const auto numChannels = inputBlock.getNumChannels();
    
    // 사이드체인으로 Block 복사
    juce::HeapBlock<char> tempBlockMem;
    juce::dsp::AudioBlock<SampleType> sidechainBlock (tempBlockMem, numChannels, numSamples);
    sidechainBlock.copyFrom (inputBlock); // 원본 입력을 복사
    juce::dsp::ProcessContextReplacing<SampleType> sidechainContext (sidechainBlock);

    sidechainBPF.setFrequency(sidechainBPFFreq);
    
    // 사이드체인 적용
    
    if (sidechainBPFOn || sidechainListen) {
      sidechainBPF.process(sidechainContext);
      sidechainBPFGain.setGainDecibels(skewedMap(sidechainBPFFreq, 50.0f, 12000.0f, -6.0f, 12.0f, 0.12f)); // 0.27f
      sidechainBPFGain.process(sidechainContext);
    } else {
      sidechainBPFGain.setGainDecibels(6.0f);
      sidechainBPFGain.process(sidechainContext);
    }
    
    for (size_t n = 0; n < numSamples; ++n)
    {
      SampleType linkedDiff = 0.0f; // 채널 링크
      std::vector<SampleType> sampleDiffs(numChannels, 0.0f); // 채널별
      for (size_t ch = 0; ch < numChannels; ++ch)
      {
        SampleType sideChainSample = sidechainBlock.getChannelPointer(ch)[n];
        sampleDiffs[ch] = transientFollower.processSample(sideChainSample, ch); // 엔벨로프 팔로워
      }
      
      // 링크 모드 처리
      if (linkChannels) {
        linkedDiff = *std::max_element(sampleDiffs.begin(), sampleDiffs.end());
      }
      
      for (size_t ch = 0; ch < numChannels; ++ch)
      {
        SampleType diff = linkChannels ? linkedDiff : sampleDiffs[ch];

        // Transient envelope
        if (diff > shapeEnv[ch])
          shapeEnv[ch] = attack * (shapeEnv[ch] - diff) + diff;
        else
          shapeEnv[ch] = release * (shapeEnv[ch] - diff) + diff;
        shapeEnv[ch] = juce::jlimit(-1.0f,1.0f,shapeEnv[ch]);

        envBlock.getChannelPointer(ch)[n] = shapeEnv[ch]; // 보관

        SampleType out = inputBlock.getChannelPointer(ch)[n];
        out = airLayer.processSample();
        
        if (sidechainListen) {
          outputBlock.getChannelPointer(ch)[n] = sidechainBlock.getChannelPointer(ch)[n]; // 사이드체인
        } else {
#if CHECK_ENV
          outputBlock.getChannelPointer(ch)[n] = shapeEnv[ch];
#elif CHECK_SIDECHAIN
          outputBlock.getChannelPointer(ch)[n] = sidechainBlock.getChannelPointer(ch)[n]; // 사이드체인
#else
          outputBlock.getChannelPointer(ch)[n] = shapeEnv[ch] * out;
#endif
        }
      }
    }
  }
  
  TransientFollower<SampleType> transientFollower;
  
  void setLinkChannels(bool value) { linkChannels = value; }

  void setSidechainBPFOn(bool value) { sidechainBPFOn = value; }
  void setSidechainBPFFreq(float value) { sidechainBPFFreq = value; }
  void setSidechainListen(bool value) { sidechainListen = value; }

  void setAttack(SampleType a) { attack = calcCoeff(a,sampleRate); }
  void setRelease(SampleType r) { release = calcCoeff(r,sampleRate); }
  void setThreshold(SampleType t) { transientFollower.threshold = t; }
  void setThresholdDecibels(SampleType t) { transientFollower.threshold = decibelToLinear(t); }
  void setDynamicMix(SampleType value) { transientFollower.setDynamicMix(value); }
  void setRatio(SampleType value) { transientFollower.ratio = value; }
  void setGeneratorType(int value) { generatorType = value; }
  
  juce::dsp::AudioBlock<SampleType> envBlock { envBuffer };

  private:
  double sampleRate = 44100.0;
  // int numChannels = 2;
  bool linkChannels = true;
  
  int generatorType = 0;
  BitCrusher bitCrusher;
  AirLayer airLayer;
  
  BandPassFilter<SampleType> sidechainBPF;
  dsp::Gain<SampleType> sidechainBPFGain;
  bool sidechainBPFOn = false;
  float sidechainBPFFreq = 1000.0f;
  bool sidechainListen = false;
  
  std::vector<SampleType> shapeEnv;
  
  SampleType attack = 0.0f;
  SampleType release = 0.0f;
  dsp::Gain<SampleType> thresholdGain;

  juce::AudioBuffer<SampleType> envBuffer;
};
