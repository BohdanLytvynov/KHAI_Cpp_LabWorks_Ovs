
#ifndef LINEPROCESSORHELPER_H

#define LINEPROCESSORHELPER_H
#include <string>
#include <vector>

struct LineProcessorHelper
{
	static bool LineContains(const std::string& line, const std::string& word);

	static std::vector<std::string> SplitLine(const std::string& line, const char delim);

	static std::vector<std::string> GetTypeAndNameFromLine(std::string& line, 
		std::vector<std::string>& keyWords, const char delim, const char end);
};

#endif

