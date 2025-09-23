#pragma once

#include <JuceHeader.h>
#include "../Assets/DemoUtilities.h"
#include "AudioProcessor/PluginAudioProcessor.h"
#include "WebviewPluginEditor/WebviewPluginEditor.h"
#include "PluginEditor/PluginEditor.h"

class PluginAudioProcessorWrapper  : public PluginAudioProcessor
{
  public:
  PluginAudioProcessorWrapper()  : PluginAudioProcessor ({})
  {}
  
  bool hasEditor() const override               { return true; }
  AudioProcessorEditor* createEditor() override {
    // return new WebviewPluginEditor (*this);
    return new PluginEditor (*this);
  }
};
