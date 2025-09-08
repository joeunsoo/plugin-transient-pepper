/*
 ==============================================================================
 
 Saturation.h
 Created: 2 Sep 2025 12:05:44pm
 Author:  JoEunsoo
 
 ==============================================================================
 */

#pragma once
#include <JuceHeader.h>
#include <cmath>

template <typename SampleType>
class SaturationProcessor : public juce::dsp::ProcessorBase
{
    public:
    SaturationProcessor() {}
    
    // =====================================
    // dsp::ProcessorBase 인터페이스
    // =====================================
    void prepare (const juce::dsp::ProcessSpec& spec) override
    {
        sampleRate = spec.sampleRate;
        reset();
    }
    
    void reset() override {}
    
    void process (const juce::dsp::ProcessContextReplacing<SampleType>& context) override
    {
        auto& block = context.getOutputBlock();
        auto numChannels = block.getNumChannels();
        auto numSamples  = block.getNumSamples();
        
        for (size_t ch = 0; ch < numChannels; ++ch)
        {
            auto* channelData = block.getChannelPointer(ch);
            
            for (size_t i = 0; i < numSamples; ++i)
                channelData[i] = processSample(channelData[i]);
        }
    }
    
    // =====================================
    // 파라미터
    // =====================================
    void setDrive(SampleType value) { drive = juce::jlimit(0.0f, 1.0f, value / 100.0f); }
    
    private:
    SampleType drive { 0.5f };
    double sampleRate { 44100.0 };
    
    // =====================================
    // 내부 샘플 처리
    // =====================================
    float processSample(SampleType x) const
    {
        return tanhvariant(x);
    }
    
    float tanhvariant(float x0) const
    {
        float x = x0;
        float y = x;
        if (drive > 0.0f) {
            x = x0;
            x *= (1.0f - (drive * 0.1f)); // 입력보정
            x *= 4.0f; // 12 dB 밀어넣기
            
            y = (std::tanh(drive * x) / std::tanh(drive));
            
            y /= 4.0f; // -12 dB 빼기
        }
        
        return y;
    }
};
