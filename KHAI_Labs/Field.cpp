#include "Field.h"

Field::Field() : m_name(""), m_type("")
{
	
}

const std::string& Field::getName() const noexcept
{
	return m_name;
}

const std::string& Field::getType() const noexcept
{
	return m_type;
}

Field::Field(const std::string& name, const std::string& type)
	: m_name(name), m_type(type)
{}

std::string Field::ToString() const
{
	return m_name + " " + m_type;
}
