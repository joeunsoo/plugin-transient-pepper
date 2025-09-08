/*
 ==============================================================================
 
 PluginAudioProcessor.cpp
 Created: 3 Sep 2025 11:01:38am
 Author:  JoEunsoo
 
 ==============================================================================
 */

#include <JuceHeader.h>
#include "PluginAudioProcessor.h"


//==============================================================================
PluginAudioProcessor::PluginAudioProcessor (AudioProcessorValueTreeState::ParameterLayout layout)
: AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                  .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
#endif
                  .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
#endif
                  ),
parameters (layout),
state (*this, nullptr, "STATE", std::move (layout))
{
    // PropertiesFile 옵션 설정
    juce::PropertiesFile::Options options;
    options.applicationName     = "preferences";
    options.filenameSuffix      = ".xml";
    options.folderName          = "JoEunsoo/RustyTone"; // macOS: ~/Library/Application Support/JoEunsoo/RustyTone.settings
    options.osxLibrarySubFolder = "Application Support";
    options.storageFormat       = juce::PropertiesFile::storeAsXML;

    // ApplicationProperties 객체를 통해 관리
    appProperties.setStorageParameters(options);

    // PropertiesFile 가져오기
    props = appProperties.getUserSettings();

    // 값 불러오기
    windowScale  = props->getIntValue("windowScale", 100);
}

//==============================================================================
PluginAudioProcessor::~PluginAudioProcessor()
{
    // 종료 시 값 저장
    props->setValue("windowScale", windowScale);

    props->saveIfNeeded();
}

//==============================================================================
void PluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    const auto channels = std::max (getTotalNumInputChannels(), getTotalNumOutputChannels());
    
    if (channels == 0)
        return;
    
    const juce::dsp::ProcessSpec spec =
    { sampleRate, (uint32_t) samplesPerBlock, (uint32_t) channels };
    
    sampleRate = spec.sampleRate;
    
    dcBlocker.prepare(spec);
    dcBlocker.reset();
    antiAliasingFilter.prepare(spec);
    antiAliasingFilter.reset();
    
    saturation.prepare (spec);
    saturation.reset();
    
    preEQ.prepare(spec);
    postEQ.prepare(spec);
    tiltEQ.prepare(spec);
    
    inputGain.setGainDecibels(0.0f);
    inputGain.reset();
    outputGain.setGainDecibels(0.0f);
    outputGain.reset();
    
    dryWetMixer.setMixingRule (juce::dsp::DryWetMixingRule::linear);
    dryWetMixer.prepare (spec);
    dryWetMixer.setWetMixProportion (1.0f);
}

bool PluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;
    
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
    
    return true;
}

void PluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                         juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
    
    const auto totalNumInputChannels  = getTotalNumInputChannels();
    const auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    inputGain.setGainDecibels(parameters.inputGain.get());
    outputGain.setGainDecibels(parameters.outputGain.get());
    
    saturation.setDrive(parameters.saturationDrive.get());
    
    preEQ.setGain(parameters.emphasis.get());
    postEQ.setGain(0-parameters.emphasis.get());
    tiltEQ.setGain(parameters.tilt.get());
    
    dryWetMixer.setWetMixProportion (parameters.dryWet.get() / 100.0f);
    
    auto outBlock = dsp::AudioBlock<float> { buffer }.getSubsetChannelBlock (0, (size_t) getTotalNumOutputChannels());
    
    if (!parameters.bypass.get()) {
        
        inputGain.process(dsp::ProcessContextReplacing<float> (outBlock));
        
        dryWetMixer.pushDrySamples (outBlock); // Dry 신호 저장
        
        preEQ.process(dsp::ProcessContextReplacing<float> (outBlock));
        
        saturation.process(dsp::ProcessContextReplacing<float> (outBlock));
        
        postEQ.process(dsp::ProcessContextReplacing<float> (outBlock));
        
        tiltEQ.process(dsp::ProcessContextReplacing<float> (outBlock));
        
        dryWetMixer.mixWetSamples (outBlock); // Dry/Wet 믹스
        
        dcBlocker.process(dsp::ProcessContextReplacing<float> (outBlock));
        
        outputGain.process(dsp::ProcessContextReplacing<float> (outBlock));
        
        antiAliasingFilter.process(dsp::ProcessContextReplacing<float> (outBlock));
    }
    
}

//==============================================================================
void PluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::ignoreUnused (destData);
}

void PluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    juce::ignoreUnused (data, sizeInBytes);
}
