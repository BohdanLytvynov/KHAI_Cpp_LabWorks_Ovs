#include "KeyWordProcessor.h"
#include"LineProcessorHelper.h"

KeyWordProcessorBase::KeyWordProcessorBase()
{
}

////////////////////////SingleKeyWordProcessorBase
SingleKeyWordProcessorBase::SingleKeyWordProcessorBase() :m_keyWord("")
{
}

SingleKeyWordProcessorBase::SingleKeyWordProcessorBase(const std::string& keyWord) :m_keyWord(keyWord)
{
}

std::string& SingleKeyWordProcessorBase::getKeyWord()
{
	return m_keyWord;
}

//////////////////////MultipleKeyWordProcessorBase
MultipleKeyWordProcessorBase::MultipleKeyWordProcessorBase()
{
}

MultipleKeyWordProcessorBase::MultipleKeyWordProcessorBase(std::vector<std::string> keyWords)
	: m_keyWords(keyWords)
{
}

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
{
}

TypeKeyWordProcessor::TypeKeyWordProcessor() :MultipleKeyWordProcessorBase()
{
}

bool TypeKeyWordProcessor::Process(std::string& line, Object* object)
{
	auto keywords = MultipleKeyWordProcessorBase::getKeyWords();

	auto res = LineProcessorHelper::GetTypeAndNameFromLine(line, keywords, " ", ";");

	if (res.size() == 2)
	{
		Field f(res[1], res[0]);
		
		object->appendField(f);

		return true;
	}

	return false;

}

MultipleKeyWordProcessor::MultipleKeyWordProcessor(std::vector<std::string> keyWords)
	: MultipleKeyWordProcessorBase(keyWords)
{
}

MultipleKeyWordProcessor::MultipleKeyWordProcessor()
{
}

bool MultipleKeyWordProcessor::Process(std::string& line, Object* object)
{
	auto keywords = MultipleKeyWordProcessorBase::getKeyWords();

	//We have found the ',' it means, that we have discovered line with 2 types
	if (line.find(",") != std::string::npos)
	{
		std::vector<std::string> res;	
		std::string typeWithoutPtr;
		auto parts = LineProcessorHelper::SplitLine(line, *",");
		int i = 0;		
		for (auto& p : parts)
		{
			if (i == 0)
			{
				p.append(";");

				res = LineProcessorHelper::GetTypeAndNameFromLine(p, keywords, " ", ";");

				const char symb[] = " *";

				typeWithoutPtr = LineProcessorHelper::RemoveEntryOfCharacters(res[0], { " ", "*"});
						
				Field f(res[1], res[0]);

				f.setIsPtr(LineProcessorHelper::HasPtr(line));

				object->appendField(f);
			}
			else
			{			

				//ProcessName
				auto name = LineProcessorHelper::RemoveEntryOfCharacters(p, {" ", ";", "*"});

				//Process Common Type				
				bool hasPtr = LineProcessorHelper::HasPtr(p);
				
				Field f(name, hasPtr ? typeWithoutPtr + "*" : typeWithoutPtr, hasPtr);

				object->appendField(f);
			}
			
			++i;
		}

		return true;
	}

	return false;
}
