#ifndef KEYWORDPROCESSOR_H

#define KEYWORDPROCESSOR_H
#include<string>
#include"Object.h"

/// <summary>
/// Abstract base class for all KeyWordProcessors
/// </summary>
struct KeyWordProcessorBase
{
	KeyWordProcessorBase();
	
	virtual void Process(std::string& line, Object* object) = 0;
};

struct SingleKeyWordProcessorBase : public KeyWordProcessorBase
{
	SingleKeyWordProcessorBase();

	SingleKeyWordProcessorBase(std::string& keyWord);

protected:
	std::string& getKeyWord();

private:
	std::string m_keyWord;
};

struct MultipleKeyWordProcessorBase : public KeyWordProcessorBase
{
	MultipleKeyWordProcessorBase();

	MultipleKeyWordProcessorBase(std::vector<std::string> keyWords);

protected:
	std::vector<std::string>& getKeyWords();

private:
	std::vector<std::string> m_keyWords;
};

////////////////////////////////////////

//Handle struct word

struct StructClassKeyWordProcessor : public SingleKeyWordProcessorBase
{
	StructClassKeyWordProcessor(std::string& keyWord);

	void Process(std::string& line, Object* object) override;
};

//Handle types

struct TypeKeyWordProcessor : public MultipleKeyWordProcessorBase
{
	TypeKeyWordProcessor(std::vector<std::string> keyWords);

	TypeKeyWordProcessor();

	void Process(std::string& line, Object* object) override;
};



#endif

