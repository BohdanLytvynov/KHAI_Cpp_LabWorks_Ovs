
#ifndef IDIRECTORY_H

#define IDIRECTORY_H
#include<vector>
namespace filesystem
{	
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

		const long int * const p;

		long const int const* p1;

		
	};

	struct IDirectory
	{
		virtual std::vector<WIN32_FIND_DATA> GetFiles(LPCTSTR Abs_path, DWORD& error) = 0;
	};
	
	struct Directory : public IDirectory
	{
		std::vector<WIN32_FIND_DATA> GetFiles(LPCTSTR Abs_path, DWORD& error) override;
	};
}

#endif



