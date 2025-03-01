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
		_name = new char[std::strlen(name)];
		std::strcpy(const_cast<char*>(_name), name);
	}

	if (manufacturer != nullptr)
	{
		_manufacturer = new char[std::strlen(manufacturer)];
		std::strcpy(const_cast<char*>(_manufacturer), manufacturer);
	}

	_volume = volume;
	_id = _id_g++;
}

Juce::~Juce()
{
	if(_name != nullptr)
		delete[] _name;//Error????

	if(_manufacturer != nullptr)
		delete[] _manufacturer;
	_id_g--;
}

Juce::Juce(const Juce& other)
{
	_name = new char[std::strlen(other._name)];
	std::strcpy(const_cast<char*>(_name), other._name);
	_manufacturer = new char[std::strlen(other._manufacturer)];
	std::strcpy(const_cast<char*>(_manufacturer), other._manufacturer);
	_volume = other._volume;	
	_id = other._id;

	other.~Juce();
}

Juce& Juce::operator=(const Juce& other)
{
	_name = new char[std::strlen(other._name)];
	std::strcpy(const_cast<char*>(_name), other._name);
	_manufacturer = new char[std::strlen(other._manufacturer)];
	std::strcpy(const_cast<char*>(_manufacturer), other._manufacturer);
	_volume = other._volume;
	_id = other._id;

	other.~Juce();

	return *this;
}

const char* Juce::getName() const
{
	return _name;
}

const char* Juce::getManufacturer() const
{
	return _manufacturer;
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
	if (_name != nullptr)
		delete[] _name;

	_name = new char[std::strlen(name)];
	std::strcpy(const_cast<char*>(_name), name);
}

void Juce::setManufacturer(const char* manufacturer)
{
	if (_manufacturer != nullptr)
		delete[] _manufacturer;

	_manufacturer = new char[std::strlen(manufacturer)];
	std::strcpy(const_cast<char*>(_manufacturer), manufacturer);
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