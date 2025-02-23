
#include <iostream>
#include <crtdbg.h>
#include"../DataStructures/data_structures.h"
#include"../ConsoleColors/console_colors.h"
#include"../ConsoleUI/console_ui.h"
#include"../ConsoleUI/Shapes.h"

void ExecCommand(const char* command)
{
    FILE* fd = _popen(command, "r");
}

int main()
{
    //ExecCommand("chcp 1251");

    int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
    flag |= _CRTDBG_LEAK_CHECK_DF;
    _CrtSetDbgFlag(flag);

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    io::ConsoleInputOutput io(console);
    graphics::ConsoleGraphics g(&io);

    int x =1 , y = 1;
    shapes::Rectangle rect(10,3, Colors::BLACK, Colors::WHITEBack, Colors::BLACK, Colors::BLACKBack );

    g.Draw(&rect, Build_COORD(1,1));

}


