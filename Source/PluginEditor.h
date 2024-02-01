/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class SynthDemov2AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
	SynthDemov2AudioProcessorEditor (SynthDemov2AudioProcessor&);
	~SynthDemov2AudioProcessorEditor() override;

	//==============================================================================
	void paint (juce::Graphics&) override;
	void resized() override;

private:
	SynthDemov2AudioProcessor& audioProcessor;
	
	//Filters
	juce::AudioParameterFloat* lowPassCutoffFrequencyParameter;
	juce::Slider lowPassKnob;
	juce::Label lowPassLabel;
	
	juce::AudioParameterFloat* highPassCutoffFrequencyParameter;
	juce::Slider highPassKnob;
	juce::Label highPassLabel;
	
	juce::AudioParameterFloat* distortParameter;
	juce::Slider distortSlider;
	juce::Label distortLabel;
	
	
	juce::Slider gainSlider;
	juce::AudioParameterFloat* gainParameter;
	juce::Label gainLabel;
	
	//Synth Stuff
	juce::Slider sawSlider;
	juce::AudioParameterFloat* sawParameter;
	juce::Label sawLabel;
	juce::Slider sineSlider;
	juce::AudioParameterFloat* sineParameter;
	juce::Label sineLabel;
	juce::Slider squareSlider;
	juce::AudioParameterFloat* squareParameter;
	juce::Label squareLabel;
	juce::Slider triangleSlider;
	juce::AudioParameterFloat* triangleParameter;
	juce::Label triangleLabel;
	
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthDemov2AudioProcessorEditor)
};
