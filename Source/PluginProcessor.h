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

    float inGain { 32 };
    float inGainScaled;
    
    float outGain;
    
    float detectionSignal;
    
    float peakReduction { 0 };
    float threshold;
    float thresholdScaled;
    
    float ratio;
    float attack;
    float release;
    
private:
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WingCompAudioProcessor)
};
