#pragma once

#include "common.h"

DEFTYPE_STRING(D_LOG_EX, ".Log");
DEFTYPE_STRING(D_LOG_STRING, "LOG");

namespace BF
{
	struct S_CS;
	namespace ELogForm
	{
		enum Enum
		{
			Day,
			Min,
			Sec,
		};
	}
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

		void	AddLog(std::string _str);
		static S_CS m_cs;
	private:

	private:
		CLog(void);

		std::string	m_strPath;
		int			m_nfh;
		bool		bFileOpen;
		ELogForm::Enum eform;
	};
}

#define BF_LOG BF::CLog::getinstance()