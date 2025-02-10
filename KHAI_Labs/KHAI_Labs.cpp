


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
   
    std::unique_ptr<ds::linear_ds::single_linked_list<int>> intsS = std::make_unique<ds::linear_ds::single_linked_list<int>>();
}


