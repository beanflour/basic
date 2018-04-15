#pragma once

#include "common.h"

DEFTYPE_STRING(D_LOG_EX, ".Log")
DEFTYPE_STRING(D_LOG_STRING, "LOG")
DEFTYPE_INT(D_MAX_LEN, 1024)

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
		Log�� ���� �����
		Log_��_��_�� ������ �ð�_��_��.Log ���Ϸ� ����ȴ�.
		�������� �ð�:��:�� = log �� ��ϵȴ�.
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