#pragma once

#include "../Provider/ScaleProvider.h"
#include "../DefineUI.h"

#define UI_MODAL_BORDER_RADIUS 4.0f
#define UI_MODAL_BUTTON_FONT_HEIGHT 8.5f
#define UI_MODAL_BUTTON_BORDER_RADIUS 4.0f
#define UI_MODAL_TEXT_LABEL_HEIGHT 9.0f
#define UI_MODAL_TEXT_LABEL_FONT_HEIGHT 9.0f
#define UI_MODAL_TEXT_EDITOR_LABEL_HEIGHT 9.0f
#define UI_MODAL_TEXT_EDITOR_LABEL_FONT_HEIGHT 9.0f
#define UI_MODAL_TEXT_EDITOR_BORDER_RADIUS 4.0f
#define UI_MODAL_TEXT_EDITOR_HEIGHT 20
#define UI_MODAL_TEXT_EDITOR_FONT_HEIGHT 10.0f

#define UI_PLUGIN_NAME_FONT_HEIGHT 14

struct ModalLookAndFeel : public LookAndFeel_V4
{
  public:
  ModalLookAndFeel(const ScaleProvider& sp)
  :scaleProvider(sp) {}
  ~ModalLookAndFeel() override {}

  void drawButtonBackground (Graphics& g,
                             Button& button,
                             const Colour& backgroundColour,
                             bool shouldDrawButtonAsHighlighted,
                             bool shouldDrawButtonAsDown)
  override
  {
    auto scale = scaleProvider.getScale();

    auto cornerSize = UI_MODAL_BUTTON_BORDER_RADIUS * scale;
    auto bounds = button.getLocalBounds().toFloat().reduced (0.5f * scale, 0.5f * scale);
    
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
  
  
  void drawTextEditorOutline (juce::Graphics& g, int width, int height, juce::TextEditor& textEditor) override
  {
    auto scale = scaleProvider.getScale();

    auto borderThickness = 1.0f;
    auto cornerSize = UI_MODAL_TEXT_EDITOR_BORDER_RADIUS * scale; // borderRadius 값
    
    auto bounds = juce::Rectangle<float>(0, 0, (float)width, (float)height);
    
    g.setColour (textEditor.hasKeyboardFocus (true)
                 ? textEditor.findColour (juce::TextEditor::focusedOutlineColourId)
                 : textEditor.findColour (juce::TextEditor::outlineColourId));
    
    g.drawRoundedRectangle (bounds.reduced (borderThickness * 0.5f),
                            cornerSize,
                            borderThickness);
  }
  
  juce::Font getTextButtonFont (juce::TextButton&, int buttonHeight) override
  {
    auto scale = scaleProvider.getScale();
    auto fontHeight = std::min<float>(UI_MODAL_BUTTON_FONT_HEIGHT * scale, buttonHeight);
    return juce::Font { FONT_PRETENDARD_REGULAR.withHeight(fontHeight) };
  }
  
  juce::Colour getPopupMenuBackgroundColour()
  {
    return DARK_RGB_6; // 원하는 배경색
  }
  
  juce::Colour getHighlightedBackgroundColour()
  {
    return DARK_RGB_5; // 원하는 배경색
  }
  juce::Colour getTextColour()
  {
    return DARK_RGB_0; // 원하는 배경색
  }
  
  juce::Font getPopupMenuFont() override
  {
    auto scale = scaleProvider.getScale();
    return juce::Font { FONT_PRETENDARD_REGULAR.withHeight(UI_POPUPMENU_FONT_HEIGHT * scale) };
  }
  
  void drawPopupMenuBackground (juce::Graphics& g, int width, int height) override
  {
    // g.fillAll (getPopupMenuBackgroundColour());
    
    auto bounds = juce::Rectangle<float> ((float) width, (float) height);
    
    g.setColour (getPopupMenuBackgroundColour());
    g.fillRect (bounds);
    
    g.setColour (DARK_RGB_4);
    g.drawRect (bounds, 1.0f);
    
#if ! JUCE_MAC
    g.setColour (findColour (PopupMenu::textColourId).withAlpha (0.6f));
    g.drawRect (0, 0, width, height);
#endif
  }
  
  void drawPopupMenuItem (Graphics& g, const juce::Rectangle<int>& area,
                          const bool isSeparator, const bool isActive,
                          const bool isHighlighted, const bool isTicked,
                          const bool hasSubMenu, const String& text,
                          const String& shortcutKeyText,
                          const Drawable* icon, const Colour* const textColourToUse)
  override
  {
    auto scale = scaleProvider.getScale();

    if (isSeparator)
    {
      auto r  = area.reduced (int(5 * scale), 0);
      r.removeFromTop (roundToInt (((float) r.getHeight() * 0.5f) - 0.5f));
      
      g.setColour(DARK_RGB_4);
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
      
      r.reduce (jmin (int(5 * scale), area.getWidth() / 20), 0);
      
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
        auto tick = getTickShape (1.0f * scale);
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
    }
  }

  private:
  const ScaleProvider& scaleProvider;
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ModalLookAndFeel)
};
