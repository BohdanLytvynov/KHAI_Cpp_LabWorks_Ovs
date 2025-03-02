
#ifndef JUCE_H

#define JUCE_H

#include<string>

struct Juce
{
	Juce();

	Juce(const char* name, const char* manufacturer, float volume);
	
	Juce(const Juce& other);

	Juce& operator = (const Juce& other);

	const char* getName() const;
	const char* getManufacturer() const;
	float getValume() const;
	int getId() const;

	void setName(const char* name);
	void setManufacturer(const char* manufacturer);
	void setVolume(float volume);

	std::string Stringify() const;

private:
	std::string _name;
	std::string _manufacturer;
	float _volume;
	int _id;
	static int _id_g;
};

#endif // !JUCE_H




