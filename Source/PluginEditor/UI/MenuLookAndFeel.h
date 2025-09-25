#pragma once

#include "../../Define.h"

struct MenuLookAndFeel : juce::LookAndFeel_V4
{
  void setFont (juce::FontOptions f) { font = f; }
  
  juce::Colour getPopupMenuBackgroundColour()
  {
    return DARK_RGB[6]; // 원하는 배경색
  }
  
  void drawPopupMenuBackground (juce::Graphics& g, int width, int height) override
  {
    g.fillAll (getPopupMenuBackgroundColour());
    
#if ! JUCE_MAC
    g.setColour (findColour (PopupMenu::textColourId).withAlpha (0.6f));
    g.drawRect (0, 0, width, height);
#endif
  }
  
  juce::Font getPopupMenuFont() override
  {
    return juce::Font { font };
  }
  
  private:
  juce::FontOptions font;
};
