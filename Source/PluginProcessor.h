/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Oscillator/AuxPort_Synth.h"

//==============================================================================
/**
*/

namespace Adin {

class Conversions
{
public:
	static float linearToDB(const float& sample) {
		return 20*log10f(sample);
		}
		static float DBtoLinear(const float& sample) {
			return powf(10, sample/10);
		}
	};
};


class SynthDemov2AudioProcessor  : public juce::AudioProcessor
{
public:
	//==============================================================================
	SynthDemov2AudioProcessor();
	~SynthDemov2AudioProcessor() override;

	//==============================================================================
	void prepareToPlay (double sampleRate, int samplesPerBlock) override;
	void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
	bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

	void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

	//==============================================================================
	juce::AudioProcessorEditor* createEditor() override;
	bool hasEditor() const override;

	//==============================================================================
	const juce::String getName() const override;

	bool acceptsMidi() const override;
	bool producesMidi() const override;
	bool isMidiEffect() const override;
	double getTailLengthSeconds() const override;

	//==============================================================================
	int getNumPrograms() override;
	int getCurrentProgram() override;
	void setCurrentProgram (int index) override;
	const juce::String getProgramName (int index) override;
	void changeProgramName (int index, const juce::String& newName) override;

	//==============================================================================
	void getStateInformation (juce::MemoryBlock& destData) override;
	void setStateInformation (const void* data, int sizeInBytes) override;

private:
	//==============================================================================
	AuxPort::Synth synth;
	
	//Filter Stuff
	juce::dsp::IIR::Filter<float> lowPassFilter;
	juce::dsp::IIR::Filter<float> lowPassFilterR;
	juce::dsp::ProcessSpec lowPassProcessSpec;
	juce::AudioParameterFloat * lowPassParameter;
	
	juce::dsp::IIR::Filter<float> highPassFilter;
	juce::dsp::IIR::Filter<float> highPassFilterR;
	juce::dsp::ProcessSpec highPassProcessSpec;
	juce::AudioParameterFloat * highPassParameter;
	
	juce::dsp::ProcessSpec spec;
 
	juce::AudioParameterFloat* distortParameter;
 
	juce::AudioParameterFloat* gainParameter;
	
	//synth stuff
	juce::AudioParameterFloat * sawParameter;
	juce::AudioParameterFloat * sineParameter;
	juce::AudioParameterFloat * squareParameter;
	juce::AudioParameterFloat * triangleParameter;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthDemov2AudioProcessor)
};
