#include "stdafx.h"
#include "Log.h"
#include "AutoLock.h"
#include "Directory.h"
#include <time.h>
#include "formatstdstring.h"
#include "FileMgr.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>


#pragma warning(disable:4996)

namespace BF
{
	S_CS CLog::m_cs;
	CLog::CLog(void)
		:	m_nfh(0)
		,	bFileOpen(false)
		,	eform(ELogForm::Sec)
	{
		std::string strDirectoryPath, strDay, strSec;

		time_t tTemp;
		struct tm *ptime;
		time(&tTemp);
		ptime	= localtime(&tTemp);
		
		strDay = format("Log_%d_%d_%d", ptime->tm_year + 1900
			,	ptime->tm_mon + 1
			,	ptime->tm_mday
			);

		strDirectoryPath = BF_DIRECTORY.GetLocalDirectory() + D_STR_DIVISION + D_LOG_STRING + D_STR_DIVISION + strDay;
			
		if(-1 == _access(D_LOG_STRING, 0))				//	LOG ������ ���� ��� ���� ����
			BF_DIRECTORY.CreateDirectory(D_LOG_STRING);
		if(-1 == _access(strDirectoryPath.c_str(), 0))	//	������ ���� ��� ���� ���� �������� Log_��_��_��
			BF_DIRECTORY.CreateDirectory(strDirectoryPath.c_str());

		strSec = format("%d_%d_%d", ptime->tm_hour
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
		std::wstring wstrTemp;
		wstrTemp.assign(strData.begin(), strData.end());
		_write(m_nfh, wstrTemp.c_str(), sizeof(wchar_t) * wcslen(wstrTemp.c_str()));
#else
		_write(m_nfh, strData.c_str(), strlen(strData.c_str()));

#endif
	}
	void	CLog::AddLog(std::wstring _wstr)
	{
		if(false == bFileOpen)
			return ;

		time_t tTemp;
		struct tm *ptime;
		time(&tTemp);
		ptime	= localtime(&tTemp);
		std::wstring wstrData = format(L"%02d:%02d:%02d = ", ptime->tm_hour, ptime->tm_min, ptime->tm_sec);
		wstrData += _wstr + L"\n";
#ifdef UNICODE
		_write(m_nfh, wstrData.c_str(), sizeof(wchar_t) * wcslen(wstrData.c_str()));
#else
		std::string strData;
		strData.assign(wstrData.begin(), wstrData.end());
		_write(m_nfh, strData.c_str(), strlen(strData.c_str()));
#endif
	}
}