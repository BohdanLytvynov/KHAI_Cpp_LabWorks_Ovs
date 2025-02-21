
#ifndef RECTANGLE_H

#define RECTANGLE_H

#include"../ConsoleUI/Shape.h"

namespace shapes
{

	using namespace shapes_base;

	struct Rectangle : public Shape
	{
		Rectangle(COORD coord, uint width, uint height,
			WORD borderForegroundColor,
			WORD borderBackgroundColor,
			WORD fillForegroundColor,
			WORD fillBackgroundColor,
			const char* fillSymbols = nullptr,
			const char* borderSymbols = nullptr);

		void Draw(console_IO* IO) override;
	};

}
#endif



