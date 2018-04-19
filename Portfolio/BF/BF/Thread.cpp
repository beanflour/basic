#include "stdafx.h"
#include "Thread.h"
#include <process.h>
#include "Range.h"
#include "Log.h"

namespace BF
{
	CONT_pThread	CThreadMgr::m_stcConThreadClass;

	CThread::CThread(void)
		:	bRunThread(true)
	{
	}


	CThread::~CThread(void)
	{
	}

	unsigned int WINAPI CThread::commthread(LPVOID pArguments)
	{
		CThread* pThreadClass = reinterpret_cast<CThread*>(pArguments);

		if (false == pThreadClass->Init())
		{
			BF_LOG.AddLog("CThread::commthread / thread init 실패. 해당 스레드는 실행되지 않는다.");
			return D_ERRTYPE_THREAD_INIT;
		}
		
		while(pThreadClass->bRunThread && pThreadClass->run());

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

	HANDLE		CThreadMgr::Start(CThread * _pBFThread)
	{
		//CONT_handle ConHandle;

		HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, &CThread::commthread, reinterpret_cast<LPVOID>(_pBFThread), 0, NULL);
		if (NULL == hThread)
		{
			BF_LOG.AddLog("CThreadMgr::Start(CThread ..) beginthreadex 실패.");
			return NULL;
		}
		_pBFThread->SetHandle(hThread);
		//ConHandle.push_back(hThread);

		{
			CAutoLock alock(m_cs);
			m_stcConThreadClass.push_back(_pBFThread);
		}

		return hThread;
	}

	CONT_handle		CThreadMgr::Start(CONT_pThread _ContPtrThread)
	{
		UINT nIndex = 0;
		CONT_handle ConHandle;
		for(auto _ptr : _ContPtrThread)
		{
			HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, &CThread::commthread, reinterpret_cast<LPVOID>(_ptr), 0, NULL);
			if (NULL == hThread)
			{
				BF_LOG.AddLog("CThreadMgr::Start(CONT_pThread ..)의 beginthreadex 실패. Index %d", nIndex);
				continue;
			}
			_ptr->SetHandle(hThread);
			ConHandle.push_back(hThread);

			{
				CAutoLock alock(m_cs);
				m_stcConThreadClass.push_back(_ptr);
			}
			++nIndex;
		}

		return ConHandle;
	}

	void	CThreadMgr::End(HANDLE const _hEndThread)
	{
		auto ptr = this->GetClassPtr(_hEndThread);
		if(nullptr != ptr)
		{
			ptr->EndThread();
			::WaitForSingleObject(ptr->GetHandle(), INFINITE);
		}

		this->DeletePtr(ptr);
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
		{
			CAutoLock lock(m_cs);
			for (CThread* _pThread : m_stcConThreadClass)
			{
				_pThread->EndThread();
				conhTemp.push_back(_pThread->GetHandle());
			}
		}
		::WaitForMultipleObjects(conhTemp.size(), conhTemp.data(), TRUE, INFINITE);
		this->DeleteAllPtr();
	}

	CThread* const CThreadMgr::GetClassPtr(HANDLE const _handle)
	{
		CAutoLock lock(m_cs);
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

		{
			CAutoLock lock(m_cs);
			m_stcConThreadClass.clear();
		}
	}

	
	void	CThreadMgr::DeletePtr(HANDLE const _handle)
	{
		auto pTemp = GetClassPtr(_handle);
		if(pTemp)
		{
			{
				CAutoLock lock(m_cs);
				m_stcConThreadClass.remove(pTemp);
			}
			SAFE_DELETE(pTemp);
		}
	}
}