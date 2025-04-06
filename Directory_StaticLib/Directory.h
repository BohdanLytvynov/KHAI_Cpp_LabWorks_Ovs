
#ifndef IDIRECTORY_H

#define IDIRECTORY_H
#include<vector>
namespace filesystem
{
	struct FileDataBase;
	struct FileDataA;
	struct FileDataW;

	struct Path
	{
		/// <summary>
	/// Removes the part of the path after the stop word	
	/// </summary>
	/// <param name="path">Path for mutation</param>
	/// <param name="stopWord">There will be no words after this word!</param>
	/// <param name="delim">Directory separator char</param>
	/// <returns>New Path. Must be released!!!!Use free() method!</returns>
		static LPTSTR Mutate(LPCTSTR path, LPCTSTR stopWord, LPCTSTR delim);
	};

	struct IDirectory
	{
		virtual std::vector<FileDataA> GetFilesA(LPCSTR Abs_path, DWORD& error) = 0;

		virtual std::vector<FileDataW> GetFilesW(LPCTSTR Abs_path, DWORD& error) = 0;
	};

	struct FileDataBase
	{
		FileDataBase(DWORD dwFileAttributes,
			FILETIME ftCreationTime,
			FILETIME ftLastAccessTime,
			FILETIME ftLastWriteTime,
			DWORD nFileSizeHigh,
			DWORD nFileSizeLow,
			DWORD dwReserved0,
			DWORD dwReserved1);
		
		DWORD getFileAttributes() const noexcept;
		FILETIME getCreationTime() const noexcept;
		FILETIME getLastAccessTime() const noexcept;
		FILETIME getLastWriteTime() const noexcept;
		DWORD getFileSizeHigh() const noexcept;
		DWORD getFileSizeLow() const noexcept;
		DWORD getReserved0() const noexcept;
		DWORD getReserved1() const noexcept;

	private:
		DWORD m_dwFileAttributes;
		FILETIME m_ftCreationTime;
		FILETIME m_ftLastAccessTime;
		FILETIME m_ftLastWriteTime;
		DWORD m_nFileSizeHigh;
		DWORD m_nFileSizeLow;
		DWORD m_dwReserved0;
		DWORD m_dwReserved1;
	};

	struct FileDataW : public FileDataBase
	{
		FileDataW(DWORD dwFileAttributes,
			FILETIME ftCreationTime,
			FILETIME ftLastAccessTime,
			FILETIME ftLastWriteTime,
			DWORD nFileSizeHigh,
			DWORD nFileSizeLow,
			DWORD dwReserved0,
			DWORD dwReserved1,
		WCHAR* cFileName,
		WCHAR* cAlternateFileName);
		
		static FileDataW FromWin32FindDataW(WIN32_FIND_DATAW* data);

		const std::wstring& getFileName() const noexcept;
		const std::wstring& getAlternateFileName() const noexcept;
		
	private:		
		std::wstring m_cFileName;
		std::wstring m_cAlternateFileName;
	};

	struct FileDataA : public FileDataBase
	{
		FileDataA(DWORD dwFileAttributes,
			FILETIME ftCreationTime,
			FILETIME ftLastAccessTime,
			FILETIME ftLastWriteTime,
			DWORD nFileSizeHigh,
			DWORD nFileSizeLow,
			DWORD dwReserved0,
			DWORD dwReserved1,
			CHAR* cFileName,
			CHAR* cAlternateFileName);

		static FileDataA FromWin32FindDataA(WIN32_FIND_DATAA* data);

		const std::string& getFileName() const noexcept;
		const std::string& getAlternateFileName() const noexcept;
		
	private:
		std::string m_cFileName;
		std::string m_cAlternateFileName;
	};
	
	struct Directory : public IDirectory
	{
		std::vector<FileDataW> GetFilesW(LPCTSTR Abs_path, DWORD& error) override;

		std::vector<FileDataA> GetFilesA(LPCSTR Abs_path, DWORD& error) override;
	};
}

#endif



