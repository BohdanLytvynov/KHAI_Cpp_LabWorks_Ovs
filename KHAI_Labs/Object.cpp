#include "Object.h"

Object::Object()
	: m_name(""),
	m_isStruct(false)
{
}

Object::Object(std::string name, bool isStruct)
	: m_name(name), m_isStruct(isStruct)
{
}

std::string& Object::getName()
{
	return m_name;
}

void Object::setName(const std::string& name)
{
	m_name = name;
}

std::vector<Field>& Object::getFields()
{
	return m_fields;
}

bool& Object::isStruct() noexcept
{
	return m_isStruct;
}
