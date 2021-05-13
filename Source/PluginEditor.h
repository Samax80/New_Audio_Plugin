/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "VuMeter.h" 

//==============================================================================
/**
*/
/// <summary>
/// Class audio pluginAudioProcessorEditor 
/// derives from juce::Slider::Slider to let the SLider modify the gain variable to the processor
/// </summary>
class New_audio_pluginAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                              public juce::Slider::Listener
{
public:
    New_audio_pluginAudioProcessorEditor (New_audio_pluginAudioProcessor&);
    ~New_audio_pluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    /// <summary>
    /// Initializes the slider.
    /// </summary>
    /// <param name="mGainSlider">The Juce::Slider class Object.</param>
    /// <param name="newPosition">The new text box position.</param>
    /// <param name="isReadOnly">if set to <c>true</c> [textbox is read only].</param>
    /// <param name="textEntryBoxWidth">Width of the text entry box.</param>
    /// <param name="textEntryBoxHeight">Height of the text entry box.</param>
    /// <param name="newStyle">The new slider style.</param>
    /// <param name="newMin">The new minimum Range.</param>
    /// <param name="newMax">The new maximum Range.</param>
    /// <param name="newInt">The new interval value.</param>
    /// <param name="newValue">The new initial value.</param>
    /// <param name="audio_pluginAudioProcessor">The audio_pluginAudioProcessor pointer.</param>
    void New_audio_pluginAudioProcessorEditor::InitializeSlider(juce::Slider& mGainSlider, juce::Slider::TextEntryBoxPosition newPosition, bool isReadOnly, int textEntryBoxWidth, int textEntryBoxHeight, juce::Slider::SliderStyle newStyle, double newMin, double newMax, double newInt, double newValue, juce::Slider::Listener* audio_pluginAudioProcessor);
    
    /// <summary>
    /// Method to manage the on slider change,to notify the processor 
    /// </summary>
    /// <param name="slider">The slider.</param>
    void New_audio_pluginAudioProcessorEditor::sliderValueChanged(juce::Slider* slider) override;

    double width;
    double height;

private:
    /// <summary>
    /// The Gain slider Object 
    /// </summary>
   juce::Slider  mGainSlider;

    std::unique_ptr<juce::Slider> smGainSlider;
    //std::unique_ptr<VuMeter> mVuMeter;

    juce::ScopedPointer< VuMeter>mVuMeter;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    New_audio_pluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (New_audio_pluginAudioProcessorEditor)
};
