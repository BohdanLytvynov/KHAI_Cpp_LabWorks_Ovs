#include "FileBuilderBase.h"
#include<algorithm>



FileBuilderBase::FileBuilderBase()
	: m_FileName(nullptr),
	m_fileStream(nullptr),
	m_obj(nullptr)
{
}

void FileBuilderBase::SetupBuilder(std::ofstream* fileStream
	, std::string* fileName,
	Object* object)
{
	m_fileStream = fileStream;
	m_FileName = fileName;
	m_obj = object;
}

FileBuilderBase::~FileBuilderBase()
{
	if (m_fileStream->is_open())
		m_fileStream->close();
}

std::ofstream* FileBuilderBase::getFileStream() const
{
	return m_fileStream;
}

const std::string* FileBuilderBase::getFileName() const
{
	return m_FileName;
}

Object* FileBuilderBase::getObject()
{
	return m_obj;
}
/// <summary>
/// Don't forget to release memory
/// </summary>
/// <param name="collection"></param>
/// <returns></returns>
Field* FileBuilderBase::ToArray(std::vector<Field> collection)
{
	size_t len = collection.size();
	if (len > 0)
	{
		Field* fields = new Field[len];
		int i = 0;
		for (auto elem : collection)
		{
			fields[i] = elem;
			++i;
		}
		return fields;
	}

	return nullptr;
}

void FileBuilderBase::WriteLine(std::ofstream* fstream, const std::string& line)
{
	*fstream << line << std::endl;
}

void FileBuilderBase::Write(std::ofstream* fstream, const std::string& line)
{
	*fstream << line;
}

std::vector<Field*> FileBuilderBase::CreateSignature(
	std::ofstream* fstream,
	std::string& funcName,
	Field* parameters,
	size_t start,
	size_t end,
	std::string returnType,
	bool writeParams)
{
	std::vector<Field*> result;

	//Has return type
	if (returnType.size() > 0)
	{
		*fstream << returnType << " ";
	}

	*fstream << funcName << "(";

	if (parameters != nullptr)
	{
		for (size_t i = start; i < end; i++)
		{
			if (writeParams)
			{
				if (i == end - 1)
				{
					*fstream << parameters[i].getType() << " " << parameters[i].getName();
				}
				else
				{
					*fstream << parameters[i].getType() << " " << parameters[i].getName() << ", ";
				}
			}

			result.push_back(parameters + i);
		}
	}

	*fstream << ")";

	return result;
}

//////////////////////HeaderFileBuilder

HeaderFileBuilder::HeaderFileBuilder()
	: FileBuilderBase()
{
}

HeaderFileBuilder::~HeaderFileBuilder()
{
	FileBuilderBase::~FileBuilderBase();
}

