#pragma once

#include <wtypes.h>

namespace BF
{
	class FileIO
	{
	public:
		FileIO();
		~FileIO();

		static DOUBLE GetDoubleINI(	_In_opt_ LPCWSTR lpAppName,
									_In_opt_ LPCWSTR lpKeyName,
									_In_opt_ DOUBLE dDefault,
									_In_opt_ LPCWSTR lpFileName);
		static FLOAT GetFloatINI(_In_opt_ LPCWSTR lpAppName,
			_In_opt_ LPCWSTR lpKeyName,
			_In_opt_ DOUBLE dDefault,
			_In_opt_ LPCWSTR lpFileName);
	};
}
