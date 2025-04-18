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
					*fstream << parameters[i].getType() << parameters[i].getName();
				}
				else
				{
					*fstream << parameters[i].getType() << parameters[i].getName() << ", ";
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
		CreateFunctionDeclaration(fstream, obj->getName(), f, 0, len);
		*fstream << "\n";
		//Create destructor 
		std::string destr("~");
		destr += obj->getName();
		CreateFunctionDeclaration(fstream, destr);
		*fstream << "\n";
		//Create Getters
		prefix = "get_";
		std::string temp;
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

		for (size_t i = 0; i < len; i++)
		{
			temp.append(prefix);
			temp.append(fields[i].getName());
			CreateFunctionDeclaration(fstream, temp, f, i, i+1, "void");
			temp.clear();
		}
		*fstream << "\n";
		*fstream << "private:" << std::endl;
		
		for (auto f : fields)
		{
			CreateField(fstream, &f);
		}

		delete[] f;
		*fstream << "};"<<std::endl;
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

void HeaderFileBuilder::CreateField(std::ofstream* fstrean, Field* field)
{
	*fstrean << "\t" << field->getType() << "m_" << field->getName() << ";" << std::endl;
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
	std::string prefix("~");

	if (fstream->is_open())
	{
		*fstream << "#include " << "\"" << *fname << "\"" << std::endl;
		*fstream << "\n";
		//Create Default Ctor
		CreateFunctionDefinition(fstream, obj->getName(), obj->getName(), 
			[](std::ofstream* fileStream, std::vector<Field*> paramsUsed, std::string& returnType)->void 
			{}, false);
		*fstream << "\n";
		//Create Main Ctor
		auto vfields = obj->getFields();
		auto fields = ToArray(vfields);
		auto len = vfields.size();
		CreateFunctionDefinition(fstream, obj->getName(), obj->getName(),
			[](std::ofstream* fileStream, std::vector<Field*> paramsUsed, std::string& returnType)->void 
			{				
				*fileStream << "\n";
				for (const auto& p : paramsUsed)
				{
					*fileStream << "\tthis->" << "m_" << p->getName() << " = " << p->getName() << ";" << std::endl;
				}

			}, true, fields, 0, vfields.size());
		*fstream << "\n";
		std::string temp = prefix + obj->getName();
		//Create Destructor		
		CreateFunctionDefinition(fstream, obj->getName(), temp, [](std::ofstream* fileStream, 
			std::vector<Field*> paramsUsed, std::string& returnType)->void
			{
				*fileStream << "\n";

				for (const auto& p : paramsUsed)
				{
					if (p->IsDestrNeeded())
					{
						if (p->IsMemoryBlock())
						{
							*fileStream << "\tdelete[] " << "m_" << p->getName() << ";" << std::endl;
						}
						else
						{
							*fileStream << "\tdelete " << "m_" << p->getName() << ";" << std::endl;
						}
					}
				}

			}, false, fields, 0, vfields.size());

		//Create Getters Definition
		int i = 0;
		while (i < len)
		{
			CreateFunctionDefinition(fstream, obj->getName(), fields[i].getName(),
				[](std::ofstream* fileStream, std::vector<Field*> paramsUsed, std::string& returnType)->void 
				{
					for (const auto& p : paramsUsed)
					{
						*fileStream << "\n\treturn " << "this->m_" << p->getName() << ";\n";
					}
				}, false, fields, i, i+1, vfields[i].getType());
			++i;
			*fstream << "\n";
		}	
		i = 0;
		//Create Setters Definitions

		while (i < len)
		{
			CreateFunctionDefinition(fstream, obj->getName(), obj->getName(),
				[](std::ofstream* fileStream, std::vector<Field*> paramsUsed, std::string& returnType)->void
				{
					for (const auto& p : paramsUsed)
					{
						*fileStream << "\n\tthis->m_" << p->getName() << " = " << p->getName() << ";\n";
					}

				}, true, fields, i, i+1, "void");
			++i;
			*fstream << "\n";
		}
	}	
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
