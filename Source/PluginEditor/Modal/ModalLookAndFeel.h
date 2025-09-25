#pragma once

#include "../../Define.h"

struct ModalLookAndFeel : public LookAndFeel_V4
{
  
  void drawButtonBackground (Graphics& g,
                             Button& button,
                             const Colour& backgroundColour,
                             bool shouldDrawButtonAsHighlighted,
                             bool shouldDrawButtonAsDown)
  override
  {
    auto cornerSize = UI_MODAL_BUTTON_BORDER_RADIUS;
    auto bounds = button.getLocalBounds().toFloat().reduced (0.5f, 0.5f);
    
    auto baseColour = backgroundColour.withMultipliedSaturation (button.hasKeyboardFocus (true) ? 1.3f : 0.9f)
      .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f);
    
    if (shouldDrawButtonAsDown || shouldDrawButtonAsHighlighted)
      baseColour = baseColour.contrasting (shouldDrawButtonAsDown ? 0.2f : 0.05f);
    
    g.setColour (baseColour);
    
    auto flatOnLeft   = button.isConnectedOnLeft();
    auto flatOnRight  = button.isConnectedOnRight();
    auto flatOnTop    = button.isConnectedOnTop();
    auto flatOnBottom = button.isConnectedOnBottom();
    
    if (flatOnLeft || flatOnRight || flatOnTop || flatOnBottom)
    {
      Path path;
      path.addRoundedRectangle (bounds.getX(), bounds.getY(),
                                bounds.getWidth(), bounds.getHeight(),
                                cornerSize, cornerSize,
                                ! (flatOnLeft  || flatOnTop),
                                ! (flatOnRight || flatOnTop),
                                ! (flatOnLeft  || flatOnBottom),
                                ! (flatOnRight || flatOnBottom));
      
      g.fillPath (path);
      
      g.setColour (button.findColour (ComboBox::outlineColourId));
      g.strokePath (path, PathStrokeType (1.0f));
    }
    else
    {
      g.fillRoundedRectangle (bounds, cornerSize);
      
      g.setColour (button.findColour (ComboBox::outlineColourId));
      g.drawRoundedRectangle (bounds, cornerSize, 1.0f);
    }
  }
  
  juce::Font getTextButtonFont (juce::TextButton&, int buttonHeight) override
  {
    auto fontHeight = std::min<float>(UI_BUTTON_FONT_HEIGHT, buttonHeight);
    return juce::Font { fontRegular.withHeight(fontHeight) };
  }
  
  void setFontRegular (juce::FontOptions f) { fontRegular = f; }
  void setFontMedium (juce::FontOptions f) { fontMedium = f; }
  void setFontSemiBold (juce::FontOptions f) { fontSemiBold = f; }
  void setFontBold (juce::FontOptions f) { fontBold = f; }
  
  private:
  juce::FontOptions fontRegular;
  juce::FontOptions fontMedium;
  juce::FontOptions fontSemiBold;
  juce::FontOptions fontBold;
};
