#include "stdafx.h"
#include <WinSock2.h>
#include "Log.h"
#include "AutoLock.h"
#include "Directory.h"
#include <time.h>
#include "formatstdstring.h"
//#include "FileMgr.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>
#include <locale.h>
#include <AtlConv.h>
#include <stdio.h>


#pragma warning(disable:4996)

namespace BF
{
	S_CS CLog::m_cs;

	CLog::CLog(void)
		:	m_nfh(0)
		,	bFileOpen(false)
	{
		CAutoLock lock(m_cs);
#ifdef UNICODE
		_wsetlocale(LC_ALL, L"korean");
#endif
		std::string strDirectoryPath, strDay, strSec;

		time_t tTemp;
		struct tm *ptime;
		time(&tTemp);
		ptime	= localtime(&tTemp);
		
		strDay = format("Log_%d_%02d_%02d", ptime->tm_year + 1900
			,	ptime->tm_mon + 1
			,	ptime->tm_mday
			);

		BF_DIRECTORY.InitMyInfo();

		std::string strTemp = BF_DIRECTORY.GetMyFullDirectoryOT().c_str();
		strDirectoryPath = strTemp + D_LOG_STRING + D_STR_DIVISION + strDay;
			
		if(-1 == _access(D_LOG_STRING, 0))				//	LOG ������ ���� ��� ���� ����
			BF_DIRECTORY.MakeDirectory(D_LOG_STRING);
		if(-1 == _access(strDirectoryPath.c_str(), 0))	//	������ ���� ��� ���� ���� �������� Log_��_��_��
			BF_DIRECTORY.MakeDirectory(strDirectoryPath.c_str());

		strSec = format("%s_%02d_%02d_%02d", BF_DIRECTORY.GetMyNameOT().c_str()
			,	ptime->tm_hour
			,	ptime->tm_min
			,	ptime->tm_sec
			);
		m_strPath = strDirectoryPath + D_STR_DIVISION + strSec + D_LOG_EX;
#ifdef UNICODE
		switch(_sopen_s(&m_nfh, m_strPath.c_str(), _O_CREAT | _O_APPEND | _O_WRONLY | _O_U16TEXT, SH_DENYNO, _S_IWRITE))
#else
		switch(_sopen_s(&m_nfh, m_strPath.c_str(), _O_CREAT | _O_APPEND | _O_WRONLY, SH_DENYNO, _S_IWRITE))
#endif
		{
		case EACCES:
			{
				std::cout << "������ ��ΰ� ���͸��ų� ������ �б� �����ε� ���� ���� ���� �۾��� �õ��߽��ϴ�.\n";
			}break;
		case EEXIST:
			{
				std::cout << "_O_CREAT �� _O_EXCL �÷��׸� ���������� filename�� �̹� �ֽ��ϴ�.\n";
			}break;
		case EINVAL:
			{
				std::cout << "oflag, shflag �Ǵ� pmode �μ��� �߸��Ǿ��ų� pfh �Ǵ� filename�� null �������Դϴ�.\n";
			}break;
		case EMFILE:
			{
				std::cout << "��� ������ �߰� ���� �����ڰ� �����ϴ�.\n";
			}break;
		case ENOENT:
			{
				std::cout << "���� �Ǵ� ��θ� ã�� �� �����ϴ�.\n";
			}break;
		}

		if(-1 != m_nfh)
			bFileOpen = true;
	}


	CLog::~CLog(void)
	{
		if(bFileOpen)
			_close(m_nfh);
	}

	CLog& CLog::getinstance()
	{
		CAutoLock lock(m_cs);
		static CLog temp;

		return temp;
	}

	void	CLog::AddLog(char *_fmt, ...)
	{
		char str[D_MAX_LEN] = { '\0' };
		va_list ap;
		va_start(ap, _fmt);
		vsprintf(str, _fmt, ap);
		va_end(ap);
		std::string strData(str);
		AddLog(strData);
	}

	void	CLog::AddLog(std::string _str)
	{
		if(false == bFileOpen)
			return ;
		
		time_t tTemp;
		struct tm *ptime;
		time(&tTemp);
		ptime	= localtime(&tTemp);

		std::string strData = format("%02d:%02d:%02d = ", ptime->tm_hour, ptime->tm_min, ptime->tm_sec);	//	�α׿� �ð�:��:�� : �α� ������ ���
		strData += _str + "\n";
#ifdef UNICODE
		USES_CONVERSION;
		std::wstring wstrTemp(A2W(strData.c_str()));
		//wstrTemp.assign(strData.begin(), strData.end());

		{
			CAutoLock lock(m_cs);
			_write(m_nfh, wstrTemp.c_str(), sizeof(wchar_t) * wcslen(wstrTemp.c_str()));
#else
			_write(m_nfh, strData.c_str(), strlen(strData.c_str()));
#endif
		}
	}
	void	CLog::AddLog(std::wstring _wstr)
	{
		if (false == bFileOpen)
			return;

		time_t tTemp;
		struct tm *ptime;
		time(&tTemp);
		ptime = localtime(&tTemp);
		std::wstring wstrData = format(L"%02d:%02d:%02d = ", ptime->tm_hour, ptime->tm_min, ptime->tm_sec);
		wstrData += _wstr + L"\n";
		{
			CAutoLock lock(m_cs);
#ifdef UNICODE
			_write(m_nfh, wstrData.c_str(), sizeof(wchar_t) * wcslen(wstrData.c_str()));
#else
			USES_CONVERSION;
			std::string strData(W2A(wstrData.c_str()));
			//strData.assign(wstrData.begin(), wstrData.end());
			_write(m_nfh, strData.c_str(), strlen(strData.c_str()));
#endif
		}
	}

	void	CLog::AddSockError(char *_str /* = nullptr*/)
	{
		LPWSTR lpOSMsg = nullptr;
		DWORD nError = WSAGetLastError();
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr,
			nError,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpOSMsg, 0, nullptr);

		this->AddLog(lpOSMsg);
		this->AddLog("WSAGetLastError : %d", nError);
		if(_str)
			this->AddLog(_str);
	}
}