void HeaderFileBuilder::Build()
{
	auto fstream = this->getFileStream();
	auto fname = this->getFileName();
	auto obj = this->getObject();
	std::string prefix("~");
	if (fstream != nullptr && fstream->is_open())
	{
		std::string macro(*fname);
		if (macro.find(".") != std::string::npos)
		{
			macro.replace(macro.size() - 2, 1, "_");
		}

		std::transform(macro.begin(), macro.end(), macro.begin(), std::toupper);

		*fstream << "#ifndef " << macro << std::endl;
		*fstream << "#define " << macro << std::endl;

		if (obj->isStruct())
		{
			*fstream << "struct " << obj->getName() << std::endl;
		}
		else
		{
			*fstream << "class " << obj->getName() << std::endl;
		}
		*fstream << "{" << std::endl;
		if (!obj->isStruct())
		{
			*fstream << "public:" << std::endl;
		}
		//Create Default Ctor
		CreateFunctionDeclaration(fstream, obj->getName());
		*fstream << "\n";
		auto fields = obj->getFields();
		size_t len = fields.size();
		Field* f = this->ToArray(fields);
		//Create main ctor
		CreateMainCtorDeclaration(fstream, obj->getName(), f, 0, len);
		*fstream << "\n";
		//Create destructor 
		std::string destr("~");
		destr += obj->getName();
		CreateFunctionDeclaration(fstream, destr);
		*fstream << "\n";

		//Create Getters for Counts
		std::string temp;
		prefix = "get_";
		std::string suffix = "_count";

		size_t ptrFields_len = 0;
		auto PtrFields = obj->getFieldsWithPtrs(ptrFields_len);
		WriteLine(fstream, "//Getters for Counts");
		for (size_t i = 0; i < ptrFields_len; i++)
		{
			temp.append(prefix);
			temp.append(PtrFields[i].getName());
			temp.append(suffix);
			CreateFunctionDeclaration(fstream, temp, nullptr, 0, 0, "size_t");
			temp.clear();
		}

		*fstream << "\n";
		//Create Getters	
		WriteLine(fstream, "//Getters for Fields");
		for (size_t i = 0; i < len; i++)
		{
			temp.append(prefix);
			temp.append(fields[i].getName());
			CreateFunctionDeclaration(fstream, temp, nullptr, 0, 0, fields[i].getType());
			temp.clear();
		}
		*fstream << "\n";
		//Create Setters
		prefix = "set_";
		WriteLine(fstream, "//Setters");
		for (size_t i = 0; i < len; i++)
		{
			if (!fields[i].IsPtr())
			{
				temp.append(prefix);
				temp.append(fields[i].getName());
				CreateFunctionDeclaration(fstream, temp, f, i, i + 1, "void");
				temp.clear();
			}
			else
			{
				CreateSetterForPtrDeclaration(fstream, &fields[i]);
			}
		}
		*fstream << "\n";
		*fstream << "private:" << std::endl;

		for (auto f : fields)
		{
			CreateField(fstream, &f);
		}

		*fstream << "\n";	
		//Create fields for counters
		for (size_t i = 0; i < ptrFields_len; i++)
		{
			CreateCountField(fstream, PtrFields[i].getName());
		}

		delete[] f;
		delete[] PtrFields;
		WriteLine(fstream, "");
		//Create Helper Functions
		//Array Initializer
		WriteLine(fstream, "\ttemplate<class T>");
		WriteLine(fstream, "\tvoid InitArray(T*& array, size_t count)");
		WriteLine(fstream, "\t{");

		WriteLine(fstream, "\t\tarray = new T[count];");

		WriteLine(fstream, "\t}");

		WriteLine(fstream, "");
		//Array Copy
		WriteLine(fstream, "\ttemplate<class T>");
		WriteLine(fstream, "\tvoid Copy(const T* src, size_t src_count,  T*& dest, size_t dest_count)");
		WriteLine(fstream, "\t{");

		WriteLine(fstream, "\t\tif (src_count != dest_count)");
		WriteLine(fstream, "\t\t\treturn;");
		WriteLine(fstream, "\t\tfor (size_t i = 0; i < src_count; i++)");
		WriteLine(fstream, "\t\t{");
		WriteLine(fstream, "\t\t\tdest[i] = src[i];");
		WriteLine(fstream, "\t\t}");

		WriteLine(fstream, "\t}");

		*fstream << "};" << std::endl;
		*fstream << "#endif";
	}
	else
	{
		throw std::exception("File Stream didn't set up!");
	}
}

void HeaderFileBuilder::CreateFunctionDeclaration(
	std::ofstream* fstream,
	std::string& funcName,
	Field* parameters,
	size_t start,
	size_t end,
	std::string returnType)
{
	*fstream << "\t";

	CreateSignature(fstream, funcName, parameters, start, end, returnType);

	*fstream << ";" << std::endl;
}

void HeaderFileBuilder::CreateMainCtorDeclaration(std::ofstream* fstream, std::string& funcName, Field* parameters, size_t start, size_t end)
{
	*fstream << "\t";

	*fstream << funcName << "(";

	if (parameters != nullptr)
	{
		for (size_t i = start; i < end; i++)
		{
			if (i == end - 1)
			{
				*fstream << parameters[i].getType() << " " << parameters[i].getName();

				if (parameters[i].IsPtr())
				{
					*fstream << ", " << "size_t " << parameters[i].getName() << "_count";
				}
			}
			else
			{
				*fstream << parameters[i].getType() << " " << parameters[i].getName() << ", ";

				if (parameters[i].IsPtr())
				{
					*fstream << "size_t " << parameters[i].getName() << "_count" << ", ";
				}
			}
		}
	}

	*fstream << ")";

	*fstream << ";" << std::endl;
}

