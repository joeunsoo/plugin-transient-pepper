#pragma once

struct KnobSlider : public juce::Slider
{
    KnobSlider()
        : juce::Slider(juce::Slider::RotaryHorizontalVerticalDrag, juce::Slider::NoTextBox)
    {
    }

    // 커스텀 멤버
    juce::String color = "primary";
    juce::String ringColor = "primary";
};
