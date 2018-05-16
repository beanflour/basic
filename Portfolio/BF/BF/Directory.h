#pragma once

#include "common.h"
#include <vector>
#include <map>
#include <string>

typedef std::vector<std::string>			CONT_STRING;

DEFTYPE_STRING(D_STR_DIVISION, "\\")

/*
	유니코드와 멀티바이트상황에 맞게 작동하지만
	코드가 보기 깔끔하도록 만들기 위함.
*/
#ifdef _UNICODE	
typedef std::wstring STRING;
typedef std::string OSTRING;
#define SPLITPATH _wsplitpath_s
#define FPRINTF fwprintf_s
#else
typedef std::string STRING;
typedef std::wtring OSTRING;
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
			low,	//	상위 디렉토리가 없으면 실패
			deep,	//	상위 디렉토리까지 모로지 생성.
		};
	}


	class CDirectory
	{
		typedef std::map<std::string, std::string>	MAP_STRING;
	public:

		static CDirectory&		getinstance();

		bool			SetSaveDirectory(std::string const _strKey, std::string	const _strDirectory);
		std::string		GetSaveDirectory(std::string const _strKey);

		CONT_STRING		GetDirectoryInfo(std::string const _strPath = "" );
		int				MakeDirectory(std::string _strPath, E_CreateDirectory::Enum const _type = E_CreateDirectory::low);
		bool			AddBackSlash(std::string &_strPath);

		bool			InitMyInfo();
		/*
			현재 문자집합에 맞는 형태로 반환
		*/
		STRING			GetMyFullPath() const;
		STRING			GetMyDrive() const;
		STRING			GetMyDirectory() const;
		STRING			GetMyFullDirectory() const;
		STRING			GetMyName() const;
		STRING			GetMyExt() const;

		/*
			현재 문자집합과 반대되는 형태로 반환.
		*/
		OSTRING			GetMyFullPathOT() const;
		OSTRING			GetMyDriveOT() const;
		OSTRING			GetMyDirectoryOT() const;
		OSTRING			GetMyFullDirectoryOT() const;
		OSTRING			GetMyNameOT() const;
		OSTRING			GetMyExtOT() const;

#ifdef _UNICODE
		std::string		GetMyFullPathA() const;
		std::string		GetMyDriveA() const;
		std::string		GetMyDirectoryA() const;
		std::string		GetMyFullDirectoryA() const;
		std::string		GetMyNameA() const;
		std::string		GetMyExtA() const;
#else
		std::wstring	GetMyFullPathW() const;
		std::wstring	GetMyDriveW() const;
		std::wstring	GetMyDirectoryW() const;
		std::wstring	GetMyFullDirectoryW() const;
		std::wstring	GetMyNameW() const;
		std::wstring	GetMyExtW() const;
#endif

		static S_CS m_cs;
	private:
		CDirectory(void);
		CDirectory(CDirectory const &_Copy);	//	복사 생성자로 사용을 막기위해 정의하지 않았다.
		~CDirectory(void);

		static void Create();
		static void KillMemory();

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
		
		static bool mb_Destory;
		static CDirectory *mp_Ins;
	};
}

#define BF_DIRECTORY	BF::CDirectory::getinstance() 