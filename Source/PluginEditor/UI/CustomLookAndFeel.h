#pragma once

#include "../../Define.h"
#include "KnobSlider.h"

struct CustomLookAndFeel : public LookAndFeel_V4
{
  public:
  CustomLookAndFeel() {}
  ~CustomLookAndFeel() override {}
  
  void drawButtonBackground (juce::Graphics& g,
                             juce::Button& button,
                             const juce::Colour&, // backgroundColour
                             bool shouldDrawButtonAsHighlighted,
                             bool shouldDrawButtonAsDown) override
  {
    auto boundsOut = button.getLocalBounds().toFloat();
    auto bounds = boundsOut;
    bounds.removeFromTop(UI_BUTTON_PADDING_TOP);
    bounds.removeFromLeft(UI_BUTTON_PADDING_LEFT);
    bounds.removeFromBottom(UI_BUTTON_PADDING_BOTTOM);
    bounds.removeFromRight(UI_BUTTON_PADDING_RIGHT);
    
    float cornerSize = UI_BUTTON_BORDER_RADIUS;
    
    
    // Drop shadow
    juce::Image buttonImage(
                            juce::Image::ARGB,
                            juce::roundToInt(boundsOut.getWidth()),
                            juce::roundToInt(boundsOut.getHeight()),
                            true);
    {
        juce::Graphics g2(buttonImage);
        g2.fillRoundedRectangle(bounds, cornerSize);
    }
    juce::DropShadow ds(
                        juce::Colours::black.withAlpha(0.5f),
                        2,
                        {0, 3});
    
    // 위치 변환 후 그림자 적용
    g.saveState();
    
    ds.drawForImage(g, buttonImage);  // 이제 2개 인자
    // g.drawImageAt(buttonImage, 0, 0);
    g.restoreState();
    
    // --- 상태별 배경색 (linear-gradient 느낌)
    juce::ColourGradient gradient(
                                  button.getToggleState()
                                  ? SECONDARY_DARK_RGB[0]   // 활성 (ON)
                                  : SECONDARY_DARK_RGB[6],     // 비활성 (OFF)
                                  bounds.getTopLeft(),
                                  button.getToggleState()
                                  ? SECONDARY_DARK_RGB[2]
                                  : SECONDARY_DARK_RGB[9],
                                  bounds.getBottomRight(),
                                  false
                                  );
    
    g.setGradientFill(gradient);
    g.fillRoundedRectangle(bounds, cornerSize);
    
    // --- border
    g.setColour(PRIMARY_RGB[9]);
    g.drawRoundedRectangle(bounds, cornerSize, 1.0f);
    
    // --- hover 효과
    if (shouldDrawButtonAsHighlighted && ! button.getToggleState())
    {
      g.setColour(juce::Colours::white.withAlpha(0.05f));
      g.fillRoundedRectangle(bounds, cornerSize);
    }
    
    // --- 클릭 상태(Down) 효과
    if (shouldDrawButtonAsDown)
    {
      g.setColour(juce::Colours::black.withAlpha(0.2f));
      g.fillRoundedRectangle(bounds, cornerSize);
    }
  }
  
  void drawButtonText (Graphics& g, TextButton& button,
                       bool /*shouldDrawButtonAsHighlighted*/, bool /*shouldDrawButtonAsDown*/)
  override
  {
    Font font (getTextButtonFont (button, button.getHeight()));

    g.setFont (font);
    g.setColour (button.findColour (button.getToggleState() ? TextButton::textColourOnId
                                    : TextButton::textColourOffId)
                 .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f));
    
    const int yIndent = jmin (4, button.proportionOfHeight (0.3f));
    const int cornerSize = jmin (button.getHeight(), button.getWidth()) / 2;
    
