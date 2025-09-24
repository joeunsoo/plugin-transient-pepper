#pragma once

struct HeaderLookAndFeel : juce::LookAndFeel_V4
{
  void setTypeface (juce::Typeface::Ptr tf) { typeface = tf; }
  
  juce::Font getPopupMenuFont() override
  {
    // Pretendard 14pt Bold 예시
    juce::FontOptions options { typeface };
    
    return juce::Font { options };
  }

  void drawButtonBackground(Graphics& g, Button& b,
                            const Colour& backgroundColour,
                            bool shouldDrawButtonAsHighlighted,
                            bool shouldDrawButtonAsDown) override
  {
      // 배경 그리지 않음 → 투명
  }

  private:
  juce::Typeface::Ptr typeface;
};
