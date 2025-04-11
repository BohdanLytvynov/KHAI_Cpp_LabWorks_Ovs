#include "KeyWordProcessor.h"
#include"LineProcessorHelper.h"

KeyWordProcessorBase::KeyWordProcessorBase()
{}

////////////////////////SingleKeyWordProcessorBase
SingleKeyWordProcessorBase::SingleKeyWordProcessorBase():m_keyWord("")
{}

SingleKeyWordProcessorBase::SingleKeyWordProcessorBase(std::string& keyWord):m_keyWord(keyWord)
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
StructClassKeyWordProcessor::StructClassKeyWordProcessor(std::string& keyWord) 
	: SingleKeyWordProcessorBase(keyWord)
{
}

void StructClassKeyWordProcessor::Process(std::string& line, Object* object)
{
	if (LineProcessorHelper::LineContains(line, SingleKeyWordProcessorBase::getKeyWord()))
	{
		auto words = LineProcessorHelper::SplitLine(line, ' ');

		if (words.size() == 2)
		{
			object->setName(words[1]);
			object->isStruct() = true;
		}
	}
}
//////////////////Type Processor

TypeKeyWordProcessor::TypeKeyWordProcessor(std::vector<std::string> keyWords)
	:MultipleKeyWordProcessorBase(keyWords)
{}

TypeKeyWordProcessor::TypeKeyWordProcessor():MultipleKeyWordProcessorBase()
{}

void TypeKeyWordProcessor::Process(std::string & line, Object * object)
{
	auto keywords = MultipleKeyWordProcessorBase::getKeyWords();

	auto res = LineProcessorHelper::GetTypeAndNameFromLine(line, keywords, *" ", *";");

	Field f(res[1], res[0]);

	object->getFields().push_back(f);
}


