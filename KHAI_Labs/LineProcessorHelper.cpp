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
	if (type.size() > 0)
		res.push_back(LineProcessorHelper::EraseLastEntry(type, " "));

	if (type.size() > 0)
		res.push_back(LineProcessorHelper::EraseLastEntry(name, " "));

	return res;
}

bool LineProcessorHelper::HasPtr(std::string& line)
{
	return line.find("*") != std::string::npos;
}

bool LineProcessorHelper::HasAttribute(std::string& line, const std::string& attribute)
{
	if (line.find("@") == std::string::npos)
		return false;

	if (line.find(attribute) == std::string::npos)
		return false;

	return true;
}

bool LineProcessorHelper::TryGetAttributeValue(std::string& line,
	const std::string& attribute, std::string& output)
{
	if (LineProcessorHelper::HasAttribute(line, attribute))
	{
		size_t pos = line.find("(");
		if (pos != std::string::npos)
		{
			output += line.substr(++pos, (line.size() - 1) - pos);

			return true;
		}
	}

	return false;
}

std::string LineProcessorHelper::EraseLastEntry(std::string line, const std::string& value)
{
	size_t pos = line.find_last_of(value);

	if (pos != std::string::npos)
	{
		line.erase(line.begin() + pos);
	}

	return line;
}

std::string LineProcessorHelper::RemoveEntryOfCharacters(const std::string& line, std::vector<std::string> strings)
{
	std::string result(line);
	for (const auto s : strings)
	{
		size_t pos = result.find(s);
		if (pos != std::string::npos)
		{
			result.erase(pos, 1);
		}
	}

	return result;
}



