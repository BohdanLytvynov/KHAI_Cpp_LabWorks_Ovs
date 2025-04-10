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
			path = TEXT("D:\\KHAI\\KHAI_Cpp_LabWorks_Ovs\\Directory_StaticLib_UT\\Test");
		}
		
		TEST_METHOD(GetFilesTest_Success)
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

			Assert::IsTrue(lstrcmp(res[0].cFileName, L"file1.txt") == 0, incorrectFile);
			Assert::IsTrue(lstrcmp(res[1].cFileName, L"file2.txt") == 0, incorrectFile);
			Assert::IsTrue(lstrcmp(res[2].cFileName, L"file3.txt") == 0, incorrectFile);
			Assert::IsTrue(lstrcmp(res[3].cFileName, L"file4.txt") == 0, incorrectFile);
			Assert::IsTrue(lstrcmp(res[4].cFileName, L"file5.txt") == 0, incorrectFile);
		}

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
