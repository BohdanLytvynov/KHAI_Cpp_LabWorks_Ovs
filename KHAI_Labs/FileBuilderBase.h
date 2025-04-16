
#ifndef FILEBUILDERBASE_H

#define FILEBUILDERBASE_H
#include "Object.h"
#include <fstream>
#include <map>

typedef void (*CreateBody)(std::ofstream* fileStream, std::vector<Field*> paramsUsed, std::string& returnType);

enum DeleteType
{
	single, multiple
};

enum FileType 
{
	h, cpp
};

struct FileBuilderBase
{
	FileBuilderBase();

	void SetupBuilder(std::ofstream* m_fileStream, 
		std::string* fileName,
		Object* object);

	virtual void Build() = 0;

	~FileBuilderBase();
protected:
	std::ofstream* getFileStream() const;
	const std::string* getFileName() const;
	Object* getObject();
	Field* ToArray(std::vector<Field> collection);

	virtual std::vector<Field*> CreateSignature(std::ofstream* fstream,
		std::string& funcName,
		Field* parameters,
		size_t start,
		size_t end,
		std::string returnType);

private:	
	std::ofstream* m_fileStream;
	std::string* m_FileName;
	Object* m_obj;
};

struct HeaderFileBuilder : public FileBuilderBase
{
	HeaderFileBuilder();
	
	~HeaderFileBuilder();

	void Build() override;

private:
	void CreateFunctionDeclaration(
		std::ofstream* fstream,
		std::string& funcName, 
		Field* parameters = nullptr, 
		size_t start = 0,
		size_t end = 0,
		std::string returnType = "");	

	void CreateField(std::ofstream* fstrean, Field* field);
};

struct CPPFileBuilder : public FileBuilderBase
{
	CPPFileBuilder();
	
	~CPPFileBuilder();

	void Build() override;

private:
	void CreateFunctionDefinition(std::ofstream* fstream,
		std::string& funcName, 
		CreateBody createBodyFunction,
		Field* parameters = nullptr,
		size_t start = 0,
		size_t end = 0,
		std::string returnType = "");

	void CreateGetterDefinition(Field* f, size_t count, std::string& );

	void CreateSetterDefinition(Field* f);

	void CreateDestructorDefinition(Field* f, size_t fieldCount, std::map<int, DeleteType>* hashTable);
};

struct FileBuilderFactory
{
	static std::unique_ptr<FileBuilderBase> getFileBuilder(FileType key);
};

#endif

