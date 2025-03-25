
#ifndef IDIRECTORY_H

#define IDIRECTORY_H
#include<vector>
namespace filesystem
{
	struct FileData;

	struct IDirectory
	{
		virtual std::vector<FileData> GetFiles(LPCTSTR Abs_path, DWORD& error) = 0;
	};

	struct FileData
	{
		FileData(DWORD dwFileAttributes,
		FILETIME ftCreationTime,
		FILETIME ftLastAccessTime,
		FILETIME ftLastWriteTime,
		DWORD nFileSizeHigh,
		DWORD nFileSizeLow,
		DWORD dwReserved0,
		DWORD dwReserved1,
		TCHAR* cFileName,
		TCHAR* cAlternateFileName);

		DWORD getFileAttributes() const noexcept;
		FILETIME getCreationTime() const noexcept;
		FILETIME getLastAccessTime() const noexcept;
		FILETIME getLastWriteTime() const noexcept;
		DWORD getFileSizeHigh() const noexcept;
		DWORD getFileSizeLow() const noexcept;
		DWORD getReserved0() const noexcept;
		DWORD getReserved1() const noexcept;
		const std::wstring& getFileName() const noexcept;
		const std::wstring& getAlternateFileName() const noexcept;

		FileData(const FileData& other);

		FileData& operator = (const FileData& other);	

	private:
		DWORD m_dwFileAttributes;
		FILETIME m_ftCreationTime;
		FILETIME m_ftLastAccessTime;
		FILETIME m_ftLastWriteTime;
		DWORD m_nFileSizeHigh;
		DWORD m_nFileSizeLow;
		DWORD m_dwReserved0;
		DWORD m_dwReserved1;
		std::wstring m_cFileName;
		std::wstring m_cAlternateFileName;
	};

	FileData ToFileData(WIN32_FIND_DATA* fde);

	struct Directory : public IDirectory
	{
		std::vector<FileData> GetFiles(LPCTSTR Abs_path, DWORD& error) override;
	};
}

#endif



