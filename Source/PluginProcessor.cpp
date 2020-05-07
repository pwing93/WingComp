/*
  ==============================================================================

    Plugin Processor Compressor
    Author: Peter Wing - April 2020

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WingCompAudioProcessor::WingCompAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

WingCompAudioProcessor::~WingCompAudioProcessor()
{
}

//==============================================================================
const String WingCompAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool WingCompAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool WingCompAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool WingCompAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double WingCompAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int WingCompAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int WingCompAudioProcessor::getCurrentProgram()
{
    return 0;
}

void WingCompAudioProcessor::setCurrentProgram (int index)
{
}

const String WingCompAudioProcessor::getProgramName (int index)
{
    return {};
}

void WingCompAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void WingCompAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // any pre - playback initialisation needed
}

void WingCompAudioProcessor::releaseResources()
{
    // Free up spare memory etc. after playback
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool WingCompAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // mono or Stereo only supported
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void WingCompAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    //
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    //
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        
        //This is where our signal processing actually happens
        for (int sample = 0; sample < buffer.getNumSamples(); sample++)
        {
            //Input gain stage
            inGainScaled = inGain / 32;
            channelData [sample] = channelData [sample] * inGainScaled;
            
            //Copy leveled input to detection circuit and rectify
            detectionSignal = channelData [sample];
            detectionSignal = fabsf(detectionSignal);
            
            //TO DO: Put Envelope Shaping application here
            
            //Process signal if above threshold with conditional
            detectionSignal = amplitudeToDecibel(detectionSignal);
            
            //Temporary conversion of peak reduction control level straight to threshold
            //TO DO: implement scaling algoritm for peak reduction control
            threshold = peakReduction;
            
            if (detectionSignal > threshold)
            {
                //formula for and apply amount of signal compression
                float ratioScaled = 1.0 - (1.0 / ratio);
                float compression = ratioScaled * (threshold - detectionSignal);
                compression = decibelToAmplitude(compression);
                
                channelData [sample] = channelData [sample] * compression;

            }
            
            
        }
        // ..do something to the data...
    }
    
    
}

//==============================================================================
bool WingCompAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* WingCompAudioProcessor::createEditor()
{
    return new WingCompAudioProcessorEditor (*this);
}

//==============================================================================
void WingCompAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // Use this method to store parameters in the memory block
    
}

void WingCompAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // Use this method to restore parameters from this memory block

}

//==============================================================================
// This creates new instances of the plugin
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new WingCompAudioProcessor();
}
