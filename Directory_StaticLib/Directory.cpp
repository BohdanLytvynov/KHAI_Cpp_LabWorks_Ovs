#include "pch.h"
#include "Directory.h"

std::vector<filesystem::FileDataW> filesystem::Directory::GetFilesW(LPCTSTR Abs_path, DWORD& error)
{
	namespace fs = filesystem;

	if (lstrlen(Abs_path) == 0)
		throw std::exception("Parameter path was empty!");

	std::vector<filesystem::FileDataW> res;

	HANDLE hFind = INVALID_HANDLE_VALUE;
	
	WIN32_FIND_DATAW ffd;

	TCHAR szDir[MAX_PATH];
	error = 0;

	StringCchCopy(szDir, MAX_PATH, Abs_path);
	StringCchCat(szDir, MAX_PATH, TEXT("\\*"));

	hFind = FindFirstFileW(szDir, &ffd);
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
		
		res.push_back(fs::FileDataW::FromWin32FindDataW(&ffd));

	} while (FindNextFileW(hFind, &ffd));

	FindClose(hFind);

	return res;
}

std::vector<filesystem::FileDataA> filesystem::Directory::GetFilesA(LPCSTR Abs_path, DWORD& error)
{
	namespace fs = filesystem;

	if (strlen(Abs_path) == 0)
		throw std::exception("Parameter path was empty!");

	std::vector<filesystem::FileDataA> res;

	HANDLE hFind = INVALID_HANDLE_VALUE;

	WIN32_FIND_DATAA ffd;

	CHAR szDir[MAX_PATH];
	error = 0;

	StringCchCopyA(szDir, MAX_PATH, Abs_path);
	StringCchCatA(szDir, MAX_PATH, "\\*");

	hFind = FindFirstFileA(szDir, &ffd);
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

		res.push_back(fs::FileDataA::FromWin32FindDataA(&ffd));

	} while (FindNextFileA(hFind, &ffd));

	FindClose(hFind);

	return res;
}

filesystem::FileDataBase::FileDataBase(
	DWORD dwFileAttributes,
	FILETIME ftCreationTime,
	FILETIME ftLastAccessTime,
	FILETIME ftLastWriteTime,
	DWORD nFileSizeHigh,
	DWORD nFileSizeLow,
	DWORD dwReserved0,
	DWORD dwReserved1) :
	m_dwFileAttributes(dwFileAttributes),
	m_ftCreationTime(ftCreationTime),
	m_ftLastAccessTime(ftLastAccessTime),
	m_ftLastWriteTime(ftLastWriteTime),
	m_nFileSizeHigh(nFileSizeHigh),
	m_nFileSizeLow(nFileSizeLow),
	m_dwReserved0(dwReserved0),
	m_dwReserved1(dwReserved1)
{}

DWORD filesystem::FileDataBase::getFileAttributes() const noexcept
{
	return m_dwFileAttributes;
}

FILETIME filesystem::FileDataBase::getCreationTime() const noexcept
{
	return m_ftCreationTime;;
}

FILETIME filesystem::FileDataBase::getLastAccessTime() const noexcept
{
	return m_ftLastAccessTime;
}

FILETIME filesystem::FileDataBase::getLastWriteTime() const noexcept
{
	return m_ftLastAccessTime;
}

DWORD filesystem::FileDataBase::getFileSizeHigh() const noexcept
{
	return m_nFileSizeHigh;
}

DWORD filesystem::FileDataBase::getFileSizeLow() const noexcept
{
	return m_nFileSizeLow;
}

DWORD filesystem::FileDataBase::getReserved0() const noexcept
{
	return m_dwReserved0;
}

DWORD filesystem::FileDataBase::getReserved1() const noexcept
{
	return m_dwReserved1;
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

filesystem::FileDataW::FileDataW(DWORD dwFileAttributes, 
	FILETIME ftCreationTime,
	FILETIME ftLastAccessTime,
	FILETIME ftLastWriteTime, 
	DWORD nFileSizeHigh, 
	DWORD nFileSizeLow, 
	DWORD dwReserved0, 
	DWORD dwReserved1, 
	WCHAR* cFileName, 
	WCHAR* cAlternateFileName) : FileDataBase(dwFileAttributes, ftCreationTime,
		ftLastAccessTime, ftLastWriteTime, nFileSizeHigh, nFileSizeLow, dwReserved0, dwReserved1)
{
	m_cFileName = std::wstring(cFileName);

	m_cAlternateFileName = std::wstring(cAlternateFileName);
}

filesystem::FileDataW filesystem::FileDataW::FromWin32FindDataW(WIN32_FIND_DATAW* data)
{		
	return FileDataW(data->dwFileAttributes, data->ftCreationTime, data->ftLastAccessTime, data->ftLastWriteTime, data->nFileSizeHigh, data->nFileSizeLow, data->dwReserved0,
		data->dwReserved1, data->cFileName, data->cAlternateFileName);
}

const std::wstring& filesystem::FileDataW::getFileName() const noexcept
{
	return m_cFileName;
}

const std::wstring& filesystem::FileDataW::getAlternateFileName() const noexcept
{
	return m_cFileName;
}

filesystem::FileDataA::FileDataA(DWORD dwFileAttributes, 
	FILETIME ftCreationTime, 
	FILETIME ftLastAccessTime, 
	FILETIME ftLastWriteTime, 
	DWORD nFileSizeHigh, 
	DWORD nFileSizeLow, 
	DWORD dwReserved0, 
	DWORD dwReserved1, 
	CHAR* cFileName, 
	CHAR* cAlternateFileName) : FileDataBase(dwFileAttributes, ftCreationTime,
		ftLastAccessTime, ftLastWriteTime, nFileSizeHigh, nFileSizeLow, dwReserved0, dwReserved1)
{
	m_cFileName = std::string(cFileName);
	m_cAlternateFileName = std::string(cAlternateFileName);
}

filesystem::FileDataA filesystem::FileDataA::FromWin32FindDataA(WIN32_FIND_DATAA* data)
{
	return FileDataA(data->dwFileAttributes, data->ftCreationTime, data->ftLastAccessTime, data->ftLastWriteTime, data->nFileSizeHigh, data->nFileSizeLow, data->dwReserved0,
		data->dwReserved1, data->cFileName, data->cAlternateFileName);
}

const std::string& filesystem::FileDataA::getFileName() const noexcept
{
	return m_cFileName;
}

const std::string& filesystem::FileDataA::getAlternateFileName() const noexcept
{
	return m_cAlternateFileName;
}
