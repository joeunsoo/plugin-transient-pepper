#pragma once

#include <JuceHeader.h>
#include "AudioProcessor/PluginAudioProcessor.h"
#include "PluginEditor/PluginEditor.h"

class PluginAudioProcessorWrapper  : public PluginAudioProcessor
{
  public:
  PluginAudioProcessorWrapper()  : PluginAudioProcessor ({})
  {}
  
  bool hasEditor() const override               { return true; }
  AudioProcessorEditor* createEditor() override {
    return new PluginEditor (*this);
  }
};

