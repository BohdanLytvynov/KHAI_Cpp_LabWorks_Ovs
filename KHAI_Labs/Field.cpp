#include "Field.h"

Field::Field() : m_name(""), m_type("")
{
	
}

std::string& Field::getName() noexcept
{
	return m_name;
}

std::string& Field::getType() noexcept
{
	return m_type;
}

Field::Field(const std::string& name, const std::string& type)
	: m_name(name), m_type(type)
{}