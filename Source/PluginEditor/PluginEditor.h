#pragma once

#include "../AudioProcessor/PluginAudioProcessor.h"
#include "../PluginWrapper.h"

#include "DefineUI.h"
#include "Provider/Providers.h"
#include "Provider/ScaleProvider.h"
#include "Provider/ScaleController.h"
#include "Provider/EditorProvider.h"
#include "Provider/AudioProcessorProvider.h"
#include "Provider/WrapperLicenseProvider.h"

#include "Header/HeaderComponent.h"
#include "Main/MainComponent.h"
#include "UI/RoundedLabel.h"
#include "Modal/AboutModal.h"
#include "Modal/ActivateModal.h"

class PluginEditor : public juce::AudioProcessorEditor,
public ScaleProvider,
public ScaleController,
public EditorProvider
{
  public:
  PluginEditor(PluginAudioProcessor& p);
  ~PluginEditor() override;
  
  void paint(juce::Graphics& g) override;
  void resized() override;
  
  void setScale(int scale) noexcept override;
  void showTooltipAt(String id, const juce::Rectangle<int>& area, const juce::String& text) const noexcept override;
  
  void setTooltipLabelVisible(bool value) const noexcept override;
  
  void setDrag(bool value, String id) noexcept override;
  void showAbout() override;
  void showActivate() override;
  //==============================================================================
  PluginAudioProcessor& processorRef;
  PluginWrapper& wrapperRef;
  //==============================================================================
  
  std::unique_ptr<RoundedLabel> tooltipLabel;
  //==============================================================================
  private:
  bool isDrag = false;
  String dragID;
  //==============================================================================
  
  AudioProcessorProvider processorProvider;
  WrapperLicenseProvider   licenseProvider;
  
  // Providers 집합 멤버 추가: Editor 자신을 ScaleProvider로 전달
  Providers providers;
  
  HeaderComponent headerComponent;
  MainComponent mainComponent;
  
  AboutModal aboutModal;
  ActivateModal activateModal;
  
  //==============================================================================
  float getScale () const noexcept override
  {
    return getLocalBounds().toFloat().getWidth() / 640.0f;
  }
  int getWindowScale () const noexcept override
  {
    return wrapperRef.windowScale;
  }
  
  Point<int> getLocalPointInEditor (const Component* source, Point<int> point) const override
  {
    return getLocalPoint (source, point);
  }

  Point<float> getLocalPointInEditor (const Component* source, Point<float> point) const override {
    return getLocalPoint (source, point);
  }
  //==============================================================================
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};
