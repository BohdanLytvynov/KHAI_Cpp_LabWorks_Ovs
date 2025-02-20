#include "Juce.h"

Juce::Juce() : Juce("", "", 0.0f)
{

}

Juce::Juce(char* name, char* manufacturer, float volume)
{
	_name = name;
	_manufacturer = manufacturer;
	_volume = volume;
	_id = _id_g++;	
}

char* Juce::getName()
{
	return _name;
}

char* Juce::getManufacturer()
{
	return _manufacturer;
}

float& Juce::getValume()
{
	return _volume;
}

int Juce::_id_g = 0;