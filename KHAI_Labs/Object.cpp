#include "Object.h"
#include <algorithm>

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

const std::vector<Field>& Object::getFields() const
{
	return m_fields;
}

void Object::appendField(Field f)
{	
	if (this->IsPtr(f.getType()))
	{
		f.setIsPtr(true);

		m_fieldsWithPtrs.push_back(f);
	}

	m_fields.push_back(f);
}

bool& Object::isStruct() noexcept
{
	return m_isStruct;
}

Field* Object::getFieldsWithPtrs(size_t& count) const
{
	count = m_fieldsWithPtrs.size();

	Field* result = new Field[count];
	int i = 0;
	for (const Field f : m_fieldsWithPtrs)
	{
		result[i] = m_fieldsWithPtrs[i];

		++i;
	}

	return result;
}

bool Object::IsPtr(const std::string& type)
{
	return type.find("*") != std::string::npos;
}

