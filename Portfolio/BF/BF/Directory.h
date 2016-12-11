#pragma once

#include "common.h"

DEFTYPE_STRING(STR_LOCAL, "Local")
DEFTYPE_STRING(STR_EXE, ".exe")
DEFTYPE_STRING(STR_DIVISION, "\\")

namespace BF
{

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
	private:
		CDirectory(void);

		std::string		m_strLocalDirectory;
		std::string		m_strTempDirectory;
		std::string		m_strFileName;

		MAP_STRING		m_ContDirectory;
		
	};
}

#define BF_DIRECTORY	BF::CDirectory::getinstance() 