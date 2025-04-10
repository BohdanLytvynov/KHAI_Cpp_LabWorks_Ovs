#include "pch.h"
#include "Directory.h"

std::vector<WIN32_FIND_DATA> filesystem::Directory::GetFiles(LPCTSTR Abs_path, DWORD& error)
{
	namespace fs = filesystem;

	if (_tcslen(Abs_path) == 0)
		throw std::exception("Parameter path was empty!");

	std::vector<WIN32_FIND_DATA> res;

	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA ffd;
	TCHAR szDir[MAX_PATH];
	error = 0;
	
	StringCchCopy(szDir, MAX_PATH, Abs_path);
	StringCchCat(szDir, MAX_PATH, TEXT("\\*"));

	hFind = FindFirstFile(szDir, &ffd);
	int i = 0;
	
	do
	{
		++i;
		if (hFind == INVALID_HANDLE_VALUE)
		{
			error = GetLastError();
			break;
		}
		if (i == 1 || i == 2)
		{
			continue;
		}
		
		res.push_back(ffd);

	} while (FindNextFile(hFind, &ffd));

	FindClose(hFind);

	return res;
}

LPTSTR filesystem::Path::Mutate(LPCTSTR path, LPCTSTR stopWord, LPCTSTR delim)
{
	if (path == nullptr)
		throw std::exception("Path pointer was nullptr!");

	if (stopWord == nullptr)
		throw std::exception("stopWord parameter was nullptr!");

	if (delim == nullptr)
		throw std::exception("delim parameter was nullptr!");

	size_t length = lstrlen(path);
	unsigned char delimCountTemp = 0;
	std::vector<TCHAR> res_g;
	std::vector<TCHAR> word_temp;
	for (size_t i = 0; i < length; i++)
	{
		if (path[i] == *delim)
		{
			word_temp.push_back('\0');
			size_t l = word_temp.size();

			TCHAR* wordForCompare = new TCHAR[word_temp.size()];
			
			for (size_t i = 0; i < l; i++)
			{
				wordForCompare[i] = word_temp[i];
			}

			if (lstrcmp(wordForCompare, stopWord) == 0)
			{
				delete[] wordForCompare;
				break;
			}
						
			word_temp.clear();
			delete[] wordForCompare;
		}
		else
		{
			word_temp.push_back(path[i]);
		}

		res_g.push_back(path[i]);
	}
	word_temp.clear();
	res_g.push_back('\0');
	size_t size = res_g.size();

	LPTSTR result = (TCHAR*)malloc(size* sizeof(TCHAR*));

	for (size_t i = 0; i < size; i++)
	{		
		result[i] = res_g[i];
	}
	res_g.clear();

	return result;
}



