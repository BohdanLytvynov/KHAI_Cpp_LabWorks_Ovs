#ifndef OBJECT_H

#define OBJECT_H
#include<string>
#include<vector>
#include"Field.h"
#include <memory>

struct Object
{
	Object();

	Object(std::string name, bool isStruct);

	std::string& getName();

	void setName(const std::string& name);

	const std::vector<Field>& getFields() const;

	void appendField(Field f);

	bool& isStruct() noexcept;

	/// <summary>
	/// Don't forget to clean memory
	/// </summary>
	/// <param name="count"></param>
	/// <returns></returns>
	Field* getFieldsWithPtrs(size_t& count) const;
private:
	bool IsPtr(const std::string& type);

	std::string m_name;
	std::vector<Field> m_fields;
	std::vector<Field> m_fieldsWithPtrs;
	bool m_isStruct;	
};

#endif
