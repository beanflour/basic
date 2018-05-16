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
		Log�� ���� �����
		Log_��_��_�� ������ �ð�_��_��.Log ���Ϸ� ����ȴ�.
		�������� �ð�:��:�� = log �� ��ϵȴ�.
	*/
	class CLog
	{
	public:
		static CLog& getinstance();

		void	AddLog(char *_fmt, ...);
		void	AddLog(wchar_t *_fmt, ...);
		void	AddLog(std::string _str);
		void	AddLog(std::wstring _wstr);
		void	AddSockError(char *str = nullptr);
		static S_CS m_cs;

		/*
			try catch(char *)�� SIGSEGV����(�޸� ���ٿ���)�� ó���ϱ� ���� �Լ�.
			getinstance()�� �� �����Ƿ� BF_LOG�� �ѹ��̶� ȣ��ȵڿ� �Ͼ SIGSEGV������ catch(char*)���� ���� �� �ִ�.
		*/
		void	SetTrySIGSEGV();
	private:
		static void Create();
		static void KillMemory();
	private:
		CLog(void);
		CLog(CLog const &_Copy);	//	���� �����ڷ� ������ ���� ���� ���Ǹ� ���� �ʾҴ�.
		~CLog(void);

		std::string	m_strPath;
		int			m_nfh;
		bool		bFileOpen;

		static bool mb_Destroy;
		static CLog *mp_Ins;
	};
}

#define BF_LOG BF::CLog::getinstance()