#include "KeyWordProcessor.h"
#include"LineProcessorHelper.h"

KeyWordProcessorBase::KeyWordProcessorBase()
{}

////////////////////////SingleKeyWordProcessorBase
SingleKeyWordProcessorBase::SingleKeyWordProcessorBase():m_keyWord("")
{}

SingleKeyWordProcessorBase::SingleKeyWordProcessorBase(const std::string& keyWord):m_keyWord(keyWord)
{}

std::string& SingleKeyWordProcessorBase::getKeyWord()
{
	return m_keyWord;
}

//////////////////////MultipleKeyWordProcessorBase
MultipleKeyWordProcessorBase::MultipleKeyWordProcessorBase()
{}

MultipleKeyWordProcessorBase::MultipleKeyWordProcessorBase(std::vector<std::string> keyWords)
	: m_keyWords(keyWords)
{}

std::vector<std::string>& MultipleKeyWordProcessorBase::getKeyWords()
{
	return m_keyWords;
}


////////////////////////Struct Class Processor
StructClassKeyWordProcessor::StructClassKeyWordProcessor(const std::string& keyWord) 
	: SingleKeyWordProcessorBase(keyWord)
{
}

bool StructClassKeyWordProcessor::Process(std::string& line, Object* object)
{
	if (LineProcessorHelper::LineContains(line, SingleKeyWordProcessorBase::getKeyWord()))
	{
		auto words = LineProcessorHelper::SplitLine(line, ' ');

		if (words.size() == 2)
		{
			if (words[1].find("{") != std::string::npos)
			{
				words[1].erase(words[1].end() - 1);
			}

			object->setName(words[1]);
			object->isStruct() = true;

			return true;
		}
	}

	return false;
}
//////////////////Type Processor

TypeKeyWordProcessor::TypeKeyWordProcessor(std::vector<std::string> keyWords)
	:MultipleKeyWordProcessorBase(keyWords)
{}

TypeKeyWordProcessor::TypeKeyWordProcessor():MultipleKeyWordProcessorBase()
{}

bool TypeKeyWordProcessor::Process(std::string & line, Object * object)
{
	auto keywords = MultipleKeyWordProcessorBase::getKeyWords();

	auto res = LineProcessorHelper::GetTypeAndNameFromLine(line, keywords, " ", ";");

	if (res.size() == 2)
	{
		Field f(res[1], res[0]);

		object->getFields().push_back(f);

		return true;
	}

	return false;
	
}


