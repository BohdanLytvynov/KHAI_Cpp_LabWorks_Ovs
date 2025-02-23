#include "pch.h"
#include "console_ui.h"

ui::ConsoleUI::ConsoleUI(HANDLE consoleHandler)
{
	_consoleHandler = consoleHandler;

	_inputModule = new io::ConsoleInputOutput(consoleHandler);
	_inpModuleDefUsed = true;

	_consoleGraphicsModule = new graphics::ConsoleGraphics(_inputModule);
	_graphModuleDefaultUsed = true;
}

ui::ConsoleUI::ConsoleUI(io::ConsoleInputOutput* io, graphics::ConsoleGraphics* g)
{
	this->_inputModule = io;
	_inpModuleDefUsed = false;

	this->_consoleGraphicsModule = g;
	_graphModuleDefaultUsed = false;
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

