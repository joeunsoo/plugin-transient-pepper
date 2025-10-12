// Fonts.h
#pragma once
#include <JuceHeader.h>

// 각 굵기별 Typeface 캐시
inline const juce::Typeface::Ptr& PretendardRegularTypeface()
{
    static juce::Typeface::Ptr tf =
        juce::Typeface::createSystemTypefaceFor(BinaryData::PretendardStdRegular_otf,
                                                BinaryData::PretendardStdRegular_otfSize);
    return tf;
}

inline const juce::Typeface::Ptr& PretendardMediumTypeface()
{
    static juce::Typeface::Ptr tf =
        juce::Typeface::createSystemTypefaceFor(BinaryData::PretendardStdMedium_otf,
                                                BinaryData::PretendardStdMedium_otfSize);
    return tf;
}

inline const juce::Typeface::Ptr& PretendardSemiBoldTypeface()
{
    static juce::Typeface::Ptr tf =
        juce::Typeface::createSystemTypefaceFor(BinaryData::PretendardStdSemiBold_otf,
                                                BinaryData::PretendardStdSemiBold_otfSize);
    return tf;
}

inline const juce::Typeface::Ptr& PretendardBoldTypeface()
{
    static juce::Typeface::Ptr tf =
        juce::Typeface::createSystemTypefaceFor(BinaryData::PretendardStdBold_otf,
                                                BinaryData::PretendardStdBold_otfSize);
    return tf;
}

// 각 굵기별 FontOptions 캐시
inline const juce::FontOptions& PretendardRegularOptions()
{
    static juce::FontOptions opts{ PretendardRegularTypeface() };
    return opts;
}

inline const juce::FontOptions& PretendardMediumOptions()
{
    static juce::FontOptions opts{ PretendardMediumTypeface() };
    return opts;
}

inline const juce::FontOptions& PretendardSemiBoldOptions()
{
    static juce::FontOptions opts{ PretendardSemiBoldTypeface() };
    return opts;
}

inline const juce::FontOptions& PretendardBoldOptions()
{
    static juce::FontOptions opts{ PretendardBoldTypeface() };
    return opts;
}

// 매크로: "상수처럼" 사용하기 위한 래퍼
#define FONT_PRETENDARD_REGULAR   PretendardRegularOptions()
#define FONT_PRETENDARD_MEDIUM    PretendardMediumOptions()
#define FONT_PRETENDARD_SEMIBOLD  PretendardSemiBoldOptions()
#define FONT_PRETENDARD_BOLD      PretendardBoldOptions()
