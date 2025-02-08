


#include <iostream>
#include<crtdbg.h>
#include"../DataStructures/data_structures.h"

int main()
{
    int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
    flag |= _CRTDBG_LEAK_CHECK_DF;
    _CrtSetDbgFlag(flag);

    using namespace ds;
    using namespace std;

     
}


