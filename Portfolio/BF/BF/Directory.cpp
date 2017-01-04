#include "stdafx.h"
#include "Directory.h"
#include <io.h>

#include <stdlib.h>
#include <direct.h>
#include <iostream>
#include "AutoLock.h"

#include <bitset>

namespace BF
{
	S_CS CDirectory::m_cs;

	CDirectory&		CDirectory::getinstance()
	{
		CAutoLock lock(m_cs);
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

		m_strFileName = m_strLocalDirectory.substr(m_strLocalDirectory.rfind(D_STR_DIVISION) + 1, m_strLocalDirectory.length());
		m_strFileName = m_strFileName.substr(0, m_strFileName.find(D_STR_EXE));
		m_strLocalDirectory = m_strLocalDirectory.substr(0, m_strLocalDirectory.rfind(D_STR_DIVISION));
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

	CONT_STRING		CDirectory::GetDirectoryInfo(std::string const _strPath /*= ""*/ )
	{
		CONT_STRING ContReturn;
		std::string strPath;
		if(_strPath.empty())
			strPath = this->GetLocalDirectory();
		else
			strPath = _strPath;

		this->AddBackSlash(strPath);

		strPath += "*.*";

		struct _finddatai64_t fd;
		intptr_t handle;

		if((handle = _findfirsti64(strPath.c_str(), &fd)) != -1L)
		{
			do 
			{
				ContReturn.push_back(fd.name);
			} while (_findnext64(handle, &fd) == 0);
		}

		return ContReturn;
	}

	/*
		폴더를 새로 생성할때 사용함.
		_strPath에 만들고자 하는 폴더명까지 포함하여 절대경로를 입력하거나 폴더명만 입력한다.
		폴더명만 입력할 경우 해당 작업 디렉토리에 생성된다.
		E_CreateDirectory::Enum값을 low로 실행하면 경로값이 맞지 않을 때 실패처리하고 deep으로 처리하면 경로값에 해당되는 모든 폴더를 생성한다.
	*/
	int		CDirectory::CreateDirectory(std::string _strPath , E_CreateDirectory::Enum const _type /*= E_CreateDirectory::low*/)
	{
		if(std::string::npos == _strPath.rfind(D_STR_DIVISION))	//	\\가 경로에 없을 경우. 즉 만들 디랙토리명만 입력했을 경우
		{
			_strPath = this->GetLocalDirectory() + D_STR_DIVISION + _strPath;
		}

		std::string strPrevPath = _strPath.substr(0, _strPath.rfind(D_STR_DIVISION));
		if(_access(strPrevPath.c_str(), 0) != 0)	//	해당 디렉토리가 없을 때 
		{
			if(E_CreateDirectory::low == _type)
				return -1;

			this->CreateDirectory(strPrevPath, E_CreateDirectory::deep);
		}

		return _mkdir(_strPath.c_str());
	}

	bool	CDirectory::AddBackSlash(std::string &_strPath) //	전달받은 path의 끝이 \\로 끝나지 않을 경우 \\를 추가해줌
	{
		if('\\' != _strPath[_strPath.length() - 1])
		{
			_strPath += '\\';
			return true;
		}

		return false;
	}
}