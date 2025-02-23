#include"pch.h"
#include"console_io.h"

io::ConsoleInputOutput::ConsoleInputOutput(HANDLE console,
	WORD defForegroundColor, WORD defBackGroundColor,
	WORD defErrorForegroundColor, WORD defErrorBackgroundColor)
{
	m_consoleHandle = console;
	m_def_foreground = defForegroundColor;
	m_def_background = defBackGroundColor;
	m_def_errorForeground = defErrorForegroundColor;
	m_def_errorBackground = defErrorBackgroundColor;
}

io::ConsoleInputOutput::ConsoleInputOutput(HANDLE console)
	: ConsoleInputOutput(console,
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
		0,
		FOREGROUND_RED,
		0
	)
{
}

io::ConsoleInputOutput::ConsoleInputOutput(HANDLE console, WORD defForegroundColor, WORD defBackGroundColor)
	:ConsoleInputOutput(console, defForegroundColor, defBackGroundColor,
		FOREGROUND_RED, 0)
{
}

io::ConsoleInputOutput::ConsoleInputOutput(HANDLE console, WORD defErrorForegroundColor, WORD defErrorBackgroundColor, ...)
	: ConsoleInputOutput(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
		0, defErrorForegroundColor, defErrorBackgroundColor)
{

}

void io::ConsoleInputOutput::PrintLine(LPCTSTR value)
{
#ifdef _UNICODE
	std::wcout << *value << std::endl;
#else //Prj builds using ASCII
	std::cout << *value << std::endl;
#endif
}

void io::ConsoleInputOutput::PrintLine(LPCTSTR value, WORD color)
{
	SetConsoleTextAttribute(m_consoleHandle, color);
#ifdef _UNICODE
	std::wcout << *value << std::endl;
#else //Prj builds using ASCII
	std::cout << *value << std::endl;
#endif
	SetConsoleTextAttribute(m_consoleHandle, m_def_foreground | m_def_background);
}

void io::ConsoleInputOutput::PrintLine(const char* value, WORD color)
{
	SetConsoleTextAttribute(m_consoleHandle, color);
	std::cout << *value << std::endl;
	SetConsoleTextAttribute(m_consoleHandle, m_def_foreground | m_def_background);
}

void io::ConsoleInputOutput::Print(LPCTSTR value, COORD coord)
{
	SetCursorPosition(coord);
	PrintLine(value);
}

void io::ConsoleInputOutput::Print(const char* value, COORD coord)
{
	SetCursorPosition(coord);
	PrintLine(value);
}

void io::ConsoleInputOutput::Print(LPCTSTR value, COORD coord, WORD color)
{
	SetCursorPosition(coord);
	PrintLine(value, color);
}

void io::ConsoleInputOutput::Print(const char* value, COORD coord, WORD color)
{
	SetCursorPosition(coord);
	PrintLine(value, color);
}

void io::ConsoleInputOutput::ReadLine(LPTSTR value, size_t length)
{
#ifdef _UNICODE
	std::wcin.getline(value, length);
#else //Prj builds using ASCII
	std::cin.getline(value, length);
#endif
}

void io::ConsoleInputOutput::PrintLine(const char* value)
{
	std::cout << *value << std::endl;
}

void io::ConsoleInputOutput::ReadLine(char* value, size_t length)
{
	std::cin.getline(value, length);
}

void io::ConsoleInputOutput::Input(LPCTSTR msg, LPTSTR& buff, std::function<bool(LPCTSTR result, LPTSTR& error)> validator)
{
	TCHAR temp[1024];
	LPTSTR error = nullptr;

	do
	{
		if (msg)
		{
			PrintLine(msg);
		}

		ReadLine(temp, sizeof(temp));

		if (validator && !validator(temp, error))
		{
			PrintLine(TEXT("Error during validation!"), m_def_errorForeground | m_def_errorBackground);
			PrintLine(error);
			std::memset(temp, 0, sizeof(temp));
			error = nullptr;
			continue;
		}

		break;

	} while (true);

	buff = temp;
}

void io::ConsoleInputOutput::Input(const char* msg, char*& buff, std::function<bool(const char* result, char*& error)> validator)
{
	char temp[1024];
	char* error = nullptr;

	do
	{
		if (msg)
		{
			PrintLine(msg);
		}

		ReadLine(temp, sizeof(temp));

		if (validator && !validator(temp, error))
		{
			PrintLine("Error during validation!", m_def_errorForeground | m_def_errorBackground);
			PrintLine(error);
			std::memset(temp, 0, sizeof(temp));
			error = nullptr;
			continue;
		}

		break;

	} while (true);

	buff = temp;
}

HANDLE io::ConsoleInputOutput::GetConsoleHandle()
{
	return m_consoleHandle;
}

void io::ConsoleInputOutput::Execute(const char* command)
{
	FILE* fd = _popen(command, "r");
}

void io::ConsoleInputOutput::SetCursorPosition(COORD cursorPosition)
{
	SetConsoleCursorPosition(m_consoleHandle, cursorPosition);
}

void io::ConsoleInputOutput::Combine(char*& result, size_t length, size_t paramsCount ...)
{
	size_t* Ptr = &paramsCount;

	std::stringstream str;

	for (size_t i = 1; i <= paramsCount; i++)
	{
		str << *(Ptr + i);
	}

	str.getline(result, length);

	str.clear();
}

COORD Build_COORD(int x, int y)
{
	COORD cord;
	cord.X = x;
	cord.Y = y;

	return cord;
}

COORD operator+(COORD l, COORD r)
{
	return Build_COORD(l.X + r.X, l.Y + r.Y);
}

COORD operator-(COORD l, COORD r)
{
	return Build_COORD(l.X - r.X, l.Y - r.Y);
}
