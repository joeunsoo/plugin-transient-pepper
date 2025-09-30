#pragma once

#include "../DefineUI.h"

struct MenuLookAndFeel : juce::LookAndFeel_V4
{
  public:
  MenuLookAndFeel() {}
  ~MenuLookAndFeel() override {}

  void setFont (juce::FontOptions f) { mainFont = f; }
  
  juce::Colour getPopupMenuBackgroundColour()
  {
    return DARK_RGB[6]; // 원하는 배경색
  }
  
  juce::Colour getHighlightedBackgroundColour()
  {
    return DARK_RGB[5]; // 원하는 배경색
  }
  juce::Colour getTextColour()
  {
    return DARK_RGB[0]; // 원하는 배경색
  }
  
  juce::Font getPopupMenuFont() override
  {
    return juce::Font { mainFont };
  }
  
  void setWindowScale(int value)
  {
    windowScale = value;
  }
  
  void drawPopupMenuBackground (juce::Graphics& g, int width, int height) override
  {
    // g.fillAll (getPopupMenuBackgroundColour());
    
    auto bounds = juce::Rectangle<float> ((float) width, (float) height);
    
    g.setColour (getPopupMenuBackgroundColour());
    g.fillRect (bounds);
    
    g.setColour (DARK_RGB[4]);
    g.drawRect (bounds, 1.0f);
    
#if ! JUCE_MAC
    g.setColour (DARK_RGB[4].withAlpha (0.6f));
    g.drawRect (0, 0, width, height);
#endif
  }
  
  void getIdealPopupMenuItemSize (const String& text, const bool isSeparator,
                                  int standardMenuItemHeight, int& idealWidth, int& idealHeight)
  override
  {
    if (isSeparator)
    {
      idealWidth = 50;
      idealHeight = standardMenuItemHeight > 0 ? standardMenuItemHeight / 10 : 10;
    }
    else
    {
      auto font = getPopupMenuFont();
      
      if (standardMenuItemHeight > 0 && font.getHeight() > (float) standardMenuItemHeight / 1.3f)
        font.setHeight ((float) standardMenuItemHeight / 1.3f);
      
      float heightScale = 2.0f; // 원래는 1.3f
      if (text == "Scale") {
        heightScale = 1.3f;
      }
      idealHeight = standardMenuItemHeight > 0 ? standardMenuItemHeight : roundToInt (font.getHeight() * heightScale);
      idealWidth = GlyphArrangement::getStringWidthInt (font, text) + idealHeight * 2;
    }
  }
  
  void drawPopupMenuItem (Graphics& g, const juce::Rectangle<int>& area,
                          const bool isSeparator, const bool isActive,
                          const bool isHighlighted, const bool isTicked,
                          const bool hasSubMenu, const String& text,
                          const String& shortcutKeyText,
                          const Drawable* icon, const Colour* const textColourToUse)
  override
  {
    if (isSeparator)
    {
      auto r  = area.reduced (5, 0);
      r.removeFromTop (roundToInt (((float) r.getHeight() * 0.5f) - 0.5f));
      
      g.setColour(DARK_RGB[4]);
      g.fillRect (r.removeFromTop (1));
    }
    else
    {
      auto textColour = (textColourToUse == nullptr ? getTextColour()
                         : *textColourToUse);
      
      auto r  = area.reduced (1);
      
      if (isHighlighted && isActive)
      {
        g.setColour (getHighlightedBackgroundColour());
        g.fillRect (r);
        
        g.setColour (getTextColour());
      }
      else
      {
        g.setColour (textColour.withMultipliedAlpha (isActive ? 1.0f : 0.5f));
      }
      
      r.reduce (jmin (5, area.getWidth() / 20), 0);
      
      auto font = getPopupMenuFont();
      
      auto maxFontHeight = (float) r.getHeight() / 1.3f;
      
      if (font.getHeight() > maxFontHeight)
        font.setHeight (maxFontHeight);
      
      g.setFont (font);
      
      auto iconArea = r.removeFromLeft (roundToInt (maxFontHeight)).toFloat();
      
      if (icon != nullptr)
      {
        icon->drawWithin (g, iconArea, RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, 1.0f);
        r.removeFromLeft (roundToInt (maxFontHeight * 0.5f));
      }
      else if (isTicked)
      {
        auto tick = getTickShape (1.0f);
        g.fillPath (tick, tick.getTransformToScaleToFit (iconArea.reduced (iconArea.getWidth() / 5, 0).toFloat(), true));
      }
      
      if (hasSubMenu)
      {
        auto arrowH = 0.6f * getPopupMenuFont().getAscent();
        
        auto x = static_cast<float> (r.removeFromRight ((int) arrowH).getX());
        auto halfH = static_cast<float> (r.getCentreY());
        
        Path path;
        path.startNewSubPath (x, halfH - arrowH * 0.5f);
        path.lineTo (x + arrowH * 0.6f, halfH);
        path.lineTo (x, halfH + arrowH * 0.5f);
        
        g.strokePath (path, PathStrokeType (2.0f));
      }
      
      r.removeFromRight (3);
      g.drawFittedText (text, r, Justification::centredLeft, 1);
      
      if (shortcutKeyText.isNotEmpty())
      {
        auto f2 = font;
        f2.setHeight (f2.getHeight() * 0.75f);
        f2.setHorizontalScale (0.95f);
        g.setFont (f2);
        
        g.drawText (shortcutKeyText, r, Justification::centredRight, true);
      }
      
      
      if (
          (text == "100%" && windowScale == 100)
          || (text == "150%" && windowScale == 150)
          || (text == "200%" && windowScale == 200)
          ) {
            g.setColour(PRIMARY_RGB[5]);
            auto bounds = area;
            
            bounds.setX(area.getWidth()-15);
            bounds.setWidth(5);
            bounds.setY((area.getHeight()-5)/2);
            bounds.setHeight(5);
            g.fillRect(bounds);
          }
    }
  }
  
  private:
  juce::FontOptions mainFont;
  int windowScale;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MenuLookAndFeel)
};
