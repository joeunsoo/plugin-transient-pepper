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
  void showTooltipAt(String id, const juce::Rectangle<int>& area, const juce::String& text);

  void setDrag(bool value, String id);
  //==============================================================================
  PluginAudioProcessor& processorRef;

  
  juce::FontOptions fontMedium {juce::Typeface::createSystemTypefaceFor(BinaryData::PretendardStdMedium_otf, BinaryData::PretendardStdMedium_otfSize)};
  juce::FontOptions fontSemiBold {juce::Typeface::createSystemTypefaceFor(BinaryData::PretendardStdSemiBold_otf, BinaryData::PretendardStdSemiBold_otfSize)};
  juce::FontOptions fontBold {juce::Typeface::createSystemTypefaceFor(BinaryData::PretendardStdBold_otf, BinaryData::PretendardStdBold_otfSize)};
  
  std::unique_ptr<juce::Label> tooltipLabel;
  bool isDrag = false;
  String dragID;
  //==============================================================================
  private:
  
  HeaderComponent headerComponent;
  MainComponent mainComponent;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};
