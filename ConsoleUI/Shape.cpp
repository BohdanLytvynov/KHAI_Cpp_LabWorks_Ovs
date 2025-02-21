#include "pch.h"
#include "Shape.h"

shapes_base::Shape::Shape(
	COORD coord, uint width, uint height,
	WORD borderForegroundColor,
	WORD borderBackgroundColor,
	WORD fillForegroundColor,
	WORD fillBackgroundColor,
	const char* fillSymbols = nullptr,
	const char* borderSymbols = nullptr
	)
{
	m_coord = coord;
	m_width = width;
	m_height = height;
	m_borderForegroundColor = borderForegroundColor;
	m_borderBackgroundColor = borderBackgroundColor;
	m_FillForegroundColor = fillForegroundColor;
	m_FillBackgroundColor = fillBackgroundColor;
	m_fillSymbols = fillSymbols;
	m_borderSymbols = borderSymbols;
}

COORD& shapes_base::Shape::getCOORD()
{
	return m_coord;
}

uint shapes_base::Shape::getWidth()
{
	return m_width;
}

uint shapes_base::Shape::getHeight()
{
	return m_height;
}

WORD& shapes_base::Shape::getBorderForegroundColor()
{
	return m_borderForegroundColor;
}

WORD& shapes_base::Shape::getBorderBackgroundColor()
{
	return m_borderBackgroundColor;
}

WORD& shapes_base::Shape::getFillForegroundColor()
{
	return m_FillForegroundColor;
}

WORD& shapes_base::Shape::getFillBackgroundColor()
{
	return m_FillBackgroundColor;
}

char*& shapes_base::Shape::getBorderSymbols()
{
	return m_borderSymbols;
}

char*& shapes_base::Shape::getFillSymbols()
{
	return m_fillSymbols;
}