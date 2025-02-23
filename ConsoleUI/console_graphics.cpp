#include "pch.h"
#include "console_graphics.h"

graphics::ConsoleGraphics::ConsoleGraphics(console_IO* IO)
{
	m_console_IO = IO;
}

void graphics::ConsoleGraphics::Draw(shapes::Shape* shape, COORD position)
{
	shape->Draw(m_console_IO, position);
}
