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
class New_audio_pluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    New_audio_pluginAudioProcessorEditor (New_audio_pluginAudioProcessor&);
    ~New_audio_pluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void New_audio_pluginAudioProcessorEditor::InitializeSlider(juce::Slider& mGainSlider, juce::Slider::TextEntryBoxPosition newPosition, bool isReadOnly, int textEntryBoxWidth, int textEntryBoxHeight, juce::Slider::SliderStyle newStyle, double newMin, double newMax, double newInt, double newValue);


private:
    /// <summary>
    /// The Gain slider Object 
    /// </summary>
    juce::Slider  mGainSlider;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    New_audio_pluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (New_audio_pluginAudioProcessorEditor)
};
