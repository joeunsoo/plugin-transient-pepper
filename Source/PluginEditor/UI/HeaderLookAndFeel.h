#pragma once

struct HeaderLookAndFeel : juce::LookAndFeel_V4
{
  void setFont (juce::FontOptions f) { font = f; }
  
  juce::Font getPopupMenuFont() override
  {
    return juce::Font { font };
  }

  private:
  juce::FontOptions font;
};
