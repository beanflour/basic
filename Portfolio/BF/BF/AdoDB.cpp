#include "stdafx.h"
#include "AdoDB.h"
#include "formatstdstring.h"
#include "Log.h"
#include "Range.h"

namespace BF
{
	CAdoDB::CAdoDB(void)
	{
		::CoInitialize(0);
	}


	CAdoDB::~CAdoDB(void)
	{
		this->ReleaseDB();
		::CoUninitialize();
	}

	bool CAdoDB::InitDB(std::string _strUserId, std::string _strPassWord, std::string _strDbIp, std::string _strDbName, std::string _strPort)
	{
		std::string strConfig = format("User ID=%s;Password=%s;Data Source=%s;Initial Catalog=%s;Network Address=%s,%s;Network Library=dbmssocn", 
										_strUserId.c_str(), _strPassWord.c_str(), _strDbIp.c_str(), _strDbName.c_str(), _strDbIp.c_str(), _strPort.c_str());
		m_pConn = new _ConnectionPtr("ADODB.Connection");
		m_pConn->Provider = "SQLOLEDB";
		m_pConn->ConnectionString = strConfig.c_str();  
		try
		{
			m_pConn->Open("","","", adConnectUnspecified);
		}catch(...)
		{
			return FALSE;
		}

		m_pRs = new _RecordsetPtr("ADODB.Recordset");
		m_pRs->CursorType = adOpenDynamic;

		m_pComm = NULL;
		m_pComm.CreateInstance(__uuidof(Command));
		m_pComm->ActiveConnection = m_pConn;
		m_pComm->CommandType = adCmdText;

		return true;
	}
	void CAdoDB::ReleaseDB()
	{
		m_pComm = NULL;
		m_pConn = NULL;
		m_pRs = NULL;
	}

	//////////////////////////////////////////////////////////////////////////
	CAdoDBMgr::CAdoDBMgr()
		:	m_bAddParameter(false)
	{

	}

	CAdoDBMgr::~CAdoDBMgr()
	{

	}

	bool CAdoDBMgr::OpenDB(std::string const _strUserId, std::string const _strPassWord, std::string const _strDbIp, std::string const _strDbName, std::string const _strPort)
	{
		if(false == m_AdoDB.InitDB(_strUserId, _strPassWord, _strDbIp, _strDbName, _strPort))
		{
			BF_LOG.AddLog("DB Open Error");
			return false;
		}

		return true;
	}

