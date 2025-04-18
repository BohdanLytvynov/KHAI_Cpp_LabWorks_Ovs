
#ifndef FIELD_H

#define FIELD_H
#include<string>

struct Field
{
	Field();

	const std::string& getName() const noexcept;

	const std::string& getType() const noexcept;

	const bool IsDestrNeeded() const noexcept;

	const bool IsMemoryBlock() const noexcept;

	void setDestrNeeded(bool destrNeeded);

	void setIsMemoryBlock(bool isMemBlock);
	
	Field(const std::string& name, const std::string& type);

	std::string ToString() const;
private:
	std::string m_name;
	std::string m_type;	
	bool m_destr_needed;
	bool m_mem_block;
};

#endif

