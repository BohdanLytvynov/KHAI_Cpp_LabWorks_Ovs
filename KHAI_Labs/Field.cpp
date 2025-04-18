#include "Field.h"

Field::Field() : m_name(""), m_type(""), m_destr_needed(false), m_mem_block(false)
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

const bool Field::IsDestrNeeded() const noexcept
{
	return m_destr_needed;
}

const bool Field::IsMemoryBlock() const noexcept
{
	return m_mem_block;
}

void Field::setDestrNeeded(bool destrNeeded)
{
	m_destr_needed = destrNeeded;
}

void Field::setIsMemoryBlock(bool isMemBlock)
{
	m_mem_block = isMemBlock;
}

Field::Field(const std::string& name, const std::string& type)
	: m_name(name), m_type(type), m_destr_needed(false), m_mem_block(false)
{}

std::string Field::ToString() const
{
	return m_name + " " + m_type;
}
