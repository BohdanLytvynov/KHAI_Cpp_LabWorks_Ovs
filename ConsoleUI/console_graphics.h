
#ifndef CONSOLE_GRAPHICS_H

#define CONSOLE_GRAPHICS_H

#include"../ConsoleUI/console_io.h"
#include"../ConsoleUI/Shapes.h"

#pragma region Exporter    

#ifdef CONSOLE_GRAPHICS_EXPORT

#define CONSOLE_GRAPHICS_API __declspec(dllexport)

#else

#define CONSOLE_GRAPHICS_API __declspec(dllimport)

#endif

#pragma endregion

namespace graphics
{
    typedef io::ConsoleInputOutput console_IO;
    /// <summary>
    /// Class that is used to use console graphics functions
    /// </summary>
    struct CONSOLE_GRAPHICS_API ConsoleGraphics
    {
        ConsoleGraphics(console_IO* IO);

        void Draw(shapes::Shape* shape, COORD position);

    private:
        console_IO* m_console_IO;
    };
}

#endif // !CONSOLE_GRAPHICS_H


