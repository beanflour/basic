#pragma once

#include <afx.h>
#include <afxwin.h>
#include <string>

#if !defined(AFX_STDAFX_H__CF9684CB_A67E_41E5_8126_BDDCF06516DF__INCLUDED_)
#define AFX_STDAFX_H__CF9684CB_A67E_41E5_8126_BDDCF06516DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF", "adoEOF")

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__CF9684CB_A67E_41E5_8126_BDDCF06516DF__INCLUDED_)

#if !defined(AFX_MYADODB_H__9FE345EF_CFCE_4C9C_A8BF_DEB0CE75CAE2__INCLUDED_)
#define AFX_MYADODB_H__9FE345EF_CFCE_4C9C_A8BF_DEB0CE75CAE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "common.h"
#include <vector>

typedef std::vector<std::string>			CONT_STRING;



//////////////////////////////////////////////////////////////////////////

namespace BF
{
	class CAdoDB
	{
	public:
		CAdoDB(void);
		~CAdoDB(void);

		bool InitDB(std::string _strUserId, std::string _strPassWord, std::string _strDbIp, std::string _strDbName, std::string _strPort);
		bool InitDB(std::wstring _wstrUserId, std::wstring _wstrPassWord, std::wstring _wstrDbIp, std::wstring _wstrDbName, std::wstring _wstrPort);
		void ReleaseDB();
	public:
		_ConnectionPtr m_pConn; 
		_RecordsetPtr m_pRs; 
		_CommandPtr m_pComm;
	};

	/*
		DB사용 클래스.
		OpenDB	-	UserID (DB 접속할때 아이디)
					Password (DB 접속용 pw)
					IP (DB가 설치되어 있는 IP)
					DB Name(Data base Name)
					Port (Port)
					로 실행하면 해당 DB에 접속한다.
		QueryReady -	실행할 쿼리문을 준비한다. 택스트 형태로 입력하여 준비한다.
						쿼리문은 Select결과문을 받아오는 쿼리형태가 되어야 한다.
		AddParameter - 매개변수로 전송할 내용을 준비한다. QueryReady를 먼저 사용해서 쿼리문을 입력해놓지 않으면 추가되지 않는다.
		Execute - 준비해놓은 쿼리문 실행. 결과를 받아온다.
		GetReturnName
		         Value -	결과로 받아온 내용을 받는 부분. 테이블의 컬럼은 Name으로 받아오고 컬럼 내용은 Value로 받아온다.
							컬럼이 없는 결과의 경우 Name이 비어있다.
	*/
	class CAdoDBMgr
	{
	public:
		CAdoDBMgr();
		~CAdoDBMgr();

		bool OpenDB(std::string const _strUserId, std::string const _strPassWord, std::string const _strDbIp, std::string const _strDbName, std::string const _strPort);
		bool OpenDB(std::wstring const _wstrUserId, std::wstring const _wstrPassWord, std::wstring const _wstrDbIp, std::wstring const _wstrDbName, std::wstring const _wstrPort);
		void QueryReady(std::string const _strQuery);
		void QueryReady(std::wstring const _wstrQuery);

		void AddParameter(int &_Data);
		void AddParameter(int const &_Data);
		void AddParameter(unsigned int &_Data);
		void AddParameter(short &_Data);
		void AddParameter(__int64 &_Data);
		void AddParameter(ULONG64 &_Data);
		void AddParameter(ULONG64 const &_Data);
		void AddParameter(float &_Data);
		void AddParameter(double &_Data);
		void AddParameter(DWORD &_Data);
		void AddParameter(char &_Data);
		void AddParameter(char const &_Data);
		void AddParameter(wchar_t &_Data);
		void AddParameter(wchar_t const &_Data);
		void AddParameter(std::string const &_strParameter);
		void AddParameter(std::wstring const &_wstrParameter);

		bool Execute();
		CONT_STRING	GetReturnName() const;
		CONT_STRING	GetReturnValue() const;
	private:
		CAdoDB			m_AdoDB;
		std::string		m_strQuery;
		CONT_STRING		m_contReturnName;
		CONT_STRING		m_contReturnValue;
		bool			m_bAddParameter;
	};
}

#endif // !defined(AFX_MYADODB_H__9FE345EF_CFCE_4C9C_A8BF_DEB0CE75CAE2__INCLUDED_)