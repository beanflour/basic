#include "stdafx.h"
#include "Directory.h"

#include <stdlib.h>

#include <iostream>
#include "AutoLock.h"

namespace BF
{
	CDirectory&		CDirectory::getinstance()
	{
		CAutoLock lock;
		static CDirectory temp;
		return temp;
	}

	CDirectory::CDirectory(void)
	{
	}


	CDirectory::~CDirectory(void)
	{
	}

	std::string	CDirectory::GetLocalDirectory()
	{
		if(m_strLocalDirectory.empty())
			this->SetLocalInfo();
		
		return m_strLocalDirectory;
	}

	std::string CDirectory::GetFileName()
	{
		if(m_strFileName.empty())
			this->SetLocalInfo();
		return m_strFileName;
	}

	void		CDirectory::SetLocalInfo()
	{
		char	sTempBuf[_MAX_PATH] = {NULL,};
		::GetModuleFileName(NULL, sTempBuf, _MAX_PATH);
		m_strLocalDirectory = sTempBuf;

		m_strFileName = m_strLocalDirectory.substr(m_strLocalDirectory.rfind(STR_DIVISION) + 1, m_strLocalDirectory.length());
		m_strFileName = m_strFileName.substr(0, m_strFileName.find(STR_EXE));
		m_strLocalDirectory = m_strLocalDirectory.substr(0, m_strLocalDirectory.rfind(STR_DIVISION));
	}

	bool	CDirectory::SetSaveDirectory(std::string const _strKey, std::string	const _strDirectory)
	{
		if(m_ContDirectory.insert(MAP_STRING::value_type(_strKey, _strDirectory)).second)
			return true;
		else
			return false;
	}

	std::string		CDirectory::GetSaveDirectory(std::string const _strKey)
	{
		std::string	tempStr;
		MAP_STRING::iterator	Iter = 	m_ContDirectory.find(_strKey);
		if( m_ContDirectory.end() != Iter)
		{
			tempStr = Iter->second;
		}
		return tempStr;
	}
}