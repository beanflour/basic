#include "stdafx.h"
#include "Thread.h"
#include <process.h>
#include "Range.h"

namespace BF
{
	CONT_pThread	CThreadMgr::m_stcConThreadClass;

	CThread::CThread(void)
		:	bRunThread(true)//,
			//a(10)
	{
		printf("");
	}


	CThread::~CThread(void)
	{
	}

	unsigned int WINAPI CThread::commthread(LPVOID pArguments)
	{
		CThread* pThreadClass = reinterpret_cast<CThread*>(pArguments);

		pThreadClass->Init();

		while(pThreadClass->bRunThread)
			pThreadClass->run();

		pThreadClass->exit();
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////

	CThreadMgr::CThreadMgr()
	{
		m_stcConThreadClass.clear();
	}

	CThreadMgr::~CThreadMgr()
	{
		//m_stcConThreadClass.clear();
		this->AllEnd();
	}

	CONT_handle		CThreadMgr::Start(CThread * _pBFThread)
	{
		CONT_handle ConHandle;

		HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, &CThread::commthread, reinterpret_cast<LPVOID>(_pBFThread), 0, NULL);
		if(NULL == hThread)
			return ConHandle;
		_pBFThread->SetHandle(hThread);
		ConHandle.push_back(hThread);
		m_stcConThreadClass.push_back(_pBFThread);

		return ConHandle;
	}

	CONT_handle		CThreadMgr::Start(CONT_pThread _ContPtrThread)
	{
		CONT_handle ConHandle;
		for(auto _ptr : _ContPtrThread)
		{
			HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, &CThread::commthread, reinterpret_cast<LPVOID>(_ptr), 0, NULL);
			if(NULL == hThread)
				continue;
			_ptr->SetHandle(hThread);
			ConHandle.push_back(hThread);
			m_stcConThreadClass.push_back(_ptr);
		}

		return ConHandle;
	}

	void	CThreadMgr::End(HANDLE const _hEndThread)
	{
		auto ptr = this->GetClassPtr(_hEndThread);
		if(nullptr != ptr)
		{
			ptr->SetbRunThread(FALSE);
			::WaitForSingleObject(ptr->GetHandle(), INFINITE);
		}
	}

	void	CThreadMgr::End(CONT_handle const _ConEndThread)
	{
		for(HANDLE hEnd : _ConEndThread)
		{
			auto pThread = this->GetClassPtr(hEnd);
			if(!pThread)
				continue;

			pThread->EndThread();

		}

		::WaitForMultipleObjects(_ConEndThread.size(), _ConEndThread.data(), TRUE, INFINITE);
		for(HANDLE hEnd : _ConEndThread)
			this->DeletePtr(hEnd);
	}

	void	CThreadMgr::AllEnd()
	{
		CONT_handle conhTemp;
		for(CThread* _pThread : m_stcConThreadClass)
		{
			_pThread->EndThread();
			conhTemp.push_back(_pThread->GetHandle());
		}
		::WaitForMultipleObjects(conhTemp.size(), conhTemp.data(), TRUE, INFINITE);
		this->DeleteAllPtr();
	}

	CThread* const CThreadMgr::GetClassPtr(HANDLE const _handle)
	{
		for(auto ptr : m_stcConThreadClass)
		{
			if(_handle == ptr->GetHandle())
				return ptr;
		}

		return nullptr;
	}
	void	CThreadMgr::DeleteAllPtr()
	{
		for(auto ptr : m_stcConThreadClass)
		{
			SAFE_DELETE(ptr);
		}

		m_stcConThreadClass.clear();
	}

	
	void	CThreadMgr::DeletePtr(HANDLE const _handle)
	{
		auto pTemp = GetClassPtr(_handle);
		if(pTemp)
		{
			m_stcConThreadClass.remove(pTemp);
			SAFE_DELETE(pTemp);
		}
	}
}