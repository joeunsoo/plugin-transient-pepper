/*
 ==============================================================================
 
 PluginAudioProcessor.h
 Created: 31 Aug 2025 10:22:01pm
 Author:  JoEunsoo
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>
#include "NamespaceParameterId.h"
#include "PluginParameters.h"

#include "PeakMeter.h"
#include "DCOffsetFilter.h"
#include "TransientNoise.h"
#include "MidSideMixer.h"
#include "TiltEQ.h"

//==============================================================================
class PluginAudioProcessor  : public AudioProcessor
{
  public:
  //==============================================================================
  PluginAudioProcessor (AudioProcessorValueTreeState::ParameterLayout layout);
  ~PluginAudioProcessor() override;
  
  //==============================================================================
  void prepareToPlay (double sampleRate, int samplesPerBlock) override;
  void releaseResources() override {}
  
  bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
  
  void processBlock (AudioBuffer<float>&, MidiBuffer&) override;
  using AudioProcessor::processBlock;
  
  //==============================================================================
  const String getName() const override        { return JucePlugin_Name; }
  
  bool acceptsMidi() const override            { return false; }
  bool producesMidi() const override           { return false; }
  bool isMidiEffect() const override           { return false; }
  double getTailLengthSeconds() const override { return 0.0; }
  
  //==============================================================================
  int getNumPrograms() override                        { return 1; }
  int getCurrentProgram() override                     { return 0; }
  void setCurrentProgram (int) override                {}
  const String getProgramName (int) override           { return {}; }
  void changeProgramName (int, const String&) override {}
  
  //==============================================================================
  void getStateInformation (MemoryBlock& destData) override;
  void setStateInformation (const void* data, int sizeInBytes) override;
  
  
  double sampleRate = 44100.0;
  
  Parameters parameters;
  AudioProcessorValueTreeState state;
  
  dsp::Gain<float> noiseLevelGain;
  dsp::Gain<float> tiltGain;
  dsp::Gain<float> outputGain;
  
  TiltEQProcessor<float> tiltEQ;
  
  juce::dsp::DryWetMixer<float> dryWetMixer;
  
  TransientNoiseProcessor<float> transientNoise;
  MidSideMixer<float> midSideMixer;

  /*
   0, 1 = L,R 출력 피크 레벨
  */
  std::vector<float> analysisData = [] { return std::vector<float> (16, 0.0f); }();

  SpinLock peakDataLock;
  PeakMeter peakMeter;
  PeakMeter noisePeakMeter;
  
  DCOffsetFilter<float> dcBlocker;

  int windowScale;
  
  private:
  juce::ApplicationProperties appProperties;
  juce::PropertiesFile* props = nullptr; // 소유권은 ApplicationProperties가 관리
  
  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginAudioProcessor)
  
};