void HeaderFileBuilder::CreateSetterForPtrDeclaration(std::ofstream* fstream, Field* f)
{
	*fstream << "\tvoid set_" << f->getName() << "(" << f->getType() << " " << f->getName() << ", size_t " << f->getName() << "_count" << ");" << std::endl;
}

void HeaderFileBuilder::CreateField(std::ofstream* fstrean, const Field* field)
{
	*fstrean << "\t" << field->getType() << " m_" << field->getName() << ";" << std::endl;
}

void HeaderFileBuilder::CreateCountField(std::ofstream* fstream, const std::string& name)
{
	*fstream << "\tsize_t " << "m_" << name << "_count;" << std::endl;
}


CPPFileBuilder::CPPFileBuilder()
	: FileBuilderBase()
{
}

CPPFileBuilder::~CPPFileBuilder()
{
	FileBuilderBase::~FileBuilderBase();
}

void CPPFileBuilder::Build()
{
	auto fstream = this->getFileStream();
	auto fname = this->getFileName();
	auto obj = this->getObject();

	auto vfields = obj->getFields();
	auto fields = ToArray(vfields);
	auto len = vfields.size();
	std::string prefix("~");

	if (fstream->is_open())
	{
		*fstream << "#include " << "\"" << *fname << "\"" << std::endl;
		*fstream << "\n";
		//Create Default Ctor
		CreateFunctionDefinition(fstream, obj->getName(), obj->getName(),
			[](std::ofstream* fileStream, std::vector<Field*> paramsUsed, std::string& returnType)->void
			{
				*fileStream << "\n";
				for (const auto p : paramsUsed)
				{
					if (p->IsPtr())
					{
						*fileStream << "\tthis->m_" << p->getName() << " = " << "nullptr;" << std::endl;
					}
				}
			}, false, fields, 0, len);
		*fstream << "\n";
		//Create Main Ctor
		
		CreateMainCtorDefinition(fstream, obj->getName() + "::" + obj->getName(),
			 fields, vfields.size());
		*fstream << "\n";
		std::string temp = prefix + obj->getName();
		//Create Destructor		
		CreateFunctionDefinition(fstream, obj->getName(), temp, [](std::ofstream* fileStream,
			std::vector<Field*> paramsUsed, std::string& returnType)->void
			{
				*fileStream << "\n";

				for (const auto& p : paramsUsed)
				{
					if (p->IsPtr())
					{
						*fileStream << "\tdelete[] " << "m_" << p->getName() << ";" << std::endl;
					}
				}

			}, false, fields, 0, vfields.size());
		prefix = "get_";
		//Create Getters Definition
		int i = 0;
		while (i < len)
		{
			CreateFunctionDefinition(fstream, obj->getName(), prefix + fields[i].getName(),
				[](std::ofstream* fileStream, std::vector<Field*> paramsUsed, std::string& returnType)->void
				{
					for (const auto& p : paramsUsed)
					{
						*fileStream << "\n\treturn " << "this->m_" << p->getName() << ";";
					}
				}, false, fields, i, i + 1, vfields[i].getType());
			++i;
			*fstream << "\n";
		}
		i = 0;
		//Create Setters Definitions
		prefix = "set_";
		while (i < len)
		{
			if (!fields[i].IsPtr())
			{
				CreateFunctionDefinition(fstream, obj->getName(), prefix + fields[i].getName(),
					[](std::ofstream* fileStream, std::vector<Field*> paramsUsed, std::string& returnType)->void
					{
						for (const auto& p : paramsUsed)
						{
							*fileStream << "\n\tthis->m_" << p->getName() << " = " << p->getName() << ";";
						}

					}, true, fields, i, i + 1, "void");
			}
			else
			{
				CreateSetterForPtrDefinition(fstream, &fields[i], obj->getName());
			}

			++i;
			*fstream << "\n";
		}

		size_t fieldsWithPtr_count = 0;
		Field* fieldsWithPtr = obj->getFieldsWithPtrs(fieldsWithPtr_count);
		prefix = "get_";
		std::string suffix = "_count";
		temp.clear();
		for (size_t i = 0; i < fieldsWithPtr_count; i++)
		{
			temp.append(prefix);
			temp.append(fieldsWithPtr[i].getName());
			temp.append(suffix);
	
			CreateFunctionDefinition(fstream, obj->getName(), temp,
				[](std::ofstream* fileStream, std::vector<Field*> paramsUsed, std::string& returnType)->void
				{
					for (const auto& p : paramsUsed)
					{
						*fileStream << "\n\t return this->m_" << p->getName() << "_count" << ";";
					}

				}, false, fieldsWithPtr, i, i + 1, "size_t");

			temp.clear();
		}

		delete[] fieldsWithPtr;
	}
}

