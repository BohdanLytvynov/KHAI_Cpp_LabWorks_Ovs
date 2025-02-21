#include "pch.h"
#include "Rectangle.h"

shapes::Rectangle::Rectangle(COORD coord, uint width, uint height,
	WORD borderForegroundColor, 
	WORD borderBackgroundColor, 
	WORD fillForegroundColor, 
	WORD fillBackgroundColor, 
	const char* fillSymbols = nullptr, 
	const char* borderSymbols = nullptr)
	:Shape(coord, width, height, 
		borderForegroundColor, 
		borderBackgroundColor, 
		fillForegroundColor, 
		fillBackgroundColor, 
		fillSymbols, 
		borderSymbols)
{
	if (!borderSymbols)
	{
		char brdSymbl[8] = {char(201), char(187), char(188), char(200), char(205), char(186)};
		Shape::getBorderSymbols() = brdSymbl;
	}

	if (!fillSymbols)
	{
		char s = ' ';
		Shape::getFillSymbols() = &s;
	}
}

void shapes::Rectangle::Draw(console_IO* IO)
{
	uint height = Shape::getHeight();

	uint width = Shape::getWidth();

	COORD pos = Shape::getCOORD();

	bool dec_symbol = false;
	
	WORD color;

	WORD borderColor = Shape::getBorderForegroundColor() | Shape::getBorderBackgroundColor();
	WORD backGroundColor = Shape::getFillForegroundColor() | Shape::getFillBackgroundColor();
	char* fillSymbol = Shape::getFillSymbols();
	char selectedSymbol;;

	char* symbols = Shape::getBorderSymbols();

	for (uint i = 0; i < height; i++)
	{
		for (uint j = 0; j < width; j++)
		{
			dec_symbol = false;

			COORD newPos;
			newPos.X = j;
			newPos.Y = i;
			
			SetConsoleCursorPosition(IO->GetConsoleHandle(), pos + newPos);

			color = borderColor;

			//Corner Symbol Switcher
			if (i == 0 && j == 0)//Left upper corner
			{
				selectedSymbol = *symbols;
				dec_symbol = true;
			}
			else if (i == 0 && j == width - 1)//Right upper corner
			{
				selectedSymbol = *(symbols + 1);
				dec_symbol = true;
			}
			else if (i == height - 1 && j == 0)//Left lower corner
			{
				selectedSymbol = *(symbols + 3);
				dec_symbol = true;
			}
			else if (i == height - 1 && j == width - 1)//Right lower corner
			{
				selectedSymbol = *(symbols + 2);
				dec_symbol = true;
			}

			//Line Symblo Switcher

			if (i == 0 && j < width - 1 && j > 0)//Upper horizontal Line
			{
				selectedSymbol = *(symbols + 4);
				dec_symbol = true;
			}
			else if (j == width - 1 && i > 0 && i < height - 1)//right Vertical Line
			{
				selectedSymbol = *(symbols + 5);
				dec_symbol = true;
			}
			else if (i == height - 1 && j > 0 && j < width - 1)//Lower horizontal Line
			{
				selectedSymbol = *(symbols + 4);
				dec_symbol = true;
			}
			else if (j == 0 && i > 0 && i < height - 1)//Left Vertical Line
			{
				selectedSymbol = *(symbols + 5);
				dec_symbol = true;
			}
			if (!dec_symbol) //Filler
			{
				selectedSymbol = *fillSymbol;
				color = backGroundColor;
			}

			IO->PrintLine(&selectedSymbol, color);
		}
	}
}


