/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
New_audio_pluginAudioProcessor::New_audio_pluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{

    mOutputSmoothed = 0;
}

New_audio_pluginAudioProcessor::~New_audio_pluginAudioProcessor()
{
}

//==============================================================================
const juce::String New_audio_pluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool New_audio_pluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool New_audio_pluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool New_audio_pluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double New_audio_pluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int New_audio_pluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int New_audio_pluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void New_audio_pluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String New_audio_pluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void New_audio_pluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void New_audio_pluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void New_audio_pluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool New_audio_pluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void New_audio_pluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

  
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
   
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            channelData[sample] = channelData[sample] *juce::Decibels::decibelsToGain( mGain);           
        }

        float absValue = std::fabs(channelData[0]);

        auto kMeterSmoothingCoeff = 0.2;

        mOutputSmoothed = kMeterSmoothingCoeff * (mOutputSmoothed - absValue) + absValue;
        OutputlevelfromProcessor= mOutputSmoothed;
    }
}

//==============================================================================
bool New_audio_pluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* New_audio_pluginAudioProcessor::createEditor()
{
    return new New_audio_pluginAudioProcessorEditor (*this);
}

//==============================================================================
void New_audio_pluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void New_audio_pluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

float New_audio_pluginAudioProcessor::getMeterLevel()
{
    return mOutputSmoothed;
}

float New_audio_pluginAudioProcessor::getGainmeterLevel()//TODO FIX THIS!!!
{
   
    const float normalizeddB = dbBToNormalizedGain(OutputlevelfromProcessor);

    return normalizeddB;
}

float New_audio_pluginAudioProcessor::dbBToNormalizedGain(float inValue)
{
    float inValuedB = juce::Decibels::gainToDecibels(inValue + 0.00001f);//to avoid infinite values when inValue=0
    inValuedB = (inValuedB + 96.0f) / 96.0f;

    return inValuedB;
}



//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new New_audio_pluginAudioProcessor();
}
