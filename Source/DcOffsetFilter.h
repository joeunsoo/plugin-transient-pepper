/*
 ==============================================================================
 
 TiltEQ.h
 Created: 3 Sep 2025 11:16:42am
 Author:  JoEunsoo
 
 ==============================================================================
 */

#pragma once
#include <JuceHeader.h>

// Lightweight DC Offset Remover (one-pole HPF)
template <typename SampleType>
class DcOffsetFilter : public juce::dsp::ProcessorBase
{
    public:
    DcOffsetFilter(float pole = 0.995f)
    : R(pole) {}
    
    void prepare (const juce::dsp::ProcessSpec& spec) override
    {
        reset();
        sampleRate = spec.sampleRate;
    }
    
    void process (const juce::dsp::ProcessContextReplacing<SampleType>& context) override
    {
        auto& block = context.getOutputBlock();
        auto numChannels = block.getNumChannels();
        auto numSamples  = block.getNumSamples();
        
        for (size_t ch = 0; ch < numChannels; ++ch)
        {
            auto* channelData = block.getChannelPointer(ch);
            auto& prevX = x1[ch];
            auto& prevY = y1[ch];
            
            for (size_t i = 0; i < numSamples; ++i)
            {
                auto x = channelData[i];
                auto y = x - prevX + R * prevY;
                
                prevX = x;
                prevY = y;
                channelData[i] = y;
            }
        }
    }
    
    void reset() override
    {
        x1.clear();
        y1.clear();
        x1.resize(2, 0.0f);  // 기본 2채널 (스테레오)
        y1.resize(2, 0.0f);
    }
    
    private:
    double sampleRate = 44100.0;
    float R; // pole coefficient (0.995 ~ 0.9999)
    
    std::vector<float> x1, y1; // per-channel history
};
