/*
  ==============================================================================

	VuMeter.h
	Created: 20 Dec 2020 5:51:18pm
	Author:  samax80

  ==============================================================================
*/


#pragma once


#include "JuceHeader.h"
#include "PluginProcessor.h"

class VuMeter
	: public juce::Component,
	public juce::Timer
{
	public:
		VuMeter(New_audio_pluginAudioProcessor* inProcessor);
		~VuMeter();

		void paint(juce::Graphics& g) override;

		void timerCallback() override;

		void setParameterID(int inParameterId);

		float Denormalize(float inValue);

	private:

		int mparameterId;

		float mCh0Level;
		float mCh1Level;

		New_audio_pluginAudioProcessor* mProcessor;
};
