#pragma once

#include "common.h"

DEFTYPE_STRING(D_STR_DIVISION, "\\")

/*
	�����ڵ�� ��Ƽ����Ʈ��Ȳ�� �°� �۵�������
	�ڵ尡 ���� ����ϵ��� ����� ����.
*/
#ifdef _UNICODE	
typedef std::wstring STRING;
#define SPLITPATH _wsplitpath_s
#define FPRINTF fwprintf_s
#else
typedef std::string STRING;
#define SPLITPATH _splitpath_s
#define FPRINTF fprintf_s
#endif

namespace BF
{
	struct S_CS;

	namespace E_CreateDirectory
	{
		enum Enum
		{
			low,	//	���� ���丮�� ������ ����
			deep,	//	���� ���丮���� ����� ����.
		};
	}


	class CDirectory
	{
		typedef std::map<std::string, std::string>	MAP_STRING;
	public:
		~CDirectory(void);

		static CDirectory&		getinstance();

		bool			SetSaveDirectory(std::string const _strKey, std::string	const _strDirectory);
		std::string		GetSaveDirectory(std::string const _strKey);

		CONT_STRING		GetDirectoryInfo(std::string const _strPath = "" );
		int				CreateDirectory(std::string _strPath, E_CreateDirectory::Enum const _type = E_CreateDirectory::low);
		bool			AddBackSlash(std::string &_strPath);

		STRING	GetMyFullPath() const;
		std::string	GetMyFullPathA() const;
		std::wstring GetMyFullPathW() const;

		STRING	GetMyDrive() const;
		std::string	GetMyDriveA() const;
		std::wstring GetMyDriveW() const;

		STRING	GetMyDirectory() const;
		std::string	GetMyDirectoryA() const;
		std::wstring GetMyDirectoryW() const;

		STRING	GetMyFullDirectory() const;
		std::string	GetMyFullDirectoryA() const;
		std::wstring GetMyFullDirectoryW() const;

		STRING	GetMyName() const;
		std::string	GetMyNameA() const;
		std::wstring GetMyNameW() const;

		STRING	GetMyExt() const;
		std::string	GetMyExtA() const;
		std::wstring GetMyExtW() const;

		bool			InitMyInfo();
		
		static S_CS m_cs;
	private:
		CDirectory(void);

		std::string		mstr_LocalDirectory;
		std::string		mstr_TempDirectory;
		std::string		mstr_FileName;

		STRING	mstr_MyFullPath;
		STRING	mstr_MyDrive;
		STRING	mstr_MyDirectory;
		STRING  mstr_MyFullDirectory;
		STRING	mstr_MyName;
		STRING	mstr_MyExt;		


		MAP_STRING		mCont_Directory;
	};
}

#define BF_DIRECTORY	BF::CDirectory::getinstance() 