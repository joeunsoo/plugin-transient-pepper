
#pragma once

//==============================================================================
/** Custom Look And Feel subclasss.
 
 Simply override the methods you need to, anything else will be inherited from the base class.
 It's a good idea not to hard code your colours, use the findColour method along with appropriate
 ColourIds so you can set these on a per-component basis.
 */
struct CustomLookAndFeel : public LookAndFeel_V4
{
  void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override
  {
    // auto bounds = juce::Rectangle<float>(x, y, width, height);
    float size = std::min(width, height);
    auto vw = size*0.0010f;

    auto bounds = juce::Rectangle<float>(0, 0, size, size)
                     .withCentre({ x + width * 0.5f, y + height * 0.5f });
    auto knobBounds = bounds;
    knobBounds.reduce(size * 0.1f, size * 0.1f);

    auto centre = knobBounds.getCentre();
    float radius = size / 2.0f;
    
    g.setColour(PRIMARY_DARK_RGB[6]);
    g.fillEllipse(knobBounds);
    
    // 윤곽선 그리기
    g.setColour(juce::Colours::black);
    g.drawEllipse(knobBounds, vw * 2.0f);
    
    // Drop shadow 노브
    juce::Image knobImage(juce::Image::ARGB, width, height, true);

    // 노브 그리기
    {
      auto BoundsIn = knobBounds;
      BoundsIn.reduce(width*0.07f, width*0.07f);
        juce::Graphics g2(knobImage);
        g2.setColour(juce::Colours::lightblue);
        g2.fillEllipse(BoundsIn);
    }

    // Drop shadow 생성
    juce::DropShadow ds(juce::Colours::black.withAlpha(0.9f), static_cast<int>(vw * 25), {0, static_cast<int>(vw * 25)});

    // 위치 변환 후 그림자 적용
    g.saveState();
    // g.addTransform(juce::AffineTransform::translation(centre.getX(), centre.getY()));
    ds.drawForImage(g, knobImage);  // 이제 2개 인자
    g.restoreState();


    // 안쪽 그리기
    {
      g.saveState();

      auto BoundsIn = knobBounds;
      BoundsIn.reduce(size * 0.1f, size * 0.1f);
      g.setColour(PRIMARY_RGB[6]);
      g.fillEllipse(BoundsIn);
      
      //그라데이션 윤곽선
      juce::ColourGradient grad(
          juce::Colours::white.withAlpha(1.0f),      // startColor
          centre.x, centre.y - BoundsIn.getWidth()/2.0f,               // 시작점 (y1)
          juce::Colour(PRIMARY_RGB[6]).withAlpha(0.0f), // primary-6 색상, 투명
          centre.x, centre.y - BoundsIn.getWidth()/2.0f + BoundsIn.getWidth()/2.0f * 0.2f, // 끝점 y2 = 20% 지점
          false                                      // radial = false → linear
      );

      // Graphics에 Gradient 적용
      float angle = juce::degreesToRadians(305.0f);
      g.addTransform(juce::AffineTransform::rotation(angle, centre.x, centre.y));
      g.setGradientFill(grad);
      // g.addTransform(juce::AffineTransform::rotation(-angle, centre.x, centre.y));

      // 윤곽선 그리기
      auto BoundsInGradStroke = knobBounds;
      BoundsInGradStroke.reduce(size * 0.1f, size * 0.1f);
      g.drawEllipse(BoundsInGradStroke, vw * 4.0f);

      // 윤곽선 그리기
      auto BoundsInStroke = knobBounds;
      BoundsInStroke.reduce(size * 0.09f, size * 0.09f);
      g.setColour(juce::Colours::black);
      g.drawEllipse(BoundsInStroke, vw * 6.0f);

      g.restoreState();
    }

    
    {
      // Thumb 그리기
      float pointerThickness = vw * 32.0f; // 두께
      
      // 각도 계산
      float angle = juce::degreesToRadians(180.0f) + rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
      
      g.saveState();
      
      // 회전 변환
      g.addTransform(juce::AffineTransform::rotation(angle, centre.x, centre.y));
      
      // 선 그리기 (pointer)
      juce::Path pointer;
      pointer.startNewSubPath(centre.x, centre.y + (75.0f * vw)); // 시작점
      pointer.lineTo(centre.x, centre.y + (300.0f * vw)); // 종료점
      
      g.setColour(juce::Colours::white); // stroke color
      g.strokePath(pointer, juce::PathStrokeType(pointerThickness, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
      
      g.restoreState();
    }
  }
};
