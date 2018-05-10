#include "stdafx.h"
#include "FileIO.h"
#include "Directory.h"
#include <string>

namespace BF
{
	FileIO::FileIO()
	{
	}
	FileIO::~FileIO()
	{
	}

	DOUBLE FileIO::GetDoubleINI(LPCWSTR lpAppName, LPCWSTR lpKeyName, DOUBLE dDefault, LPCWSTR lpFileName)
	{
		TCHAR buf[1024] = {};

		DWORD nSize = GetPrivateProfileString(lpAppName,lpKeyName, L"", buf, 1024, lpFileName);
		if(0 == nSize)
			return 0.0;

		STRING str = buf;
		size_t szstr = str.size();

		DOUBLE dR = std::stod(str, &szstr);		
		return dR;
	}
	FLOAT FileIO::GetFloatINI(LPCWSTR lpAppName, LPCWSTR lpKeyName, DOUBLE dDefault, LPCWSTR lpFileName)
	{
		TCHAR buf[1024] = {};

		DWORD nSize = GetPrivateProfileString(lpAppName, lpKeyName, L"", buf, 1024, lpFileName);
		if (0 == nSize)
			return 0.0;

		STRING str = buf;
		size_t szstr = str.size();

		FLOAT fR = std::stof(str, &szstr);
		return fR;
	}
}