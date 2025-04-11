#ifndef OBJECT_H

#define OBJECT_H
#include<string>
#include<vector>
#include"Field.h"

struct Object
{
	Object();

	Object(std::string name, bool isStruct);

	std::string& getName();

	void setName(const std::string& name);

	std::vector<Field>& getFields();

	bool& isStruct() noexcept;

private:
	std::string m_name;
	std::vector<Field> m_fields;
	bool m_isStruct;	
};

#endif
