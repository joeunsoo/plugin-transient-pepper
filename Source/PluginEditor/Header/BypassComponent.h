#pragma once

#include "../Provider/ProcessorProvider.h"
#include <JuceHeader.h>

//==============================================================================
class BypassComponent : public juce::ToggleButton {
public:
  BypassComponent(ProcessorProvider &pp);
  ~BypassComponent() override;

  void resized() override {}

  //==============================================================================
protected:
  bool hitTest(int x, int y) override;
  void paintButton(juce::Graphics &g, bool isMouseOver, bool isMouseDown) override;

  //==============================================================================
private:
  std::unique_ptr<juce::Drawable> normalSvg, overSvg, downSvg;
  std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> bypassAttachment;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BypassComponent)
};
