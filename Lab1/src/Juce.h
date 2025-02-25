
#ifndef JUCE_H

#define JUCE_H

#include<string>

struct Juce
{
	Juce();

	Juce(char* name, char* manufacturer, float volume);

	char* getName();
	char* getManufacturer();
	float& getValume();

	std::string Stringify() const;

private:
	char* _name;
	char* _manufacturer;
	float _volume;
	int _id;
	static int _id_g;
};

#endif // !JUCE_H




