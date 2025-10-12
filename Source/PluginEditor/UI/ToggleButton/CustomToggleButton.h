#pragma once

#include "../../DefineUI.h"
#include "../../Provider/ScaleProvider.h"

struct CustomToggleButton : public juce::TextButton
{
  CustomToggleButton(const ScaleProvider& sp)
  : juce::TextButton(), scaleProvider(sp)
  {
    setClickingTogglesState(true);
  }
  
  void paintButton(juce::Graphics& g, bool shouldDrawButtonAsHighlighted,
                   bool shouldDrawButtonAsDown) override
  {
    auto scale = scaleProvider.getScale();
    LookAndFeel& laf = getLookAndFeel();
    
    juce::Colour backgroundColor = getToggleState() ? DARK_RGB_0 : DARK_RGB_4;
    laf.drawButtonBackground(g, *this, backgroundColor,
                             shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);
    
    if (svgDrawable != nullptr)
    {
      auto bounds = getLocalBounds().toFloat();
      bounds.removeFromTop(UI_BUTTON_PADDING_TOP * scale);
      bounds.removeFromLeft(UI_BUTTON_PADDING_LEFT * scale);
      bounds.removeFromBottom(UI_BUTTON_PADDING_BOTTOM * scale);
      bounds.removeFromRight(UI_BUTTON_PADDING_RIGHT * scale);
      bounds.reduce(UI_BUTTON_SVG_PADDING * scale, UI_BUTTON_SVG_PADDING * scale);
      
      auto normal = svgDrawable->createCopy();
      normal->replaceColour(juce::Colours::black, juce::Colours::white);
      juce::Drawable* svgToDraw = normal.get();

      svgToDraw->drawWithin(g,
                            bounds,
                            juce::RectanglePlacement::centred, 1.0f * scale);
    } else {
      laf.drawButtonText (g, *this, shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);
    }
  }
  
  void setSvgDrawable(std::unique_ptr<Drawable> drawable)
  {
    svgDrawable = std::move(drawable);
  }

  private:
  const ScaleProvider& scaleProvider;
  std::unique_ptr<juce::Drawable> svgDrawable;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomToggleButton)
};
