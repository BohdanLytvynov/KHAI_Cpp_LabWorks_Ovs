
#include <iostream>
#include <crtdbg.h>
#include"../DataStructures/data_structures.h"
#include"../ConsoleColors/console_colors.h"
#include"../ConsoleUI/console_ui.h"

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


}


