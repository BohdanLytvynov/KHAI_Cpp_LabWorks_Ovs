#include "Field.h"

Field::Field() : m_name(""), m_type(""), m_isPtr(false)
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

const bool Field::IsPtr() const noexcept
{
	return m_isPtr;
}

void Field::setIsPtr(bool isPtr)
{
	m_isPtr = isPtr;
}

Field::Field(const std::string& name, 
	const std::string& type)
	: m_name(name), m_type(type), m_isPtr(false)
{}

Field::Field(const std::string & name, 
	const std::string & type, 
	bool isPtr)
	:Field(name, type) 
{
	m_isPtr = isPtr;
}

std::string Field::ToString() const
{
	return m_name + " " + m_type + " IsPtr: " + std::to_string(m_isPtr);
}
