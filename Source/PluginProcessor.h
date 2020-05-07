/*
  ==============================================================================

    Plugin Processor Compressor - Header File
    Author: Peter Wing - April 2020

  ==============================================================================
*/

#include <JuceHeader.h>
#pragma once

//==============================================================================
/**
*/
class WingCompAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    WingCompAudioProcessor();
  
    ~WingCompAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

//Plugin Parameters expressed in variables
    float inGain { 32 };
    float inGainScaled;
    
    float outGain;
    
    float detectionSignal;
    
    float peakReduction { 0.0 };
    float threshold;
    float thresholdScaled;
    
    float ratio { 4 };
    float attack;
    float release;
    
// Plugin functions defined here
    
    // Amplitude to decibel conversion
    float amplitudeToDecibel(float amplitude)
    {
        return 20.f * log10(amplitude);
    }
    
    // Decibel to amplitude conversion
    float decibelToAmplitude(float decibel)
    {
        return pow(10.f, decibel / 20.f);
    }
    
private:
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WingCompAudioProcessor)
};
