#pragma once
#include "../AudioProcessor/PluginAudioProcessor.h"
#include "Header/HeaderComponent.h"
#include "Main/MainComponent.h"
#include "Main/DetectorComponent.h"

class PluginEditor : public juce::AudioProcessorEditor
{
  public:
  PluginEditor(PluginAudioProcessor& p);
  ~PluginEditor() override;
  
  void paint(juce::Graphics& g) override;
  void resized() override;
  
  void setScale(int scale);
  //==============================================================================
  juce::Typeface::Ptr pretendardMediumTypeface;
  juce::Typeface::Ptr pretendardSemiBoldTypeface;
  juce::Typeface::Ptr pretendardBoldTypeface;
  //==============================================================================
  private:
  PluginAudioProcessor& processorRef;
  
  HeaderComponent headerComponent;
  MainComponent mainComponent;
  DetectorComponent detectorComponent;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};