    const int fontHeight = roundToInt (font.getHeight() * 0.6f);
    const int leftIndent  = jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnLeft() ? 4 : 2));
    const int rightIndent = jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnRight() ? 4 : 2));
    const int textWidth = button.getWidth() - leftIndent - rightIndent;
    
    auto bounds = button.getLocalBounds();
    bounds.removeFromTop(UI_BUTTON_PADDING_TOP + yIndent);
    bounds.removeFromLeft(UI_BUTTON_PADDING_LEFT + leftIndent);
    bounds.removeFromBottom(UI_BUTTON_PADDING_BOTTOM + yIndent);
    bounds.removeFromRight(UI_BUTTON_PADDING_RIGHT + rightIndent);
    
    if (textWidth > 0)
      g.drawFittedText (button.getButtonText(),
                        bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight(),
                        Justification::centred, 2);
  }
  
  void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override
  {
    juce::Colour colorIn = PRIMARY_RGB[6];
    juce::Colour colorDotLine = PRIMARY_DARK_RGB[2];
    juce::Colour colorDot = PRIMARY_DARK_RGB[3];
    juce::Colour colorRing = PRIMARY_DARK_RGB[6];
    
    if (auto* knobSlider = dynamic_cast<KnobSlider*>(&slider))
    {
      juce::String color = knobSlider->color;
      juce::String ringColor = knobSlider->ringColor;
      
      if (color == "secondary") {
        colorIn = SECONDARY_RGB[6];
        colorDotLine = SECONDARY_DARK_RGB[2];
        colorDot = SECONDARY_DARK_RGB[3];
      }
      if (ringColor == "secondary") {
        colorRing = SECONDARY_DARK_RGB[6];
      }
    }
    
    // auto bounds = juce::Rectangle<float>(x, y, width, height);
    float size = std::min(width, height);
    auto vw = size*0.001f;
    
    auto bounds = juce::Rectangle<float>(0, 0, size, size)
      .withCentre({ x + width * 0.5f, y + height * 0.5f });
    
    auto centre = bounds.getCentre();
    
    {
      auto radius = (size * 0.95f) / 2.0f;
      auto rx = centre.getX() - radius;
      auto ry = centre.getY() - radius;
      auto rw = radius * 2.0f;
      
      {
        auto lineThickness = vw * 2.0f;
        Path outlineArc;
        outlineArc.addCentredArc(
                                 rx + rw * 0.5f,  // 중심 X
                                 ry + rw * 0.5f,  // 중심 Y
                                 rw * 0.5f,       // X 반지름
                                 rw * 0.5f,       // Y 반지름
                                 0.0f,            // rotation
                                 rotaryStartAngle,
                                 rotaryEndAngle,
                                 true             // true = moveTo(startAngle) → 선만
                                 );
        g.setColour(colorDotLine.withAlpha(0.7f));
        g.strokePath (outlineArc, PathStrokeType (lineThickness));
      }
      
      // 2. 점 (circle)
      auto drawDot = [&](float rad) {
        auto radPosition = rad - juce::degreesToRadians(90.0f);
        float startX = centre.getX() + (radius * std::cos(radPosition));
        float startY = centre.getY() + (radius * std::sin(radPosition));
        float dotRadius = vw * 30.0f; // 라인 두께와 어울리게
        juce::Rectangle<float> dotArea(startX - dotRadius,
                                       startY - dotRadius,
                                       dotRadius * 2,
                                       dotRadius * 2);
        
        g.setColour(colorDot);
        
        g.fillEllipse(dotArea);
      };
      drawDot(rotaryStartAngle);
      drawDot(rotaryEndAngle);
    }
    
    auto knobBounds = bounds;
    knobBounds.reduce(size * 0.1f, size * 0.1f);
    // 노브 바깥쪽 그리기
    {
      g.setColour(colorRing);
      g.fillEllipse(knobBounds);
      
      // 윤곽선 그리기
      g.setColour(juce::Colours::black);
      g.drawEllipse(knobBounds, vw * 2.0f);
    }
    
    // Drop shadow 노브
    juce::Image knobImage(juce::Image::ARGB, width, height, true);
    
    // 노브 그리기
    {
      auto BoundsIn = knobBounds;
      BoundsIn.reduce(width * 0.07f, width * 0.07f);
      juce::Graphics g2(knobImage);
      g2.setColour(juce::Colours::lightblue);
      g2.fillEllipse(BoundsIn);
    }
    
    if ((vw * 25) > 1) {
      // Drop shadow 생성
      juce::DropShadow ds(
                          juce::Colours::black.withAlpha(0.9f),
                          static_cast<int>(vw * 120),
                          {0, static_cast<int>(vw * 150)});
      
      // 위치 변환 후 그림자 적용
      g.saveState();
      ds.drawForImage(g, knobImage);  // 이제 2개 인자
      g.restoreState();
    }
    
    
    // 안쪽 그리기
    {
      g.saveState();
      
      auto BoundsIn = knobBounds;
      BoundsIn.reduce(size * 0.08f, size * 0.08f);
      g.setColour(colorIn);
      g.fillEllipse(BoundsIn);
      
      //그라데이션 윤곽선
      juce::ColourGradient grad(
                                juce::Colours::white.withAlpha(1.0f),      // startColor
                                centre.x, centre.y - BoundsIn.getWidth()/2.0f,               // 시작점 (y1)
                                juce::Colour(PRIMARY_RGB[6]).withAlpha(0.0f), // primary-6 색상, 투명
                                centre.x, centre.y - BoundsIn.getWidth()/2.0f + BoundsIn.getWidth()/2.0f * 0.25f, // 끝점 y2 = 20% 지점
                                false                                      // radial = false → linear
                                );
      
      // Graphics에 Gradient 적용
      float angle = juce::degreesToRadians(330.0f);
      g.addTransform(juce::AffineTransform::rotation(angle, centre.x, centre.y));
      g.setGradientFill(grad);
      // g.addTransform(juce::AffineTransform::rotation(-angle, centre.x, centre.y));
      
      // 윤곽선 그리기
      auto BoundsInGradStroke = knobBounds;
      BoundsInGradStroke.reduce(size * 0.085f, size * 0.085f);
      g.drawEllipse(BoundsInGradStroke, vw * 16.0f);
      
      // 윤곽선 그리기
      auto BoundsInStroke = knobBounds;
      BoundsInStroke.reduce(size * 0.07f, size * 0.07f);
      g.setColour(juce::Colours::black);
      g.drawEllipse(BoundsInStroke, vw * 16.0f);
      
      g.restoreState();
    }
    
    
    {
      // Thumb 그리기
      float pointerThickness = vw * 48.0f; // 두께
      
      // 각도 계산
      float angle = juce::degreesToRadians(180.0f) + rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
      
      g.saveState();
      
      // 회전 변환
      g.addTransform(juce::AffineTransform::rotation(angle, centre.x, centre.y));
      
      // 선 그리기 (pointer)
      juce::Path pointer;
      pointer.startNewSubPath(centre.x, centre.y + (100.0f * vw)); // 시작점
      pointer.lineTo(centre.x, centre.y + (290.0f * vw)); // 종료점
      
      g.setColour(juce::Colours::white); // stroke color
      g.strokePath(pointer, juce::PathStrokeType(pointerThickness, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
      
      g.restoreState();
    }
  }
  
  juce::Font getTextButtonFont (juce::TextButton&, int buttonHeight) override
  {
    auto fontHeight = std::min<float>(UI_BUTTON_FONT_HEIGHT, buttonHeight);
    return juce::Font { fontMedium.withHeight(fontHeight) };
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
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomLookAndFeel)
};