void CPPFileBuilder::CreateMainCtorDefinition(std::ofstream* fstream, 
	const std::string& funcName, 
	Field* parameters, 
	size_t count)
{
	*fstream << funcName << "(";

	if (parameters != nullptr)
	{
		for (size_t i = 0; i < count; i++)
		{
			if (i == count - 1)
			{
				*fstream << parameters[i].getType() << " " << parameters[i].getName();

				if (parameters[i].IsPtr())
				{
					*fstream << ", " << "size_t " << parameters[i].getName() << "_count";
				}
			}
			else
			{
				*fstream << parameters[i].getType() << " " << parameters[i].getName() << ", ";

				if (parameters[i].IsPtr())
				{
					*fstream << "size_t " << parameters[i].getName() << "_count" << ", ";
				}
			}
		}
	}

	*fstream << ")" << std::endl;
	*fstream << "{" << std::endl;

	for (size_t i = 0; i < count; i++)
	{			
		std::string field = "this->m_" + parameters[i].getName();

		if (parameters[i].IsPtr())
		{
			std::string count_field = field + "_count";

			*fstream << "\t" << count_field << " = " << parameters[i].getName() << "_count;" << std::endl;

			*fstream << "\tInitArray(" << field << ", " << count_field << ");" << std::endl;

			*fstream << "\tCopy(" << parameters[i].getName() << ", " << count_field << ", " << field << ", " << count_field << ");" << std::endl;
			*fstream << std::endl;
		}
		else
		{
			*fstream << "\t" << field << " = " << parameters[i].getName() << ";" << std::endl;;
		}
	}

	*fstream << "}" << std::endl;
}

void CPPFileBuilder::CreateFunctionDefinition(std::ofstream* fstream,
	const std::string& objName,
	const std::string& funcName,
	CreateBody createBodyFunction,
	bool writeParams,
	Field* parameters,
	size_t start,
	size_t end,
	std::string returnType)
{
	std::string temp = objName + "::" + funcName;

	auto paramsTemp = FileBuilderBase::CreateSignature(fstream,
		temp, parameters, start, end,
		returnType, writeParams);

	*fstream << "\n{";
	createBodyFunction(fstream, paramsTemp, returnType);
	*fstream << "\n}" << std::endl;
}

void CPPFileBuilder::CreateSetterForPtrDefinition(std::ofstream* fstream, const Field* f, const std::string& objName)
{
	*fstream << "void " << objName << "::" << "set_" << f->getName() << "(" << f->getType() << " " << f->getName() << ", size_t " << f->getName() << "_count" << ")" << std::endl;
	*fstream << "{" << std::endl;

	std::string field = "this->m_" + f->getName();

	*fstream << "\tif(" << field << " != nullptr) delete[] " << field <<";";
	*fstream << "\n" << std::endl;
	*fstream << "\t" << field << "_count" << " = " << f->getName() << "_count;" << std::endl;
	*fstream << "\tInitArray(" << field << ", " << f->getName() << "_count" <<");" << std::endl;	
	*fstream << "\tCopy(" << f->getName() << ", " << f->getName() << "_count, " << field << ", " << f->getName() << "_count" << ");" << std::endl;

	*fstream << "}" << std::endl;
}

std::unique_ptr<FileBuilderBase> FileBuilderFactory::getFileBuilder(FileType key)
{
	switch (key)
	{
	case h:
		return std::make_unique<HeaderFileBuilder>();
		break;
	case cpp:
		return std::make_unique<CPPFileBuilder>();
		break;
	default:
		throw std::exception("Unsupported key!");
	}
}
