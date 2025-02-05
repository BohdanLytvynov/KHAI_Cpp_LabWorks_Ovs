
#include <iostream>
#include<crtdbg.h>

int main()
{
    int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
    flag |= _CRTDBG_LEAK_CHECK_DF;
    _CrtSetDbgFlag(flag);

    int* ptr = new int[5];

    std::cout << "Hello World!\n";
}


