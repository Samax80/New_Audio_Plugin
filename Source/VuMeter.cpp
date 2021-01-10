/*
  ==============================================================================

	VuMeter.cpp
	Created: 20 Dec 2020 5:51:18pm
	Author:  Kijiji

  ==============================================================================
*/

#include "VuMeter.h"

VuMeter::VuMeter(New_audio_pluginAudioProcessor* inProcessor) :
	mparameterId(-1), mCh0Level(0), mCh1Level(0), mProcessor(inProcessor)
{

}

VuMeter::~VuMeter()
{
}

void VuMeter::paint(juce::Graphics& g)
{
	const int meter_width = getWidth() / 3;

	g.setColour(juce::Colours::blue);
	//Left
	g.fillRect(0, 0, meter_width, getHeight());

	//Right
	g.fillRect(meter_width * 2, 0, meter_width, getHeight());

	int ch0fill = getHeight() - (getHeight() *  mCh0Level);

	int ch1fill = getHeight() - (getHeight() * mCh1Level);

	if (ch0fill < 0)
	{
		ch0fill = 0;
	}

	if (ch1fill < 0)
	{
		ch1fill = 0;
	}

	g.setColour(juce::Colours::yellow);
	g.fillRect(0, ch0fill, meter_width, getHeight());
	g.fillRect(meter_width * 2, ch1fill, meter_width, getHeight());
}

void VuMeter::timerCallback()
{
	float updateCh0Level = mProcessor->getGainmeterLevel(); //0.35f;//static value ,this will change
	float updateCh1Level = mProcessor->getGainmeterLevel();
	auto kMeterSmoothingCoeff = 0.2;

	mCh0Level = mCh0Level > updateCh0Level ? updateCh0Level : kMeterSmoothingCoeff * (mCh0Level - updateCh0Level) + updateCh0Level;//smooth parameter	
	mCh1Level = mCh1Level > updateCh1Level ? updateCh1Level : kMeterSmoothingCoeff * (mCh1Level - updateCh1Level) + updateCh1Level;//smooth parameter
	
	mCh0Level = Denormalize(mCh0Level);
	mCh1Level = Denormalize(mCh1Level);

	if (mCh0Level && mCh1Level)
	{
		repaint();
	}
}

void VuMeter::setParameterID(int inParameterId)
{
	mparameterId = inParameterId;

	auto timefrequencyHz = 15;

	juce::Timer::startTimerHz(timefrequencyHz);

}

float VuMeter::Denormalize(float inValue)
{
	float absValue = std::fabs(inValue);

	//0.00000000000001
	return absValue = absValue < 1e-15 ? 0.0f : inValue;
}


