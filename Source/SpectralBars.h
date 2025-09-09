/*
 ==============================================================================
 
 SpectralBars.h
 Created: 9 Sep 2025 9:51:29pm
 Author:  JoEunsoo
 
 ==============================================================================
 */

#pragma once

class CircularBuffer
{
  public:
  CircularBuffer (int numChannels, int numSamples)
  : buffer (data, (size_t) numChannels, (size_t) numSamples)
  {
  }
  
  template <typename T>
  void push (dsp::AudioBlock<T> b)
  {
    jassert (b.getNumChannels() == buffer.getNumChannels());
    
    const auto trimmed = b.getSubBlock (  b.getNumSamples()
                                        - std::min (b.getNumSamples(), buffer.getNumSamples()));
    
    const auto bufferLength = (int64) buffer.getNumSamples();
    
    for (auto samplesRemaining = (int64) trimmed.getNumSamples(); samplesRemaining > 0;)
    {
      const auto writeOffset = writeIx % bufferLength;
      const auto numSamplesToWrite = std::min (samplesRemaining, bufferLength - writeOffset);
      
      auto destSubBlock = buffer.getSubBlock ((size_t) writeOffset, (size_t) numSamplesToWrite);
      const auto sourceSubBlock = trimmed.getSubBlock (trimmed.getNumSamples() - (size_t) samplesRemaining,
                                                       (size_t) numSamplesToWrite);
      
      destSubBlock.copyFrom (sourceSubBlock);
      
      samplesRemaining -= numSamplesToWrite;
      writeIx += numSamplesToWrite;
    }
  }
  
  template <typename T>
  void push (Span<T> s)
  {
    auto* ptr = s.begin();
    dsp::AudioBlock<T> b (&ptr, 1, s.size());
    push (b);
  }
  
  void read (int64 readIx, dsp::AudioBlock<float> output) const
  {
    const auto numChannelsToUse = std::min (buffer.getNumChannels(), output.getNumChannels());
    
    jassert (output.getNumChannels() == buffer.getNumChannels());
    
    const auto bufferLength = (int64) buffer.getNumSamples();
    
    for (auto outputOffset = (size_t) 0; outputOffset < output.getNumSamples();)
    {
      const auto inputOffset = (size_t) ((readIx + (int64) outputOffset) % bufferLength);
      const auto numSamplesToRead = std::min (output.getNumSamples() - outputOffset,
                                              (size_t) bufferLength - inputOffset);
      
      auto destSubBlock = output.getSubBlock (outputOffset, numSamplesToRead)
        .getSubsetChannelBlock (0, numChannelsToUse);
      
      destSubBlock.copyFrom (buffer.getSubBlock (inputOffset, numSamplesToRead)
                             .getSubsetChannelBlock (0, numChannelsToUse));
      
      outputOffset += numSamplesToRead;
    }
  }
  
  int64 getWriteIndex() const noexcept { return writeIx; }
  
  private:
  HeapBlock<char> data;
  dsp::AudioBlock<float> buffer;
  int64 writeIx = 0;
};


class SpectralBars
{
  public:
  static constexpr int getNumBars() noexcept
  {
    return analysisWindowWidth / 2;
  }
  
  template <typename T>
  void push (Span<T> data)
  {
    buffer.push (data);
  }
  
  void compute (Span<float> output)
  {
    auto* ptr = output.begin();
    auto result = dsp::AudioBlock<float> (&ptr, 1, output.size());
    result.clear();
    auto analysisData = fftTmp.getSubBlock (0, analysisWindowWidth);
    
    for (int i = 0; i < numAnalysisWindows; ++i)
    {
      buffer.read (0 + i * analysisWindowOverlap, analysisData);
      fft.performFrequencyOnlyForwardTransform (fftTmp.getChannelPointer (0), true);
      result.add (analysisData);
    }
    
    result.multiplyBy (1.0f / numAnalysisWindows);
  }
  
  static inline constexpr int64 fftOrder            = 5;
  static inline constexpr int64 analysisWindowWidth = 1 << fftOrder;
  static inline constexpr int numAnalysisWindows    = 16;
  static inline constexpr int analysisWindowOverlap = analysisWindowWidth / 2;
  
  private:
  dsp::FFT fft { fftOrder };
  
  HeapBlock<char> fftTmpData;
  dsp::AudioBlock<float> fftTmp { fftTmpData, 1, (size_t) (2 * fft.getSize()) };
  
  CircularBuffer buffer { 1, (int) analysisWindowWidth
    + (numAnalysisWindows - 1) * analysisWindowOverlap };
};

