#ifndef FILEPROCESSOR_H

#define FILEPROCESSOR_H
#include<vector>
#include"KeyWordProcessor.h"
#include<fstream>
#include<string>

struct FileProcessor
{
	FileProcessor();

	FileProcessor(std::vector<KeyWordProcessorBase*>& processors);

	void ProcessFile(std::fstream* streamToFile, Object* object);
	
private:
	std::vector<KeyWordProcessorBase*> m_processors;
};

#endif
