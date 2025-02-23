#include "pch.h"
#include "console_ui.h"

ui::ConsoleUI::ConsoleUI(HANDLE consoleHandler, 
	io::ConsoleInputOutput* inputModule, 
	g::ConsoleGraphics* consoleGraphicsModule)
{
	_consoleHandler = consoleHandler;
	if (inputModule == nullptr)
	{
		_inputModule = new io::ConsoleInputOutput(consoleHandler);
		_inpModuleDefUsed = true;
	}
	else
	{
		_inputModule = inputModule;
		_inpModuleDefUsed = false;
	}
	
	if (consoleGraphicsModule == nullptr)
	{ 
		_consoleGraphicsModule = new graphics::ConsoleGraphics(_inputModule);
		_graphModuleDefaultUsed = true;
	}
	else
	{
		_consoleGraphicsModule = consoleGraphicsModule;
		_graphModuleDefaultUsed = false;
	}
	
}

ui::ConsoleUI::~ConsoleUI()
{
	if (_inpModuleDefUsed)
		delete _inputModule;
	if (_graphModuleDefaultUsed)
		delete _consoleGraphicsModule;
}

void ui::ConsoleUI::Print(LPTSTR value)
{
	_inputModule->PrintLine(value);
}

void ui::ConsoleUI::ReadLine(LPTSTR value, size_t size)
{
	_inputModule->ReadLine(value, size);
}

void ui::ConsoleUI::DrawView()
{
	for (auto& v : m_views)
	{
		v->Draw(_consoleGraphicsModule, v->getPosition());
	}
}

void ui::ConsoleUI::RegisterView(ui_controls::View* view)
{
	if (view == nullptr)
		throw std::exception("Parameter element was nullptr!");

	m_views.push_back(view);
}

