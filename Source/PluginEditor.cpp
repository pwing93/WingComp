/*
  ==============================================================================

    Plugin GUI Editor Compressor
    Author: Peter Wing - April 2020

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WingCompAudioProcessorEditor::WingCompAudioProcessorEditor (WingCompAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    //sets plugin window size
    setSize (700, 400);
    
    
    //this is the rotary control for the LA2A input gain control
    inGainSlider.setSliderStyle(Slider::Rotary);
    inGainSlider.setRange(0, 100, 1);
    inGainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 150, 20);
    inGainSlider.setPopupDisplayEnabled(true, false, this);
    inGainSlider.setTextValueSuffix(" Gain");
    inGainSlider.setValue(32);
    inGainSlider.addListener(this);
    
    //this is the rotary control for the gain reduction control of the LA2A
    peakReductionSlider.setSliderStyle(Slider::Rotary);
    peakReductionSlider.setRange(-60.0, 0.0, 0.03);
    peakReductionSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 150, 20);
    peakReductionSlider.setPopupDisplayEnabled(true, false, this);
    peakReductionSlider.setTextValueSuffix(" Peak Reduction");
    peakReductionSlider.setValue(0.0);
    peakReductionSlider.addListener(this);
    
    
    addAndMakeVisible(inGainSlider);
    addAndMakeVisible(peakReductionSlider);
}

WingCompAudioProcessorEditor::~WingCompAudioProcessorEditor()
{
}

//==============================================================================
void WingCompAudioProcessorEditor::paint (Graphics& g)
{
    // Background fill colour and TELETRONIX style text
    g.fillAll (Colours::gainsboro);
    g.setColour (Colours::firebrick);
    g.setFont (27.0);
    g.drawFittedText ("WINGCOMP Ver3.8.2", 40, 40, 175, 50, Justification::centred, 1);
}

void WingCompAudioProcessorEditor::resized()
{
    // subcomponents in plugin window
    
    inGainSlider.setSize(150, 150);
    inGainSlider.setCentrePosition(120, 240);
    
    peakReductionSlider.setSize(150, 150);
    peakReductionSlider.setCentrePosition(580, 240);
}

// Changes Plugin Parameters using controls
void WingCompAudioProcessorEditor::sliderValueChanged (Slider *slider)
{
    if (slider == &inGainSlider)
    {
        processor.inGain = inGainSlider.getValue();
    }
    
    if (slider == &peakReductionSlider)
    {
        processor.peakReduction = peakReductionSlider.getValue();
    }
}


