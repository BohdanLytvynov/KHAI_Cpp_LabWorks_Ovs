
#ifndef FIELD_H

#define FIELD_H
#include<string>

struct Field
{
	Field();

	const std::string& getName() const noexcept;

	const std::string& getType() const noexcept;

	const bool IsPtr() const noexcept;

	void setIsPtr(bool isPtr);
	
	Field(const std::string& name, const std::string& type);

	Field(const std::string& name, const std::string& type, bool isPtr);

	std::string ToString() const;
private:
	std::string m_name;
	std::string m_type;
	bool m_isPtr;
};

#endif

