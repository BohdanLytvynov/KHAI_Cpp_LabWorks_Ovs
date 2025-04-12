#include "FileProcessor.h"
FileProcessor::FileProcessor()
{}

FileProcessor::FileProcessor(std::vector<KeyWordProcessorBase*>& processors)
{
	m_processors = processors;
}

void FileProcessor::ProcessFile(std::fstream* streamToFile, Object* object)
{
	char line[2048];

	while (!streamToFile->eof())
	{
		streamToFile->getline(line, sizeof(line));

		std::string str(line);

		if (str.size() == 0 || str.compare("{") == 0 || str.compare("}") == 0)
			continue;

		if (size_t pos = str.find("\t") != std::string::npos)
		{
			str.erase(str.begin() + (pos - 1));
		}

		for (auto processor : m_processors)
		{
			if (processor->Process(str, object))
			{
				break;
			}
		}

		std::memset(line, 0, sizeof(line));
	}
}
