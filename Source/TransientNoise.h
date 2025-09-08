/*
 ==============================================================================
 
 TransientNoise.h
 Created: 8 Sep 2025 3:45:52pm
 Author:  JoEunsoo
 
 ==============================================================================
 */

#pragma once
#include <JuceHeader.h>

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
        
        prevSample.resize(numChannels, 0.0f);
        envelopeValues.resize(numChannels, 0.0f);
        
        envelopeFollower.prepare(spec);
        envelopeFollower.setAttack(0.001f);   // 0.01f = 10ms attack
        envelopeFollower.setRelease(0.001f);   // 0.1f = 100ms release

        noiseGenerator.setSeed(juce::Random::getSystemRandom().nextInt());
    }
    
    void reset() override
    {
        std::fill(prevSample.begin(), prevSample.end(), 0.0f);
        std::fill(envelopeValues.begin(), envelopeValues.end(), 0.0f);
    }
    
    void process(const juce::dsp::ProcessContextReplacing<SampleType>& context) override
    {
        auto& inputBlock = context.getInputBlock();
        auto& outputBlock = context.getOutputBlock();
        
        for (size_t ch = 0; ch < inputBlock.getNumChannels(); ++ch)
        {
            auto* in = inputBlock.getChannelPointer(ch);
            auto* out = outputBlock.getChannelPointer(ch);
            
            for (size_t n = 0; n < inputBlock.getNumSamples(); ++n)
            {
                SampleType sample = in[n];
                
                // Envelope follower (simple peak)
                envelopeValues[ch] = envelopeFollower.processSample(sample, envelopeValues[ch]);

                // 간단한 transient detection
                SampleType transient = sample - prevSample[ch];
                prevSample[ch] = sample;
                
                float dynamicNoise = noiseLevel * 0.01f * envelopeValues[ch];

                // noise 생성
                SampleType noiseSample = dynamicNoise * (noiseGenerator.nextFloat() * 2.0f - 1.0f);
                
                // transient shaping
                SampleType gain = 1.0f + transientAmount * std::abs(transient);
                out[n] = juce::jlimit(-1.0f, 1.0f, sample * gain + noiseSample);
            }
        }
    }
    
    void setNoiseLevel(SampleType level) { noiseLevel = level; }
    void setTransientAmount(SampleType amount) { transientAmount = amount; }
    
    private:
    // Envelope follower (simple peak detector)
    struct EnvelopeFollower
    {
        void setAttack(SampleType a) { attack = a; alphaAttack = std::exp(-1.0f / (attack * sampleRate)); }
        void setRelease(SampleType r) { release = r; alphaRelease = std::exp(-1.0f / (release * sampleRate)); }
        
        void prepare(const juce::dsp::ProcessSpec& spec)
        {
            sampleRate = spec.sampleRate;
        }
        
        float processSample(SampleType input, SampleType env)
        {
            float rectified = std::abs(input);
            if (rectified > env)
                env = alphaAttack * env + (1.0f - alphaAttack) * rectified;
            else
                env = alphaRelease * env + (1.0f - alphaRelease) * rectified;
            return env;
        }
        
        float attack = 0.01f;
        float release = 0.1f;
        float alphaAttack = 0.99977f;
        float alphaRelease = 0.9989f;
        
        double sampleRate = 44100.0;
    };

    double sampleRate = 44100.0;
    int numChannels = 2;
    
    juce::Random noiseGenerator;
    SampleType noiseLevel = 0.05f;
    SampleType transientAmount = 1.0f;
    std::vector<SampleType> prevSample;
    std::vector<SampleType> envelopeValues;
    EnvelopeFollower envelopeFollower;
};
