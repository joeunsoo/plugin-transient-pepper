#pragma once

struct CustomToggleButton : public juce::TextButton
{
  CustomToggleButton()
        : juce::TextButton()
    {
      setClickingTogglesState(true);
    }
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomToggleButton)
};
