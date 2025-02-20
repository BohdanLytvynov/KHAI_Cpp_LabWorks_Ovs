
#ifndef JUCE_H

#define JUCE_H

struct Juce
{
	Juce();

	Juce(char* name, char* manufacturer, float volume);

	char* getName();
	char* getManufacturer();
	float& getValume();

private:
	char* _name;
	char* _manufacturer;
	float _volume;
	int _id;
	static int _id_g;
};

#endif // !JUCE_H




