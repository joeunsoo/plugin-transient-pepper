#pragma once

struct ToggleButton : public juce::ToggleButton
{
  ToggleButton()
        : juce::ToggleButton()
    {
    }
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ToggleButton)
};
