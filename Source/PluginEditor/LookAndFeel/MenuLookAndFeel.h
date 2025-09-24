#pragma once

struct MenuLookAndFeel : juce::LookAndFeel_V4
{
  void setTypeface (juce::Typeface::Ptr tf) { typeface = tf; }
  
  juce::Font getPopupMenuFont() override
  {
    // Pretendard 14pt Bold 예시
    juce::FontOptions options { typeface };
    
    return juce::Font { options };
  }
  private:
  juce::Typeface::Ptr typeface;
};
