#include "Juce.h"
#include<sstream>
#include <boost/json/src.hpp>

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

std::string Juce::Stringify() const
{
	boost::json::object curr;
	curr["id"] = _id;
	curr["name"] = _name;
	curr["manufacturer"] = _manufacturer;
	curr["volume"] = _volume;

	return boost::json::serialize(curr);
}

int Juce::_id_g = 0;