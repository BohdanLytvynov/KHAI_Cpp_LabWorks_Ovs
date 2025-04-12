
#ifndef FILEBUILDERBASE_H

#define FILEBUILDERBASE_H
#include "Object.h"
#include <fstream>

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
};

struct FileBuilderFactory
{
	static std::unique_ptr<FileBuilderBase> getFileBuilder(FileType key);
};

#endif

