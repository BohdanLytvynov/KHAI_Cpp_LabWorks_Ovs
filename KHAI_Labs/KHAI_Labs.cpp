


#include <iostream>
#include<crtdbg.h>
#include"../DataStructures/data_structures.h"

int main()
{
    using namespace ds;

    int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
    flag |= _CRTDBG_LEAK_CHECK_DF;
    _CrtSetDbgFlag(flag);
   
    ds::linear_ds::single_linked_list<int> sll;

    std::exception err;

    int r = sll.addToStart(1, err);

   if (r == 0)
   {
        int len = sll.length();
        int* res = new int[len];

        if (sll.ToArray(res, err) == 0)
        {
            for (size_t i = 0; i < len; i++)
            {
                printf("Value is: %s\n", res[i]);
            }
        }
   }
   else
   {
        printf("error on adding %s\n", err.what());
   }

    

}


