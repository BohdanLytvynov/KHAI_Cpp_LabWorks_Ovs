#include "pch.h"
#include "CppUnitTest.h"
#include"../Directory_StaticLib/Directory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DirectoryStaticLibUT
{
	TEST_CLASS(DirectoryStaticLibUT)
	{
	public:

		DirectoryStaticLibUT()
		{
			path = TEXT("D:\\KHAI\\C++ Prg Ovsyannic\\Directory_StaticLib_UT\\Test");
		}
		
		/*TEST_METHOD(GetFilesTest_Success)
		{
			namespace fs = filesystem;
			fs::IDirectory* dir = new fs::Directory();
			DWORD error = 0;
			auto res = dir->GetFiles(path, error);
			
			delete dir;

			std::wstringstream str;

			str << TEXT("Error Happened! Code: ") << error;

			wchar_t msg[1024];

			str.getline(msg, sizeof(msg));

			Assert::IsTrue(error == 0, msg);

			const wchar_t* incorrectFile = TEXT("Fail to find the test file!");

			Assert::IsTrue(res[0].getFileName() == L"file1.txt", incorrectFile);
			Assert::IsTrue(res[1].getFileName() == L"file2.txt", incorrectFile);
			Assert::IsTrue(res[2].getFileName() == L"file3.txt", incorrectFile);
			Assert::IsTrue(res[3].getFileName() == L"file4.txt", incorrectFile);
			Assert::IsTrue(res[4].getFileName() == L"file5.txt", incorrectFile);
		}*/

		TEST_METHOD(Path_Muatae_Test_Success1)
		{
			namespace fs = filesystem;

			LPCTSTR path = TEXT("D:\\Folder1\\Folder2\\Folder3\\File1");
			LPCTSTR success_result = TEXT("D:\\Folder1\\Folder2\\Folder3");
		
			TCHAR* result = fs::Path::Mutate(path, TEXT("Folder3"), TEXT("\\"));

			Assert::IsTrue(lstrcmp(result, success_result) == 0, TEXT("Actual result is not the same as Success_Result!"));

			free(result);
		}

		TEST_METHOD(Path_Muatae_Test_Success2)
		{
			namespace fs = filesystem;

			LPCTSTR path = TEXT("D:\\Folder1\\Folder2\\Folder3\\File1");
			LPCTSTR success_result = TEXT("D:\\Folder1");
			
			TCHAR* result = fs::Path::Mutate(path, TEXT("Folder1"), TEXT("\\"));

			Assert::IsTrue(lstrcmp(result, success_result) == 0, TEXT("Actual result is not the same as Success_Result!"));
			free(result);
		}

	private:		
		LPCTSTR path = nullptr;
	};
}
