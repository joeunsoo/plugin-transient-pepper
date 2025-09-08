#pragma once

#include <JuceHeader.h>
#include "DemoUtilities.h"
#include "PluginAudioProcessor.h"
#include "PluginAudioEditor.h"

class PluginAudioProcessorWrapper  : public PluginAudioProcessor
{
    public:
    PluginAudioProcessorWrapper()  : PluginAudioProcessor ({})
    {}
    
    bool hasEditor() const override               { return true; }
    AudioProcessorEditor* createEditor() override {
        return new PluginAudioEditor (*this);
    }
};
