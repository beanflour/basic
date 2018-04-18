#include "stdafx.h"
#include "Directory.h"
#include <io.h>

#include <stdlib.h>
#include <direct.h>
#include <iostream>
#include "AutoLock.h"

#include <bitset>
#include <tchar.h>


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

	bool	CDirectory::SetSaveDirectory(std::string const _strKey, std::string	const _strDirectory)
	{
		if(mCont_Directory.insert(MAP_STRING::value_type(_strKey, _strDirectory)).second)
			return true;
		else
			return false;
	}

	std::string		CDirectory::GetSaveDirectory(std::string const _strKey)
	{
		std::string	tempStr;
		MAP_STRING::iterator	Iter = 	mCont_Directory.find(_strKey);
		if( mCont_Directory.end() != Iter)
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
			strPath = this->GetMyFullDirectoryOT().c_str();
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
	int		CDirectory::MakeDirectory(std::string _strPath , E_CreateDirectory::Enum const _type /*= E_CreateDirectory::low*/)
	{
		if(std::string::npos == _strPath.rfind(D_STR_DIVISION))	//	\\가 경로에 없을 경우. 즉 만들 디랙토리명만 입력했을 경우
		{
			std::string strTemp = this->GetMyFullDirectoryOT().c_str();
			_strPath = strTemp + _strPath;
		}

		std::string strPrevPath = _strPath.substr(0, _strPath.rfind(D_STR_DIVISION));
		if(_access(strPrevPath.c_str(), 0) != 0)	//	해당 디렉토리가 없을 때 
		{
			if(E_CreateDirectory::low == _type)
				return -1;

			this->MakeDirectory(strPrevPath, E_CreateDirectory::deep);
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

	STRING	CDirectory::GetMyFullPath() const
	{
		return mstr_MyFullPath;
	}
	STRING	CDirectory::GetMyDrive() const
	{
		return mstr_MyDrive;
	}
	STRING	CDirectory::GetMyDirectory() const
	{
		return mstr_MyDirectory;
	}
	STRING	CDirectory::GetMyFullDirectory() const
	{
		return mstr_MyFullDirectory;
	}
	STRING	CDirectory::GetMyName() const
	{
		return mstr_MyName;
	}
	STRING	CDirectory::GetMyExt() const
	{
		return mstr_MyExt;
	}

	OSTRING CDirectory::GetMyFullPathOT() const
	{
		OSTRING str;
		if(!mstr_MyFullPath.empty())
		{
			str.assign(mstr_MyFullPath.begin(), mstr_MyFullPath.end());
		}
		return str;
	}
	OSTRING	CDirectory::GetMyDriveOT() const
	{
		OSTRING str;
		if (!mstr_MyDrive.empty())
		{
			str.assign(mstr_MyDrive.begin(), mstr_MyDrive.end());
		}
		return str;
	}
	OSTRING	CDirectory::GetMyDirectoryOT() const
	{
		OSTRING str;
		if (!mstr_MyDirectory.empty())
		{
			str.assign(mstr_MyDirectory.begin(), mstr_MyDirectory.end());
		}
		return str;
	}
	OSTRING	CDirectory::GetMyFullDirectoryOT() const
	{
		OSTRING str;
		if (!mstr_MyFullDirectory.empty())
		{
			str.assign(mstr_MyFullDirectory.begin(), mstr_MyFullDirectory.end());
		}
		return str;
	}
	OSTRING	CDirectory::GetMyNameOT() const
	{
		OSTRING str;
		if (!mstr_MyName.empty())
		{
			str.assign(mstr_MyName.begin(), mstr_MyName.end());
		}
		return str;
	}
	OSTRING	CDirectory::GetMyExtOT() const
	{
		OSTRING str;
		if (!mstr_MyExt.empty())
		{
			str.assign(mstr_MyExt.begin(), mstr_MyExt.end());
		}
		return str;
	}
#ifdef _UNICODE
	std::string	CDirectory::GetMyFullPathA() const
	{
		std::string wstr = "";
		// 값이 없을때 그냥 리턴
		if (!mstr_MyFullPath.empty())
		{
			wstr.assign(mstr_MyFullPath.begin(), mstr_MyFullPath.end());
		}
		return wstr;
	}
	std::string	CDirectory::GetMyDriveA() const
	{
		std::string wstr = "";
		// 값이 없을때 그냥 리턴
		if (!mstr_MyDrive.empty())
		{
			wstr.assign(mstr_MyDrive.begin(), mstr_MyDrive.end());
		}
		return wstr;
	}
	std::string	CDirectory::GetMyDirectoryA() const
	{
		std::string wstr = "";
		// 값이 없을때 그냥 리턴
		if (!mstr_MyDirectory.empty())
		{
			wstr.assign(mstr_MyDirectory.begin(), mstr_MyDirectory.end());
		}
		return wstr;
	}
	std::string	CDirectory::GetMyFullDirectoryA() const
	{
		std::string wstr = "";
		// 값이 없을때 그냥 리턴
		if (!mstr_MyFullDirectory.empty())
		{
			wstr.assign(mstr_MyFullDirectory.begin(), mstr_MyFullDirectory.end());
		}
		return wstr;
	}
	std::string	CDirectory::GetMyNameA() const
	{
		std::string wstr = "";
		// 값이 없을때 그냥 리턴
		if (!mstr_MyName.empty())
		{
			wstr.assign(mstr_MyName.begin(), mstr_MyName.end());
		}
		return wstr;
	}
	std::string	CDirectory::GetMyExtA() const
	{
		std::string wstr = "";
		// 값이 없을때 그냥 리턴
		if (!mstr_MyExt.empty())
		{
			wstr.assign(mstr_MyExt.begin(), mstr_MyExt.end());
		}
		return wstr;
	}
#else
	std::wstring CDirectory::GetMyFullPathW() const
	{
		std::wstring wstr = L"";
		// 값이 없을때 그냥 리턴
		if (!mstr_MyFullPath.empty())
		{
			wstr.assign(mstr_MyFullPath.begin(), mstr_MyFullPath.end());
		}
		return wstr;
	}
	std::wstring CDirectory::GetMyDriveW() const
	{
		std::wstring wstr = L"";
		// 값이 없을때 그냥 리턴
		if (!mstr_MyDrive.empty())
		{
			wstr.assign(mstr_MyDrive.begin(), mstr_MyDrive.end());
		}
		return wstr;
	}
	std::wstring CDirectory::GetMyDirectoryW() const
	{
		std::wstring wstr = L"";
		// 값이 없을때 그냥 리턴
		if (!mstr_MyDirectory.empty())
		{
			wstr.assign(mstr_MyDirectory.begin(), mstr_MyDirectory.end());
		}
		return wstr;
	}
	std::wstring CDirectory::GetMyFullDirectoryW() const
	{
		std::wstring wstr = L"";
		// 값이 없을때 그냥 리턴
		if (!mstr_MyFullDirectory.empty())
		{
			wstr.assign(mstr_MyFullDirectory.begin(), mstr_MyFullDirectory.end());
		}
		return wstr;
	}

	std::wstring CDirectory::GetMyNameW() const
	{
		std::wstring wstr = L"";
		// 값이 없을때 그냥 리턴
		if (!mstr_MyName.empty())
		{
			wstr.assign(mstr_MyName.begin(), mstr_MyName.end());
		}
		return wstr;
	}
	std::wstring CDirectory::GetMyExtW() const
	{
		std::wstring wstr = L"";
		// 값이 없을때 그냥 리턴
		if (!mstr_MyExt.empty())
		{
			wstr.assign(mstr_MyExt.begin(), mstr_MyExt.end());
		}
		return wstr;
	}
#endif

	bool CDirectory::InitMyInfo()
	{
		if(!mstr_MyFullPath.empty())	//	이게 비어있지 않다면 이미 해당정보를 갖고 있으므로 다시 실행할 필요 없음.
			return true;

		mstr_MyFullPath.resize(_MAX_PATH);
		mstr_MyDrive.resize(_MAX_DRIVE);
		mstr_MyDirectory.resize(_MAX_DIR);
		mstr_MyName.resize(_MAX_FNAME);
		mstr_MyExt.resize(_MAX_EXT);

		GetModuleFileName(NULL, &mstr_MyFullPath[0], 260);
		switch(SPLITPATH(mstr_MyFullPath.c_str(), &mstr_MyDrive[0], _MAX_DRIVE, &mstr_MyDirectory[0], _MAX_DIR, &mstr_MyName[0], _MAX_FNAME, &mstr_MyExt[0], _MAX_EXT))
		{
			case EINVAL:
			{
				FPRINTF(stderr, _T("에러\n"));
				return false;
			}break;
			case ERANGE:
			{
				FPRINTF(stderr, _T("버퍼 오버플로우\n"));
				return false;
			}break;
			default:
			{
			}
		}
		STRING str = mstr_MyDrive.c_str();
		mstr_MyFullDirectory = str + mstr_MyDirectory.c_str();
		return true;
	}
}