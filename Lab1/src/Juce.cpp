#include "Juce.h"
#include<sstream>
#include <boost/json/src.hpp>

Juce::Juce() : Juce(nullptr, nullptr, 0.0f)
{
	
}

Juce::Juce(const char* name, const  char* manufacturer, float volume)
{
	if (name != nullptr)
	{
		_name = std::string(name);
	}

	if (manufacturer != nullptr)
	{
		_manufacturer = std::string(manufacturer);
	}

	_volume = volume;
	_id = _id_g++;
}

Juce::Juce(const Juce& other)
{
	_name = other._name;
	_manufacturer = other._manufacturer;
	_volume = other._volume;	
	_id = other._id;	
}

Juce& Juce::operator=(const Juce& other)
{
	_name = other._name;
	_manufacturer = other._manufacturer;
	_volume = other._volume;
	_id = other._id;
	
	return *this;
}

const char* Juce::getName() const
{
	return _name.c_str();
}

const char* Juce::getManufacturer() const
{
	return _manufacturer.c_str();
}

float Juce::getValume() const
{
	return _volume;
}

int Juce::getId() const
{
	return _id;
}

void Juce::setName(const char* name)
{	
	_name = std::string(name);
}

void Juce::setManufacturer(const char* manufacturer)
{
	_manufacturer = std::string(manufacturer);
}

void Juce::setVolume(float volume)
{
	_volume = volume;
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