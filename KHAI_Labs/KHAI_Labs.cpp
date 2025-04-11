
#include <iostream>
#include <crtdbg.h>
#include<fstream>
#include<string>
#include"Object.h"
#include<vector>
#include"Field.h"


int main()
{
    using namespace std;

    string pathToFile;

    int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
    flag |= _CRTDBG_LEAK_CHECK_DF;
    _CrtSetDbgFlag(flag);
   
    system("chcp 1251");
   
    printf("\tЛитвинов Богдан Юрійович 125 група\n\n");
    printf("\tЛабораторна робота номер 2 ІЗВП Варіант 9\n\n");
    printf("\tНеобхідно розробити программу, що Вичитує файл з декларейшинами (long int*, double*, double) та розширює його за допомогою дефінішенів та створює деструктор.\n\n");

    //Main Cycle

    do
    {
        printf("\tВведіть абсолютний шлях до файла із классом або структурою та натисніть клавішу Ентер\n");
        printf("\tЯкщо ви хочете вийти з программи натисніть клавішу q\n");

        getline(cin, pathToFile);

        bool pathCorrect = false;

        fstream fileStream;

        fileStream.open(pathToFile.c_str(), ios::in);

        pathCorrect = fileStream.is_open();

        if (pathCorrect)
        {
            char line[2048];

            //Process file
            while (!fileStream.eof())
            {
                fileStream.getline(line, sizeof(line));


            }
        }
        else
        {
            printf("\tПомилка сталася під час відкриття файла!\n");
        }

        if (pathToFile == "q" || pathToFile == "Q" || pathToFile == "Й" || pathToFile == "й")
        {
            printf("Приємно було попрацювати! До побачення!");
            break;
        }
    } while (true);

    return 0;
}