/*
 ==============================================================================
 
 AntiAliasingFilter.h
 Created: 3 Sep 2025 3:12:20pm
 Author:  JoEunsoo
 
 ==============================================================================
 */

#pragma once
#include <JuceHeader.h>

class AntiAliasingFilter : public juce::dsp::ProcessorBase
{
    public:
    AntiAliasingFilter() {}
    ~AntiAliasingFilter() override {}
    
    void prepare(const juce::dsp::ProcessSpec& spec) override
    {
        sampleRate = spec.sampleRate;
        cutoffFreq = 0.45 * sampleRate;
        
        auto numChannels = spec.numChannels;
        
        // 2차 Butterworth low-pass filter 설계 (cutoff: Nyquist/2 이하)
        for (int ch = 0; ch < numChannels; ++ch)
        {
            filters.emplace_back(std::make_unique<juce::dsp::IIR::Filter<float>>());
            juce::dsp::IIR::Coefficients<float>::Ptr coeffs =
            juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, cutoffFreq);
            filters[ch]->coefficients = coeffs;
        }
    }
    
    void reset() override
    {
        for (auto& f : filters)
            if (f) f->reset();
    }
    
    void process (const juce::dsp::ProcessContextReplacing<float>& context) override
    {
        auto& block = context.getOutputBlock();
        const auto numChannels = block.getNumChannels();
        const auto numSamples = block.getNumSamples();
        
        for (size_t ch = 0; ch < numChannels; ++ch)
        {
            auto* data = block.getChannelPointer(ch);
            for (size_t n = 0; n < numSamples; ++n)
            {
                data[n] = filters[ch]->processSample(data[n]);
            }
        }
    }
    
    private:
    double sampleRate = 44100.0;
    float cutoffFreq = 20000.0f; // 기본값 20kHz
    std::vector<std::unique_ptr<juce::dsp::IIR::Filter<float>>> filters;
};
