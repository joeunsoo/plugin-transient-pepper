#pragma once

#include <JuceHeader.h>

class RoundedLabel : public juce::Label
{
public:
    RoundedLabel() = default;

    void paint(juce::Graphics& g) override
    {
        auto bounds = getLocalBounds().toFloat();
        float radius = UI_TOOLTIP_BORDER_RADIUS; // 원하는 border-radius

        // 배경
        g.setColour(findColour(backgroundColourId));
        g.fillRoundedRectangle(bounds, radius);

        // 텍스트
        g.setColour(findColour(textColourId));
        g.setFont(getFont());
        g.drawFittedText(getText(), getLocalBounds(), getJustificationType(), 1);
    }
};

