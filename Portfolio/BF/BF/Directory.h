#pragma once

#include "common.h"

DEFTYPE_STRING(D_STR_LOCAL, "Local")
DEFTYPE_STRING(D_STR_EXE, ".exe")
DEFTYPE_STRING(D_STR_DIVISION, "\\")

namespace BF
{
	struct S_CS;

	namespace E_CreateDirectory
	{
		enum Enum
		{
			low,	//	상위 디렉토리가 없으면 실패
			deep,	//	상위 디렉토리까지 모로지 생성.
		};
	}


	class CDirectory
	{
		typedef std::map<std::string, std::string>	MAP_STRING;
	public:
		~CDirectory(void);

		static CDirectory&		getinstance();
		std::string		GetLocalDirectory();
		std::string		GetFileName();

		void			SetLocalInfo();
		bool			SetSaveDirectory(std::string const _strKey, std::string	const _strDirectory);
		std::string		GetSaveDirectory(std::string const _strKey);

		CONT_STRING		GetDirectoryInfo(std::string const _strPath = "" );
		int			CreateDirectory(std::string _strPath, E_CreateDirectory::Enum const _type = E_CreateDirectory::low);
		bool			AddBackSlash(std::string &_strPath);
		
		static S_CS m_cs;
	private:
		CDirectory(void);

		std::string		m_strLocalDirectory;
		std::string		m_strTempDirectory;
		std::string		m_strFileName;

		MAP_STRING		m_ContDirectory;
	};
}

#define BF_DIRECTORY	BF::CDirectory::getinstance() 