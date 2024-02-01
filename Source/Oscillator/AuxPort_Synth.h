#ifndef AuxPort_Synth_H
#define AuxPort_Synth_H
#include "AuxPort_Osc.h"
#include <vector>
#include "JuceHeader.h"
namespace AuxPort
{
	
	class Synth
	{
	public:
		Synth() = default;
		~Synth() = default;
		Synth(const Synth& synth) = default;

		void prepareToPlay(const uint32& sampleRate)
		{
            sawToothOscillators.resize(128);
            sinewaveoscillators.resize(128);
            squarewaveoscillators.resize(128);
            trianglewaveoscillators.resize(128);
			if (this->sampleRate != sampleRate)
			{
				for (uint32 i = 0; i < sawToothOscillators.size(); i++)
				{
					sawToothOscillators[i].setSampleRate(sampleRate);
				}
                for (uint32 i = 0; i < sinewaveoscillators.size(); i++)
                {
                    sinewaveoscillators[i].setSampleRate(sampleRate);
                }
                for (uint32 i = 0; i < squarewaveoscillators.size(); i++)
                {
                    squarewaveoscillators[i].setSampleRate(sampleRate);
                }
                for (uint32 i = 0; i < trianglewaveoscillators.size(); i++)
                {
                    trianglewaveoscillators[i].setSampleRate(sampleRate);
                }
				this->sampleRate = sampleRate;
			}
		}

		void render(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& messages)
		{
			auto currentSample = 0;
			for (const auto midi : messages)
			{
				auto message = midi.getMessage();
				auto messagePosition = static_cast<int> (message.getTimeStamp());
				process(buffer, currentSample, messagePosition);
				currentSample = messagePosition;
				handleMidiEvent(message);
			}
			process(buffer, currentSample, buffer.getNumSamples());
		}
        
        void setSawVolume(float sawVolume) {
            this->sawVolume = powf(10,sawVolume/20);
        }
        
        void setSineVolume(float sineVolume) {
            this->sineVolume = powf(10,sineVolume/20);
        }
        void setSquareVolume(float squareVolume) {
            this->squareVolume = powf(10, squareVolume/20);
        }
        void settriangleVolume(float triangleVolume) {
            this->triangleVolume = powf(10, triangleVolume/20);
        }
        
	private:
		float midiToFreq(const uint32& midiNote)
		{
			constexpr float A4_FREQ = 440;
			constexpr float A4_MIDINOTE = 69;
			constexpr float NOTES_IN_OCTAVE = 12.f;
			return A4_FREQ * std::powf(2, (static_cast<float>(midiNote) - A4_MIDINOTE) / NOTES_IN_OCTAVE);
		}

		void handleMidiEvent(const juce::MidiMessage& message)
		{
			if (message.isNoteOn())
			{
				sawToothOscillators[message.getNoteNumber()].setFrequency(midiToFreq(message.getNoteNumber()));
                sinewaveoscillators[message.getNoteNumber()].setFrequency(midiToFreq(message.getNoteNumber()));
                squarewaveoscillators[message.getNoteNumber()].setFrequency(midiToFreq(message.getNoteNumber()));
                trianglewaveoscillators[message.getNoteNumber()].setFrequency(midiToFreq(message.getNoteNumber()));
			}

			if (message.isNoteOff())
			{
				sawToothOscillators[message.getNoteNumber()].stop();
                sinewaveoscillators[message.getNoteNumber()].stop();
                squarewaveoscillators[message.getNoteNumber()].stop();
                trianglewaveoscillators[message.getNoteNumber()].stop();
			}

			if (message.isAllNotesOff())
			{
				for (uint32_t i = 0; i < sawToothOscillators.size(); i++)
				{
					sawToothOscillators[i].stop();
				}
                for (uint32_t i = 0; i < sinewaveoscillators.size(); i++)
                {
                    sinewaveoscillators[i].stop();
                }
                for (uint32_t i = 0; i < squarewaveoscillators.size(); i++)
                {
                    squarewaveoscillators[i].stop();
                }
                for (uint32_t i = 0; i < trianglewaveoscillators.size(); i++)
                {
                    trianglewaveoscillators[i].stop();
                }
			}
		}

		void process(juce::AudioBuffer<float>& buffer, const uint32& startSample, const uint32& endSample)
		{
			auto* firstChannel = buffer.getWritePointer(0);
			for (uint32 i = 0; i < sawToothOscillators.size(); i++)
			{
				if (sawToothOscillators[i].isPlaying())
				{
					for (auto j = startSample; j < endSample; j++)
					{
						firstChannel[j] += sawToothOscillators[i].getSample() * sawVolume;
					}
				}
			}

            for (uint32 i = 0; i < sinewaveoscillators.size(); i++)
            {
                if (sinewaveoscillators[i].isPlaying())
                {
                    for (auto j = startSample; j < endSample; j++)
                    {
                        firstChannel[j] += sinewaveoscillators[i].getSample() * sineVolume;
                    }
                }
            }
            
            for (uint32 i = 0; i < squarewaveoscillators.size(); i++)
            {
                if (squarewaveoscillators[i].isPlaying())
                {
                    for (auto j = startSample; j < endSample; j++)
                    {
                        firstChannel[j] += squarewaveoscillators[i].getSample() * squareVolume;
                    }
                }
            }
            for (uint32 i = 0; i < trianglewaveoscillators.size(); i++)
            {
                if (trianglewaveoscillators[i].isPlaying())
                {
                    for (auto j = startSample; j < endSample; j++)
                    {
                        firstChannel[j] += trianglewaveoscillators[i].getSample() * triangleVolume;
                    }
                }
            }

            
			for (uint32 channel = 1; channel < buffer.getNumChannels(); channel++)
			{
				auto channelData = buffer.getWritePointer(channel);
				std::copy(firstChannel + startSample, firstChannel + endSample, channelData + startSample);
			}
		}


		uint32 sampleRate = 44100;
		std::vector<AuxPort::Sawtooth> sawToothOscillators;
        std::vector<AuxPort::sinewave> sinewaveoscillators;
        std::vector<AuxPort::squarewave> squarewaveoscillators;
        std::vector<AuxPort::trianglewave> trianglewaveoscillators;
        float sawVolume = 1;
        float sineVolume = 1;
        float squareVolume = 1;
        float triangleVolume = 1;
	};
	
}
#endif
