/*
  ==============================================================================

    Plugin GUI Editor Compressor - Header File
    Author: Peter Wing - April 2020

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class WingCompAudioProcessorEditor  : public AudioProcessorEditor,
public Slider::Listener
{
public:
    WingCompAudioProcessorEditor (WingCompAudioProcessor&);
    ~WingCompAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void sliderValueChanged (Slider* slider) override;

private:
    
    // access the processor object
    WingCompAudioProcessor& processor;
    
    Slider inGainSlider;
    Slider peakReductionSlider;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WingCompAudioProcessorEditor)
};
