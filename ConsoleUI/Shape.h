
#ifndef SHAPE_H

#define SHAPE_H

#include"../ConsoleUI/console_io.h"

typedef io::ConsoleInputOutput console_IO;
typedef unsigned int uint;

namespace shapes_base
{	
	struct Shape
	{
		Shape(COORD coord, uint width, uint height, 			
			WORD borderForegroundColor,
			WORD borderBackgroundColor,			
			WORD fillForegroundColor,
			WORD fillBackgroundColor,
			const char* fillSymbols = nullptr, 
			const char* borderSymbols = nullptr
			);

		virtual void Draw(console_IO* IO) = 0;

		COORD& getCOORD();

		uint getWidth();
		uint getHeight();

		char*& getBorderSymbols();
		WORD& getBorderForegroundColor();
		WORD& getBorderBackgroundColor();

		char*& getFillSymbols();
		WORD& getFillBackgroundColor();
		WORD& getFillForegroundColor();
	private:
		//Location of the shape				
		COORD m_coord;

		//Size of the shape
		uint m_width;
		uint m_height;

		//Border paraneters
		char* m_borderSymbols;
		WORD m_borderForegroundColor;
		WORD m_borderBackgroundColor;

		//Fill properties
		char* m_fillSymbols;
		WORD m_FillBackgroundColor;
		WORD m_FillForegroundColor;
	};
}

#endif




