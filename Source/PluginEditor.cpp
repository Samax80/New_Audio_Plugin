/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
New_audio_pluginAudioProcessorEditor::New_audio_pluginAudioProcessorEditor (New_audio_pluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{   
    auto newMinimunRange = -60.0f;
    InitializeSlider(mGainSlider, juce::Slider::TextBoxBelow, true, 50, 20, juce::Slider::SliderStyle::LinearVertical, newMinimunRange, 0.0f, 0.01, -20.0f,this);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    width = 200;
    height = 300;

    //mVuMeter = std::make_unique<VuMeter>(&p);

    mVuMeter = new VuMeter(&p);   

    addAndMakeVisible(mVuMeter);


     auto actualSliderValue = ((mGainSlider.getValue() - newMinimunRange) * ((1 - 0.53) / (0 - newMinimunRange))) + 0.53;//TO BE ABLE TO START UP THE SIZE OF THE WINDOW WITH THE CURRENT SLIDER VALUE WHEN PLUGIN UI IS CREATED

    setSize(width* actualSliderValue, height* actualSliderValue);//here we set the size of the plugin window 
    auto timeInhertz =15;
    mVuMeter->SetVuTimerInHZ(timeInhertz);
}

New_audio_pluginAudioProcessorEditor::~New_audio_pluginAudioProcessorEditor()
{
}

//==============================================================================
void New_audio_pluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    auto backGroundColor = juce:: Colours::black;
    g.fillAll(backGroundColor);

    //mVuMeter->SetVuTimerInHZ(15);//This call juce::Timer::startTimerHz(timefrequencyHz);  
}

void New_audio_pluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto actualSliderValue = ((mGainSlider.getValue() - -60) * ((1 - 0.53) / (0 - (-60)))) + 0.53;

    mGainSlider.setBounds(getWidth() / 2 - 50 * actualSliderValue, getHeight() / 2 - 75 * actualSliderValue, 100* actualSliderValue, 150* actualSliderValue);

    const int meter_width = 25;

    mVuMeter->setBounds(((getWidth() * 0.25) - (meter_width * 0.25))*actualSliderValue,
        ((getHeight() * 0.35) - (meter_width * 0.5))* actualSliderValue,
        meter_width* actualSliderValue,
        (getHeight() * 0.65)* actualSliderValue);

   
}

void New_audio_pluginAudioProcessorEditor::InitializeSlider(juce::Slider& mGainSlider, juce::Slider::TextEntryBoxPosition newPosition, bool isReadOnly, int textEntryBoxWidth, int textEntryBoxHeight, juce::Slider::SliderStyle newStyle, double newMin, double newMax, double newInt, double newValue, juce::Slider::Listener * audio_pluginAudioProcessor)
{
    mGainSlider.setSliderStyle(newStyle);
    mGainSlider.setTextBoxStyle(newPosition, isReadOnly, textEntryBoxWidth, textEntryBoxHeight);
    mGainSlider.setRange(newMin, newMax, newInt);
    mGainSlider.setValue(newValue);
    mGainSlider.addListener(audio_pluginAudioProcessor);
    addAndMakeVisible(mGainSlider);//this makes the child to the component visible.
}

void New_audio_pluginAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    auto ismGainSlider = slider == &mGainSlider;

    if (ismGainSlider)
    {
        audioProcessor.mGain = mGainSlider.getValue();
        
        //TEST RESIZE UI SLIDER STARTS
        //Once the plugin Ui  have been initialized it can be resized on sliderValue Changed between max 1 (100%) and minimum of 0.53 (53%)    

        //maps values from -60db-0db to  new range 0.53%-100%      
        auto actualSliderValue = ((mGainSlider.getValue() - -60) * ((1 - 0.53) / (0 - (-60)))) + 0.53;

        float minimunvalue = 0.53f;
        if(actualSliderValue> minimunvalue)
        {
            widthref = 300 * actualSliderValue;
            heightref = 200 * actualSliderValue;
            setSize(heightref, widthref);  
        }
                 
        //TEST RESIZE UI SLIDER ENDSS          
    }
}
