
#ifndef FILEBUILDERBASE_H

#define FILEBUILDERBASE_H
#include "Object.h"
#include <fstream>

typedef void (*CreateBody)(std::ofstream* fileStream, 
	std::vector<Field*> paramsUsed, 
	std::string& returnType);

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
	void WriteLine(std::ofstream* fstream, const std::string& line);
	void Write(std::ofstream* fstream, const std::string& line);

	virtual std::vector<Field*> CreateSignature(std::ofstream* fstream,
		std::string& funcName,
		Field* parameters,
		size_t start,
		size_t end,
		std::string returnType,
		bool writeParams = true);

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

	void CreateMainCtorDeclaration(
		std::ofstream* fstream,
		std::string& funcName,
		Field* parameters = nullptr,
		size_t start = 0,
		size_t end = 0
	);

	void CreateSetterForPtrDeclaration(std::ofstream *fstream, Field* f);

	void CreateField(std::ofstream* fstrean, const Field* field);

	void CreateCountField(std::ofstream* fstream, const std::string& name);
};

struct CPPFileBuilder : public FileBuilderBase
{
	CPPFileBuilder();
	
	~CPPFileBuilder();

	void Build() override;

private:
	void CreateMainCtorDefinition(
		std::ofstream* fstream,
		const std::string& funcName,
		Field* parameters,
		size_t count
	);

	void CreateFunctionDefinition(std::ofstream* fstream,
		const std::string& objName,
		const std::string& funcName, 
		CreateBody createBodyFunction,
		bool writeParams,
		Field* parameters = nullptr,
		size_t start = 0,
		size_t end = 0,
		std::string returnType = "");	

	void CreateSetterForPtrDefinition(std::ofstream* fstream, const Field* f, const std::string& objName);

};

struct FileBuilderFactory
{
	static std::unique_ptr<FileBuilderBase> getFileBuilder(FileType key);
};

#endif

