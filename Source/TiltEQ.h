/*
 ==============================================================================
 
 TiltEQ.h
 Created: 3 Sep 2025 11:16:42am
 Author:  JoEunsoo
 
 ==============================================================================
 */

#pragma once
#include <JuceHeader.h>

// TiltEQ DSP
template <typename SampleType>
class TiltEQProcessor : public juce::dsp::ProcessorBase
{
    public:
    TiltEQProcessor() {}
    
    void prepare(const juce::dsp::ProcessSpec& spec) override
    {
        sampleRate = spec.sampleRate;
        
        lowShelf.reset();
        highShelf.reset();
        
        lowShelf.prepare(spec);
        highShelf.prepare(spec);
    }
    
    void reset() override
    {
        lowShelf.reset();
        highShelf.reset();
    }
    
    void process(const juce::dsp::ProcessContextReplacing<SampleType>& context) override
    {
        auto tiltGain = juce::Decibels::decibelsToGain(tiltDb);
        
        *lowShelf.state = *juce::dsp::IIR::Coefficients<SampleType>::makeLowShelf(
                                                                                  sampleRate, 1000.0f, 0.35f, 1.0f / tiltGain);
        
        *highShelf.state = *juce::dsp::IIR::Coefficients<SampleType>::makeHighShelf(
                                                                                    sampleRate, 1000.0f, 0.35f, tiltGain);
        
        lowShelf.process(context);
        highShelf.process(context);
    }
    
    void setGain(float db) { tiltDb = db; }
    
    private:
    double sampleRate = 44100.0;
    float tiltDb = 0.0f;
    
    // ProcessorDuplicator를 사용해 스테레오 대응
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<SampleType>,
    juce::dsp::IIR::Coefficients<SampleType>> lowShelf;
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<SampleType>,
    juce::dsp::IIR::Coefficients<SampleType>> highShelf;
};
