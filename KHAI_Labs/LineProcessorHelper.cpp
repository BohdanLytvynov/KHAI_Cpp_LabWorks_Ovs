#include "LineProcessorHelper.h"

bool LineProcessorHelper::LineContains(const std::string& line, const std::string& word)
{
	size_t count = line.find(word);

    return count != std::string::npos;
}

std::vector<std::string> LineProcessorHelper::SplitLine(const std::string& line, const char delim)
{
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = line.find(delim);

    while (end != std::string::npos) {
        tokens.push_back(line.substr(start, end - start));
        start = end + 1;
        end = line.find(delim, start);
    }

    tokens.push_back(line.substr(start));
    return tokens;
}

std::vector<std::string> LineProcessorHelper::GetTypeAndNameFromLine(std::string& line,
	std::vector<std::string>& keyWords, 
	const char* delim, const char* end)
{
	std::vector<std::string> res;
	std::string type("");
	std::string name("");
	std::string word("");
	char temp[2];
	for (const char c : line)
	{
		temp[0] = c;
		temp[1] = *"\0";
	
		//We have found the delimeter word ready for compare
		if (strcmp(temp, delim) == 0)
		{
			for (auto w : keyWords)
			{
				if (word.compare(w) == 0)//Some type found
				{
					type += word + " ";
					break;
				}
			}

			word.clear();
		}
		else if (strcmp(temp, end) == 0)
		{
			name += word;
		}
		else
		{
			word += c;
		}
	}
	if(type.size() > 0)
		res.push_back(type);

	if(type.size() > 0)
		res.push_back(name);

	return res;
}





