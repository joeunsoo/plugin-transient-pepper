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
    numChannels = spec.numChannels;
    
    sidechainTilt.prepare(spec);
    sidechainTilt.reset();
    sidechainTiltGain.setGainDecibels(0.0f);
    sidechainTiltGain.reset();
    
    sidechainBPF.prepare(spec);
    sidechainBPF.reset();
    sidechainBPFGain.prepare(spec);
    sidechainBPFGain.reset();
    
    transientFollower.prepare(spec);
    
    hfClick.prepare(spec);
    bitCrusher.prepare(spec);
    airLayer.prepare(spec);

    attack = calcCoeff(0.01f, sampleRate);
    release = calcCoeff(0.01f, sampleRate);
    shapeEnv.resize(numChannels, 0.0f);
  }
  
  void reset() override
  {
    std::fill(shapeEnv.begin(), shapeEnv.end(), 0.0f);
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

    // 파라미터
    sidechainTilt.setGain(emphasis);
    sidechainTiltGain.setGainDecibels(emphasis * 0.4f);
    
    sidechainBPFGain.setGainDecibels(skewedMap(sidechainBPFFreq, 100.0f, 12000.0f, -6.0f, 12.0f, 0.27f));
    sidechainBPF.setFrequency(sidechainBPFFreq);
    
    SampleType thresholdGain = skewedMap(threshold, 0.0f, 1.0f, 40.0f, 10.0f, 1.0f);

    // 사이드체인 적용
    sidechainTilt.process(sidechainContext);
    sidechainTiltGain.process(sidechainContext);
    
    if (sidechainBPFOn) {
      sidechainBPF.process(sidechainContext);
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
        // 평균값 링크 (원하면 max() 등 다른 방식 가능)
        // for (auto v : sampleEnvelopes) linkedEnvelope += v;
        // linkedEnvelope /= (SampleType)numChannels;

        // 최대값 링크
        linkedDiff = *std::max_element(sampleDiffs.begin(), sampleDiffs.end());
      }
      
      for (size_t ch = 0; ch < numChannels; ++ch)
      {
        SampleType diff = linkChannels ? linkedDiff : sampleDiffs[ch];

        // Threshold, Ratio
        diff = diff > 0 ? diff : 0.0f; // 0 아래 0.0f
        if (diff < threshold)
          diff = 0.0f; // Threshold 아래 0.0f
        else
          diff = threshold + ((diff - threshold) / ratio); // 트레숄드 보다 높은건 Ratio 적용
        diff = juce::jlimit(0.0f, 1.0f, diff); // 안전하게 제한
        
        diff *= thresholdGain;

        // Transient envelope
        if (diff > shapeEnv[ch])
          shapeEnv[ch] = attack * (shapeEnv[ch] - diff) + diff;
        else
          shapeEnv[ch] = release * (shapeEnv[ch] - diff) + diff;
        
        SampleType out = inputBlock.getChannelPointer(ch)[n];
        out = hfClick.processSample(shapeEnv[ch] > 0.001f ? shapeEnv[ch] : 0.0f );
        // out = bitCrusher.processSample(static_cast<float>(out));
        // out = airLayer.processSample();
        
#if !CHECK_ENV
        outputBlock.getChannelPointer(ch)[n] = shapeEnv[ch] * out;
#else
        outputBlock.getChannelPointer(ch)[n] = shapeEnv[ch];
#endif
        // outputBlock.getChannelPointer(ch)[n] = sidechainBlock.getChannelPointer(ch)[n]; // 사이드체인
      }
    }
  }
  
  TransientFollower<SampleType> transientFollower;
  
  void setLinkChannels(bool value) { linkChannels = value; }
  void setEmphasis(SampleType value) { emphasis = value; }
  void setSidechainBPFOn(bool value) { sidechainBPFOn = value; }
  void setSidechainBPFFreq(float value) { sidechainBPFFreq = value; }
  
  void setAttack(SampleType a) { attack = calcCoeff(a,sampleRate); }
  void setRelease(SampleType r) { release = calcCoeff(r,sampleRate); }
  void setThreshold(SampleType t) { threshold = t; }
  void setThresholdDecibels(SampleType t) { threshold = decibelToLinear(t); }
  void setRatio(SampleType value) { ratio = value; }

  private:
  double sampleRate = 44100.0;
  int numChannels = 2;
  bool linkChannels = true;
  
  HFClick hfClick;
  BitCrusher bitCrusher;
  AirLayer airLayer;
  
  TiltEQProcessor<SampleType> sidechainTilt;
  dsp::Gain<SampleType> sidechainTiltGain;
  SampleType emphasis = 0.0f;
  
  BandPassFilter<SampleType> sidechainBPF;
  dsp::Gain<SampleType> sidechainBPFGain;
  bool sidechainBPFOn = false;
  float sidechainBPFFreq = 1000.0f;
  
  std::vector<SampleType> shapeEnv;
  
  SampleType attack = 0.0f;
  SampleType release = 0.0f;
  SampleType threshold = 0.03f;
  SampleType ratio = 20.0f;
  dsp::Gain<SampleType> thresholdGain;
};
