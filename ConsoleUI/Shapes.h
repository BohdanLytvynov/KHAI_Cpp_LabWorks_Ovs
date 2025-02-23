
#ifndef SHAPE_H

#define SHAPE_H

#pragma region EXPORTER

#ifdef SHAPES_EXPORRT
#define SHAPES_API __declspec(dllexport)
#else
#define SHAPES_API __declspec(dllexport)
#endif

#pragma endregion

#include"../ConsoleUI/console_io.h"

typedef io::ConsoleInputOutput console_IO;
typedef unsigned int uint;

namespace shapes
{	
	struct Shape
	{
		Shape(uint width, uint height, 			
			WORD borderForegroundColor,
			WORD borderBackgroundColor,			
			WORD fillForegroundColor,
			WORD fillBackgroundColor,
			const char* codepage,
			char* fillSymbols = nullptr, 
			char* borderSymbols = nullptr);

		virtual void Draw(console_IO* IO, COORD coord) = 0;

		~Shape();
				
		uint getWidth();
		uint getHeight();

		char*& getBorderSymbols();
		WORD& getBorderForegroundColor();
		WORD& getBorderBackgroundColor();

		char*& getFillSymbols();
		WORD& getFillBackgroundColor();
		WORD& getFillForegroundColor();
		
		const char* getCodePage();

	protected:
		bool m_defborderSymblUsed;
		bool m_deffillSymblUsed;
		
	private:		
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

		//CodePage name to draw this shape
		const char* m_codePage;
	};

	struct Rectangle : public Shape
	{
		SHAPES_API Rectangle(uint width, uint height,
			WORD borderForegroundColor,
			WORD borderBackgroundColor,
			WORD fillForegroundColor,
			WORD fillBackgroundColor,
			const char* codepage = "866",
			char* fillSymbols = nullptr,
			char* borderSymbols = nullptr);

		SHAPES_API ~Rectangle();

		void Draw(console_IO* IO, COORD coord) override;
	};
}

#endif




