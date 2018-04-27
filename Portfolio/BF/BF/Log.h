#pragma once

#include "common.h"
#include <string>

DEFTYPE_STRING(D_LOG_EX, ".Log")
DEFTYPE_STRING(D_LOG_STRING, "LOG")
DEFTYPE_INT(D_MAX_LEN, 1024)

namespace BF
{
	struct S_CS;
	/*
		Log의 저장 방식은
		Log_년_월_일 폴더에 시간_분_초.Log 파일로 저장된다.
		저장방식은 시간:분:초 = log 로 기록된다.
	*/
	class CLog
	{
	public:
		
		~CLog(void);

		static CLog& getinstance();

		void	AddLog(char *_fmt, ...);
		//void	AddLog(WCHAR *_fmt, ...);
		void	AddLog(std::string _str);
		void	AddLog(std::wstring _wstr);
		void	AddSockError(char *str = nullptr);
		static S_CS m_cs;

		/*
			try catch(char *)로 SIGSEGV에러(메모리 접근에러)를 처리하기 위한 함수.
			getinstance()에 들어가 있으므로 BF_LOG가 한번이라도 호출된뒤에 일어난 SIGSEGV에러를 catch(char*)에서 받을 수 있다.
		*/
		void	SetTrySIGSEGV();
	private:

	private:
		CLog(void);

		std::string	m_strPath;
		int			m_nfh;
		bool		bFileOpen;
	};
}

#define BF_LOG BF::CLog::getinstance()