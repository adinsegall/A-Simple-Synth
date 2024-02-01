/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthDemov2AudioProcessorEditor::SynthDemov2AudioProcessorEditor (SynthDemov2AudioProcessor& p)
	: AudioProcessorEditor (&p), audioProcessor (p)
{
	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize (650, 550);
	
	addAndMakeVisible(sawSlider);
	addAndMakeVisible(sineSlider);
	addAndMakeVisible(squareSlider);
	addAndMakeVisible(triangleSlider);
	addAndMakeVisible(lowPassKnob);
	addAndMakeVisible(highPassKnob);
	addAndMakeVisible(gainSlider);
	addAndMakeVisible(distortSlider);
	
	
	sawLabel.setText("Saw", juce::dontSendNotification);
	sawLabel.attachToComponent(&sawSlider, false);
	sineLabel.setText("Sine", juce::dontSendNotification);
	sineLabel.attachToComponent(&sineSlider, false);
	squareLabel.setText("Square", juce::dontSendNotification);
	squareLabel.attachToComponent(&squareSlider, false);
	triangleLabel.setText("Triangle", juce::dontSendNotification);
	triangleLabel.attachToComponent(&triangleSlider, false);
	lowPassLabel.setText("Low Pass", juce::dontSendNotification);
	lowPassLabel.attachToComponent(&lowPassKnob, false);
	highPassLabel.setText("High Pass", juce::dontSendNotification);
	highPassLabel.attachToComponent(&highPassKnob, false);
	gainLabel.setText("Gain", juce::dontSendNotification);
	gainLabel.attachToComponent(&gainSlider, false);
	distortLabel.setText("Distortion", juce::dontSendNotification);
	distortLabel.attachToComponent(&distortSlider, false);
	
	
	auto parameterTree = audioProcessor.getParameters();
	
	sawParameter = static_cast<juce::AudioParameterFloat*>(parameterTree.getUnchecked(0));
	sineParameter = static_cast<juce::AudioParameterFloat*>(parameterTree.getUnchecked(1));
	squareParameter = static_cast<juce::AudioParameterFloat*>(parameterTree.getUnchecked(2));
	triangleParameter = static_cast<juce::AudioParameterFloat*>(parameterTree.getUnchecked(3));
	lowPassCutoffFrequencyParameter = static_cast<juce::AudioParameterFloat*>(parameterTree.getUnchecked(4));
	highPassCutoffFrequencyParameter = static_cast<juce::AudioParameterFloat*>(parameterTree.getUnchecked(5));
	gainParameter = static_cast<juce::AudioParameterFloat*>(parameterTree.getUnchecked(6));
	distortParameter = static_cast<juce::AudioParameterFloat*>(parameterTree.getUnchecked(7));
	
	
	
	sawSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
	sawSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 120, 18);
	sawSlider.setTextValueSuffix(" db");
	sawSlider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::blueviolet);
	sawSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::rebeccapurple);
	sawSlider.setRange(sawParameter->range.start, sawParameter->range.end, 0.01);
	sawSlider.setValue(sawParameter->get());
	sawSlider.onValueChange = [this]
	{
		*sawParameter = sawSlider.getValue();
	};
	
	sineSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
	sineSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 120, 18);
	sineSlider.setTextValueSuffix(" db");
	sineSlider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::blueviolet);
	sineSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::rebeccapurple);
	sineSlider.setRange(sineParameter->range.start, sineParameter->range.end, 0.01);
	sineSlider.setValue(sineParameter->get());
	sineSlider.onValueChange = [this]
	{
		*sineParameter = sineSlider.getValue();
	};
	
	squareSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
	squareSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 120, 18);
	squareSlider.setTextValueSuffix(" db");
	squareSlider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::blueviolet);
	squareSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::rebeccapurple);
	squareSlider.setRange(squareParameter->range.start, squareParameter->range.end, 0.01);
	squareSlider.setValue(squareParameter->get());
	squareSlider.onValueChange = [this]
	{
	*squareParameter = squareSlider.getValue();
	};
	
	triangleSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
	triangleSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 120, 18);
	triangleSlider.setTextValueSuffix(" db");
	triangleSlider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::blueviolet);
	triangleSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::rebeccapurple);
	triangleSlider.setRange(triangleParameter->range.start, triangleParameter->range.end, 0.01);
	triangleSlider.setValue(triangleParameter->get());
	triangleSlider.onValueChange = [this]
	{
	*triangleParameter = triangleSlider.getValue();
	};

	lowPassKnob.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
	lowPassKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 120, 18);
	lowPassKnob.setSkewFactor(0.2);
	lowPassKnob.setTextValueSuffix("hz");
	lowPassKnob.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::tan);
	lowPassKnob.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::bisque);
	lowPassKnob.setRange(lowPassCutoffFrequencyParameter->range.start, lowPassCutoffFrequencyParameter->range.end, .01);
	lowPassKnob.setValue(lowPassCutoffFrequencyParameter->get());
	lowPassKnob.onValueChange = [this]
	{
		*lowPassCutoffFrequencyParameter = lowPassKnob.getValue();
	};
	
	highPassKnob.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
	highPassKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 120, 18);
	highPassKnob.setSkewFactor(0.2);
	highPassKnob.setTextValueSuffix("hz");
	highPassKnob.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::tan);
	highPassKnob.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::bisque);
	highPassKnob.setRange(highPassCutoffFrequencyParameter->range.start, highPassCutoffFrequencyParameter->range.end, .01);
	highPassKnob.setValue(highPassCutoffFrequencyParameter->get());
	highPassKnob.onValueChange = [this]
	{
		*highPassCutoffFrequencyParameter = highPassKnob.getValue();
	};
	
	gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
	gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 120, 18);
	gainSlider.setTextValueSuffix(" db");
	gainSlider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::lime);
	gainSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::seagreen);
	gainSlider.setRange(gainParameter->range.start, gainParameter->range.end, 0.01);
	gainSlider.onValueChange = [this]
	{
		*gainParameter = gainSlider.getValue();
	};
	
	distortSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
	distortSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 120, 18);
	distortSlider.setTextValueSuffix(" db");
	distortSlider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::lime);
	distortSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::seagreen);
	distortSlider.setRange(distortParameter->range.start, distortParameter->range.end, 0.01);
	distortSlider.onValueChange = [this]
	{
		*distortParameter = distortSlider.getValue();
	};
	


}

SynthDemov2AudioProcessorEditor::~SynthDemov2AudioProcessorEditor()
{
}

//==============================================================================
void SynthDemov2AudioProcessorEditor::paint (juce::Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

	g.setColour (juce::Colours::white);
	g.setFont (15.0f);
	//g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void SynthDemov2AudioProcessorEditor::resized()
{
	
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor..
	auto x = getWidth() / 10;
	auto y = getHeight() / 10;
	sineSlider.setBounds(.8 * x, .8 * y, 1 * x, 2.5 * y);
	squareSlider.setBounds(3.35 * x, .8 * y, 1 * x, 2.5 * y);
	triangleSlider.setBounds(5.75 * x, .8 * y, 1 * x, 2.5 *y);
	sawSlider.setBounds(8.2 * x, .8 * y, 1 * x, 2.5 * y);
	
	lowPassKnob.setBounds(.8 * x, 6 * y, 1 * x, 2.5 * y);
	highPassKnob.setBounds(3.35 * x, 6 * y, 1 * x, 2.5 * y);
	
	gainSlider.setBounds(8.2 * x, 6 * y, 1 * x, 2.5 * y);
	distortSlider.setBounds(5.75 * x, 6 * y, 1 * x, 2.5 * y);
	
	
}
