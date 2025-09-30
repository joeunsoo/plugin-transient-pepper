#pragma once

#include "../AudioProcessor/PluginAudioProcessor.h"
#include "../PluginWrapper.h"
#include "Header/HeaderComponent.h"
#include "Main/MainComponent.h"
#include "UI/RoundedLabel.h"
#include "Modal/AboutModal.h"
#include "Modal/ActivateModal.h"

class PluginWrapper;

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
  void showAbout();
  void showActivate();

  //==============================================================================
  PluginAudioProcessor& processorRef;
  PluginWrapper& wrapperRef;
  //==============================================================================
  
  juce::FontOptions fontPretendardRegular {juce::Typeface::createSystemTypefaceFor(BinaryData::PretendardStdRegular_otf, BinaryData::PretendardStdRegular_otfSize)};
  juce::FontOptions fontPretendardMedium {juce::Typeface::createSystemTypefaceFor(BinaryData::PretendardStdMedium_otf, BinaryData::PretendardStdMedium_otfSize)};
  juce::FontOptions fontPretendardSemiBold {juce::Typeface::createSystemTypefaceFor(BinaryData::PretendardStdSemiBold_otf, BinaryData::PretendardStdSemiBold_otfSize)};
  juce::FontOptions fontPretendardBold {juce::Typeface::createSystemTypefaceFor(BinaryData::PretendardStdBold_otf, BinaryData::PretendardStdBold_otfSize)};
  
  std::unique_ptr<RoundedLabel> tooltipLabel;
  bool isDrag = false;
  String dragID;
  //==============================================================================
  private:
  
  HeaderComponent headerComponent;
  MainComponent mainComponent;
  
  AboutModal aboutModal;
  ActivateModal activateModal;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};
