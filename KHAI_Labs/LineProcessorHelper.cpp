#include "LineProcessorHelper.h"

bool LineProcessorHelper::LineContains(const std::string& line, const std::string& word)
{
    return line.find(word) > 0;
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
	const char delim, const char end)
{
	std::vector<std::string> res;
	std::string type("");
	std::string name("");
	std::string word("");

	for (char c : line)
	{
		//We have found the delimeter word ready for compare
		if (strcmp(&c, &delim) == 0)
		{
			for (auto w : keyWords)
			{
				if (word.compare(w) == 0)//Some type found
				{
					type += word + " ";
					word.clear();
				}
			}
		}
		else if (strcmp(&c, &end))
		{
			name.append(word);
		}
		else
		{
			word.append(&c);
		}
	}

	res.push_back(type);
	res.push_back(name);

	return res;
}





