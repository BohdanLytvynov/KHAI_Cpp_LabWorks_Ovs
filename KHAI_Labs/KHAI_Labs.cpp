
#include <iostream>
#include <crtdbg.h>
#include"../DataStructures/data_structures.h"
#include"../ConsoleColors/console_colors.h"
#include"../ConsoleUI/console_ui.h"
#include"../ConsoleUI/Shapes.h"
#include"../ConsoleUI/UIElements.h"

io::ConsoleInputOutput* IO;
graphics::ConsoleGraphics* g;
ui::ConsoleUI* UI;

int main()
{
#pragma region View Shapes

    shapes::Rectangle mainView();

#pragma endregion


    IO->Execute("chcp 1251");

    int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
    flag |= _CRTDBG_LEAK_CHECK_DF;
    _CrtSetDbgFlag(flag);

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    IO = new io::ConsoleInputOutput(console);
    g = new graphics::ConsoleGraphics(IO);
    UI = new ui::ConsoleUI(IO, g);

    namespace uc = ui_controls;

    //uc::View view("Main", );

    delete UI;
    delete g;
    delete IO;
}