	void CAdoDBMgr::QueryReady(std::string const _strQuery)
	{
		m_strQuery.clear();
		m_bAddParameter = false;
		m_strQuery = _strQuery + " ";
	}

#pragma region AddParameter
	void CAdoDBMgr::AddParameter(std::string const &_strParameter)
	{
		std::string strComma = " ";
		if(m_bAddParameter)
			strComma = D_STR_ADD_COMMA;
		else
			m_bAddParameter = true;
		m_strQuery += strComma + _strParameter;
	}
	void CAdoDBMgr::AddParameter(std::wstring const &_wstrParameter)
	{
		std::string strComma = " ";
		if(m_bAddParameter)
			strComma = D_STR_ADD_COMMA;
		else
			m_bAddParameter = true;

		std::string strTemp;
		strTemp.assign(_wstrParameter.begin(), _wstrParameter.end());
		m_strQuery += strComma + strTemp;
	}
	void CAdoDBMgr::AddParameter(int &_Data)
	{
		std::string strComma = " ";
		if(m_bAddParameter)
			strComma = D_STR_ADD_COMMA;
		else
			m_bAddParameter = true;

			m_strQuery += strComma + format("%d", _Data);
	}
	void CAdoDBMgr::AddParameter(int const &_Data)
	{
		std::string strComma = " ";
		if(m_bAddParameter)
			strComma = D_STR_ADD_COMMA;
		else
			m_bAddParameter = true;

		m_strQuery += strComma + format("%d", _Data);
	}
	void CAdoDBMgr::AddParameter(unsigned int &_Data)
	{
		std::string strComma = " ";
		if(m_bAddParameter)
			strComma = D_STR_ADD_COMMA;
		else
			m_bAddParameter = true;

		m_strQuery += strComma + format("%u", _Data);
	}
	void CAdoDBMgr::AddParameter(short &_Data)
	{
		std::string strComma = " ";
		if(m_bAddParameter)
			strComma = D_STR_ADD_COMMA;
		else
			m_bAddParameter = true;

		m_strQuery += strComma + format("%d", _Data);
	}
	void CAdoDBMgr::AddParameter(__int64 &_Data)
	{
		std::string strComma = " ";
		if(m_bAddParameter)
			strComma = D_STR_ADD_COMMA;
		else
			m_bAddParameter = true;

		m_strQuery += strComma + format("%I64d", _Data);
	}
	void CAdoDBMgr::AddParameter(ULONG64 &_Data)
	{
		std::string strComma = " ";
		if(m_bAddParameter)
			strComma = D_STR_ADD_COMMA;
		else
			m_bAddParameter = true;

		m_strQuery += strComma + format("%I64u", _Data);
	}
	void CAdoDBMgr::AddParameter(ULONG64 const &_Data)
	{
		std::string strComma = " ";
		if(m_bAddParameter)
			strComma = D_STR_ADD_COMMA;
		else
			m_bAddParameter = true;

		m_strQuery += strComma + format("%I64u", _Data);
	}
	void CAdoDBMgr::AddParameter(float &_Data)
	{
		std::string strComma = " ";
		if(m_bAddParameter)
			strComma = D_STR_ADD_COMMA;
		else
			m_bAddParameter = true;

		m_strQuery += strComma + format("%f", _Data);
	}
	void CAdoDBMgr::AddParameter(double &_Data)
	{
		std::string strComma = " ";
		if(m_bAddParameter)
			strComma = D_STR_ADD_COMMA;
		else
			m_bAddParameter = true;

		m_strQuery += strComma + format("%e", _Data);
	}
	void CAdoDBMgr::AddParameter(DWORD &_Data)
	{
		std::string strComma = " ";
		if(m_bAddParameter)
			strComma = D_STR_ADD_COMMA;
		else
			m_bAddParameter = true;

		m_strQuery += strComma + format("%u", _Data);
	}
	void CAdoDBMgr::AddParameter(char &_Data)
	{
		std::string strComma = " ";
		if(m_bAddParameter)
			strComma = D_STR_ADD_COMMA;
		else
			m_bAddParameter = true;

		m_strQuery += strComma + format("%c", _Data);
	}
	void CAdoDBMgr::AddParameter(char const &_Data)
	{
		std::string strComma = " ";
		if(m_bAddParameter)
			strComma = D_STR_ADD_COMMA;
		else
			m_bAddParameter = true;

		m_strQuery += strComma + format("%c", _Data);
	}
	void CAdoDBMgr::AddParameter(wchar_t &_Data)
	{
		std::string strComma = " ";
		if(m_bAddParameter)
			strComma = D_STR_ADD_COMMA;
		else
			m_bAddParameter = true;

		m_strQuery += strComma + format("%C", _Data);
	}
	void CAdoDBMgr::AddParameter(wchar_t const &_Data)
	{
		std::string strComma = " ";
		if(m_bAddParameter)
			strComma = D_STR_ADD_COMMA;
		else
			m_bAddParameter = true;

		m_strQuery += strComma + format("%C", _Data);
	}
#pragma endregion

	bool CAdoDBMgr::Execute()
	{
		m_AdoDB.m_pComm->CommandText = m_strQuery.c_str();
		m_contReturnName.clear();
		m_contReturnValue.clear();

		_RecordsetPtr &TempRs = m_AdoDB.m_pRs;
		try
		{
			TempRs = m_AdoDB.m_pComm->Execute(NULL, NULL, adCmdText);
		}
		catch(...)
		{
			BF_LOG.AddLog("DB Execute error");
			return false;
		}

		long const cnRow = TempRs->Fields->Count;

		char strTemp[_MAX_PATH] = {'\0',};
		_variant_t	vtColum;
		_variant_t	vtNull;	vtNull.ChangeType(VT_NULL);

		for(long nIndex = 0; nIndex < cnRow; nIndex++)
		{
			::ZeroMemory(strTemp, _MAX_PATH);
			vtColum = TempRs->Fields->GetItem(nIndex)->Name;
			vtColum.ChangeType(VT_BSTR);

			::StrCpyN(strTemp, (_bstr_t)vtColum, _MAX_PATH -1);
			std::string strTemp = strTemp;
			if(!strTemp.empty())
				m_contReturnName.push_back(std::string(strTemp));
		}

		while(!TempRs->adoEOF)
		{
			for(long nIndex = 0; nIndex < cnRow ; nIndex++)
			{
				vtColum = TempRs->GetCollect(nIndex);
				if(vtColum == vtNull)
				{
					vtColum = _variant_t("");
				}
				else
				{
					vtColum.ChangeType(VT_BSTR);
				}
				::StrCpyN(strTemp, (_bstr_t)vtColum, _MAX_PATH -1);
				m_contReturnValue.push_back(std::string(strTemp));
			}
			TempRs->MoveNext();
		}

		TempRs->Close();

		return true;
	}

	CONT_STRING	CAdoDBMgr::GetReturnName() const
	{
		return m_contReturnName;
	}
	CONT_STRING	CAdoDBMgr::GetReturnValue() const
	{
		return m_contReturnValue;
	}
}