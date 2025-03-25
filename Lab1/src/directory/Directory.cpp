#include "pch.h"
#include "Directory.h"

std::vector<filesystem::FileData> filesystem::Directory::GetFiles(LPCTSTR Abs_path, DWORD& error)
{
	namespace fs = filesystem;

	if (lstrlen(Abs_path) == 0)
		throw std::exception("Parameter path was empty!");
	
	std::vector<filesystem::FileData> res;

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
		
		fs::FileData fd = fs::ToFileData(&ffd);

		res.push_back(fd);

	} while (FindNextFile(hFind, &ffd));

	FindClose(hFind);
	
	return res;
}

filesystem::FileData::FileData(
	DWORD dwFileAttributes, 
	FILETIME ftCreationTime, 
	FILETIME ftLastAccessTime, 
	FILETIME ftLastWriteTime, 
	DWORD nFileSizeHigh, 
	DWORD nFileSizeLow, 
	DWORD dwReserved0, 
	DWORD dwReserved1, 
	TCHAR* cFileName, 
	TCHAR* cAlternateFileName) :
	m_dwFileAttributes(dwFileAttributes),
	m_ftCreationTime(ftCreationTime),
	m_ftLastAccessTime(ftLastAccessTime),
	m_ftLastWriteTime(ftLastWriteTime),
	m_nFileSizeHigh(nFileSizeHigh),
	m_nFileSizeLow(nFileSizeLow),
	m_dwReserved0(dwReserved0),
	m_dwReserved1(dwReserved1)	
{
	m_cFileName = std::wstring(cFileName);

	m_cAlternateFileName = std::wstring(cAlternateFileName);
}

DWORD filesystem::FileData::getFileAttributes() const noexcept
{
	return m_dwFileAttributes;
}

FILETIME filesystem::FileData::getCreationTime() const noexcept
{
	return m_ftCreationTime;;
}

FILETIME filesystem::FileData::getLastAccessTime() const noexcept
{
	return m_ftLastAccessTime;
}

FILETIME filesystem::FileData::getLastWriteTime() const noexcept
{
	return m_ftLastAccessTime;
}

DWORD filesystem::FileData::getFileSizeHigh() const noexcept
{
	return m_nFileSizeHigh;
}

DWORD filesystem::FileData::getFileSizeLow() const noexcept
{
	return m_nFileSizeLow;
}

DWORD filesystem::FileData::getReserved0() const noexcept
{
	return m_dwReserved0;
}

DWORD filesystem::FileData::getReserved1() const noexcept
{
	return m_dwReserved1;
}

const std::wstring& filesystem::FileData::getFileName() const noexcept
{
	return m_cFileName;
}

const std::wstring& filesystem::FileData::getAlternateFileName() const noexcept
{
	return m_cAlternateFileName;
}

filesystem::FileData::FileData(const FileData& other)
{
	m_dwFileAttributes = other.m_dwFileAttributes;
	m_ftCreationTime = other.m_ftCreationTime;
	m_ftLastAccessTime = other.m_ftLastAccessTime;
	m_nFileSizeHigh = other.m_nFileSizeHigh;
	m_nFileSizeLow = other.m_nFileSizeLow;
	m_dwReserved0 = other.m_dwReserved0;
	m_dwReserved1 = other.m_dwReserved1;

	m_cFileName = other.m_cFileName;
	m_cAlternateFileName = other.m_cAlternateFileName;
}

filesystem::FileData& filesystem::FileData::operator=(const FileData& other)
{
	m_dwFileAttributes = other.m_dwFileAttributes;
	m_ftCreationTime = other.m_ftCreationTime;
	m_ftLastAccessTime = other.m_ftLastAccessTime;
	m_nFileSizeHigh = other.m_nFileSizeHigh;
	m_nFileSizeLow = other.m_nFileSizeLow;
	m_dwReserved0 = other.m_dwReserved0;
	m_dwReserved1 = other.m_dwReserved1;

	m_cFileName = other.m_cFileName;
	m_cAlternateFileName = other.m_cAlternateFileName;

	return *this;
}

filesystem::FileData filesystem::ToFileData(WIN32_FIND_DATA* fd)
{
	return FileData(fd->dwFileAttributes, 
		fd->ftCreationTime,
		fd->ftLastAccessTime,
		fd->ftLastWriteTime,
		fd->nFileSizeHigh,
		fd->nFileSizeLow,
		fd->dwReserved0,
		fd->dwReserved1,
		fd->cFileName,
		fd->cAlternateFileName);
}
