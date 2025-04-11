
#ifndef FIELD_H

#define FIELD_H
#include<string>

struct Field
{
	Field();

	std::string& getName() noexcept;

	std::string& getType() noexcept;
	
	Field(const std::string& name, const std::string& type);
private:
	std::string m_name;
	std::string m_type;	
};

#endif

