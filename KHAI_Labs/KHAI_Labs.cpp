
#include <iostream>
#include <crtdbg.h>
#include<fstream>
#include<string>
#include"Object.h"
#include<vector>
#include"Field.h"
#include"FileProcessor.h"
#include "FileBuilderBase.h"
#include "LineProcessorHelper.h"

std::string GetFilename(std::string& path)
{
    auto arr = LineProcessorHelper::SplitLine(path, *"\\");

    return *(arr.end() - 1);
}

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

    //Configure And Setup Processing Pipeline

    vector<string> keyWords = {"long", "int", "int*", "double", "double*" , "*"};

    vector<KeyWordProcessorBase*> processors;
     
    auto p1 = StructClassKeyWordProcessor("struct");
    auto p2 = StructClassKeyWordProcessor("class");
    auto p3 = MultipleKeyWordProcessor(keyWords);
    auto p4 = TypeKeyWordProcessor(keyWords);

    processors.push_back(&p1);
    processors.push_back(&p2);
    processors.push_back(&p3);
    processors.push_back(&p4);

    unique_ptr<FileProcessor> fileProcessor = make_unique<FileProcessor>(processors);
  
    //Main Cycle

    do
    {
        Object obj;

        printf("\tВведіть абсолютний шлях до файла із классом або структурою та натисніть клавішу Ентер\n");
        printf("\tЯкщо ви хочете вийти з программи натисніть клавішу q\n");

        getline(cin, pathToFile);

        bool pathCorrect = false;

        fstream fileStream;

        string filename = GetFilename(pathToFile);

        fileStream.open(pathToFile.c_str(), ios::in);

        pathCorrect = fileStream.is_open();

        if (pathCorrect)
        {
            fileProcessor->ProcessFile(&fileStream, &obj);
            fileStream.close();
            
            printf("Обробка файла Завершена!\n");
            auto fields = obj.getFields();
            if (fields.size() == 0)
            {
                printf("НАЖАЛЬ не вдалося знайти ніяких полів!\n\n");
            }
            else
            {
                printf("Було знайдено наступні поля:\n");

                int i = 1;
                for (auto field : fields)
                    printf("\t%d) %s\n", i++, field.ToString().c_str());

                printf("Введіть шлях де ви хочете створити *.h файл та натисніть Enter:\n");

                getline(cin, pathToFile);

                ofstream outFileStream((pathToFile + "\\" + filename).c_str(), std::ios::app);

                bool cppBuildPossible = false;

                if (outFileStream.is_open())
                {
                    printf("Створюю новий *.h файл...\n\n");

                    auto fb = FileBuilderFactory::getFileBuilder(FileType::h);

                    fb->SetupBuilder(&outFileStream, &filename, &obj);

                    fb->Build();

                    printf("Створення *.h файлу завершено.\n\n");

                    cppBuildPossible = true;

                    outFileStream.close();
                }
                else
                {
                    printf("Помилка під час створення *.h файла!\n");
                }

                bool testcompilePossible = false;

                if (cppBuildPossible)
                {
                    printf("Введіть шлях де ви хочете створити *.cpp файл та натисніть Enter:\n");

                    getline(cin, pathToFile);

                    std::string cpp(filename);

                    if (cpp.find(".h") != std::string::npos)
                    {
                        cpp.erase(cpp.end() - 1);
                        cpp.append("cpp");
                    }

                    outFileStream.open((pathToFile + "\\" + cpp).c_str(), std::ios::app);

                    if (outFileStream.is_open())
                    {
                        printf("Створюю новий *.cpp файл...\n\n");

                        auto fb = FileBuilderFactory::getFileBuilder(FileType::cpp);

                        fb->SetupBuilder(&outFileStream, &filename, &obj);

                        fb->Build();

                        printf("Створення *.cpp файлу завершено.\n\n");

                        testcompilePossible = true;

                        outFileStream.close();
                    }
                    else
                    {
                        printf("Помилка під час створення *.cpp файла!\n");
                    }
                }

                if (testcompilePossible)
                {
                    //Compile to test
                }
            }
        }
        else
        {
            fileStream.close();
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