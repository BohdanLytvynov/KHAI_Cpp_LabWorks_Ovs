
#ifndef FIELD_H

#define FIELD_H
#include<string>

struct Field
{
	Field();

	const std::string& getName() const noexcept;

	const std::string& getType() const noexcept;
	
	Field(const std::string& name, const std::string& type);

	std::string ToString() const;
private:
	std::string m_name;
	std::string m_type;	
};

#endif

