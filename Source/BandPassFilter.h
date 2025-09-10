#pragma once
#include <JuceHeader.h>

template <typename SampleType>
class BandPassFilter : public juce::dsp::ProcessorBase
{
public:
    BandPassFilter() {}

    void prepare(const juce::dsp::ProcessSpec& spec) override
    {
        sampleRate = spec.sampleRate;

        bandPass.reset();
        bandPass.prepare(spec);

        // 초기 계수 생성
        currentFrequency = frequency;
        currentQ = q;

        *bandPass.state = *juce::dsp::IIR::Coefficients<SampleType>::makeBandPass(sampleRate, frequency, q);
    }

    void reset() override
    {
        bandPass.reset();
    }

    void process(const juce::dsp::ProcessContextReplacing<SampleType>& context) override
    {
        // 샘플 단위로 계수 부드럽게 업데이트
        smoothCoefficients();

        bandPass.process(context);
    }

    // 파라미터 설정 (목표값)
    void setFrequency(float newFreqHz)
    {
        frequency = juce::jlimit(20.0f, (float)(sampleRate * 0.45), newFreqHz);
    }

    void setQ(float newQ)
    {
        q = juce::jmax(0.1f, newQ);
    }

private:
    void smoothCoefficients()
    {
        // alpha: smoothing factor (0.001~0.05)
        constexpr float alpha = 0.05f;

        // 선형 보간: 현재 주파수/질량 → 목표 주파수/질량
        currentFrequency = alpha * frequency + (1.0f - alpha) * currentFrequency;
        currentQ = alpha * q + (1.0f - alpha) * currentQ;

        // 새 Coefficients 객체 생성
        auto newCoeffs = juce::dsp::IIR::Coefficients<SampleType>::makeBandPass(
            sampleRate, currentFrequency, currentQ);

        // ProcessorDuplicator에 적용
        *bandPass.state = *newCoeffs;
    }

    double sampleRate = 44100.0;

    // 목표 파라미터
    float frequency = 1000.0f;
    float q = 5.0f;

    // 현재 보간값
    float currentFrequency = 1000.0f;
    float currentQ = 5.0f;

    juce::dsp::ProcessorDuplicator<
        juce::dsp::IIR::Filter<SampleType>,
        juce::dsp::IIR::Coefficients<SampleType>>
        bandPass;
};
