#include "pch.h"
#include "Shapes.h"

shapes::Shape::Shape(
	uint width, uint height,
	WORD borderForegroundColor,
	WORD borderBackgroundColor,
	WORD fillForegroundColor,
	WORD fillBackgroundColor,
	char* fillSymbols,
	char* borderSymbols
	)
{	
	m_width = width;
	m_height = height;
	m_borderForegroundColor = borderForegroundColor;
	m_borderBackgroundColor = borderBackgroundColor;
	m_FillForegroundColor = fillForegroundColor;
	m_FillBackgroundColor = fillBackgroundColor;
	m_fillSymbols = fillSymbols;
	m_borderSymbols = borderSymbols;
}

shapes::Shape::~Shape()
{
	if (m_defborderSymblUsed)
	{
		delete[] m_borderSymbols;
		m_borderSymbols = nullptr;
	}

	if (m_deffillSymblUsed)
	{
		delete[] m_fillSymbols;
		m_fillSymbols = nullptr;
	}
		
}

uint shapes::Shape::getWidth()
{
	return m_width;
}

uint shapes::Shape::getHeight()
{
	return m_height;
}

WORD& shapes::Shape::getBorderForegroundColor()
{
	return m_borderForegroundColor;
}

WORD& shapes::Shape::getBorderBackgroundColor()
{
	return m_borderBackgroundColor;
}

WORD& shapes::Shape::getFillForegroundColor()
{
	return m_FillForegroundColor;
}

WORD& shapes::Shape::getFillBackgroundColor()
{
	return m_FillBackgroundColor;
}

char*& shapes::Shape::getBorderSymbols()
{
	return m_borderSymbols;
}

char*& shapes::Shape::getFillSymbols()
{
	return m_fillSymbols;
}

shapes::Rectangle::Rectangle(
	uint width, uint height,
	WORD borderForegroundColor,
	WORD borderBackgroundColor,
	WORD fillForegroundColor,
	WORD fillBackgroundColor,
	char* fillSymbols,
	char* borderSymbols)
	:Shape(width, height,
		borderForegroundColor,
		borderBackgroundColor,
		fillForegroundColor,
		fillBackgroundColor,
		fillSymbols,
		borderSymbols)
{
	char* brdSymblptr = nullptr;
	char* fillSymblptr = nullptr;

	if (borderSymbols == nullptr)
	{
		brdSymblptr = new char[6];

		brdSymblptr[0] = (char)201; //left upper corner symbol
		brdSymblptr[1] = (char)187; //right upper corner symbol
		brdSymblptr[2] = (char)188; //right lower corner symbol
		brdSymblptr[3] = (char)200; //left lower corner symbol
		brdSymblptr[4] = (char)205; //horizontal line symbol
		brdSymblptr[5] = (char)186; //vertical line symbol	
		m_defborderSymblUsed = true;//Rectangle allocates and Rectangle deallocates
	}
	else
	{
		brdSymblptr = borderSymbols;
		m_defborderSymblUsed = false;
	}

	if (fillSymbols == nullptr)
	{
		fillSymblptr = new char[1];
		fillSymblptr[0] = ' ';
		m_deffillSymblUsed = true;//Rectangle allocates and Rectangle deallocates
	}
	else
	{
		fillSymblptr = fillSymbols;
		m_deffillSymblUsed = false;
	}

	this->getBorderSymbols() = brdSymblptr;
	this->getFillSymbols() = fillSymblptr;
}

shapes::Rectangle::~Rectangle()
{
	Shape::~Shape();
}

void shapes::Rectangle::Draw(console_IO* IO, COORD pos)
{
	uint height = Shape::getHeight();

	uint width = Shape::getWidth();
	
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
			
			SetConsoleCursorPosition(IO->GetConsoleHandle(), pos + Build_COORD(j, i));

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