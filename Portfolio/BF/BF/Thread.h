#pragma once

#include <windows.h>
#include <vector>
#include <list>
#include "common.h"

namespace BF
{
	typedef std::vector<HANDLE>		CONT_handle;

	class CThread
	{
	public:
		CThread(void);
		~CThread(void);
		static unsigned int WINAPI commthread(LPVOID pArguments);

		bool	GetbRunThread() const {return bRunThread;}
		void	SetbRunThread(bool const &_bSet) {bRunThread = _bSet;}
		void	EndThread(){bRunThread = false;}
		
		HANDLE	GetHandle() const {return hThread;}
		void	SetHandle(HANDLE const &_handle) {hThread = _handle;}
		
	protected:
		virtual void run() = 0;
		virtual bool Init() = 0;
		virtual void exit() = 0;
		HANDLE	hThread;
		bool	bRunThread;
		//int		a;
	};

	typedef std::list<CThread*>	CONT_pThread;

	//BFThreadMgr* BFThreadMgr::getInstance()
	//{
	//	static BFThreadMgr tempThreadMgr;
	//	return &tempThreadMgr;
	//}

	class CThreadMgr
	{
		typedef void (*TY_pFunc)(void);
	public:
		static CThreadMgr& getInstance()
		{
			static CThreadMgr tempThreadMgr;
			return tempThreadMgr;
		}
		~CThreadMgr();

		CONT_handle		Start(CThread * _pBFThread);		//	쓰레드를 일정 카운트만큼 실행함.
		CONT_handle		Start(CONT_pThread _ContPtrThread);
		void			End(HANDLE const _hEndThread);
		void			End(CONT_handle const _ConEndThread);
		void			AllEnd();
	private:
		explicit CThreadMgr();

		CThread* const GetClassPtr(HANDLE const _handle);

		void			DeletePtr(HANDLE const _handle);
		void			DeleteAllPtr();

		static CONT_pThread	m_stcConThreadClass;
	};
#define BFTHREAD_MGR	CThreadMgr::getInstance()
}