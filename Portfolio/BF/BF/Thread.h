#pragma once

#include <vector>
#include <list>
#include "common.h"
#include "AutoLock.h"

namespace BF
{
	typedef std::vector<HANDLE>		CONT_handle;

	class CThread
	{
	public:
		CThread(void);
		virtual ~CThread(void);
		static unsigned int WINAPI commthread(LPVOID pArguments);

		bool	GetbRunThread() const {return bRunThread;}
		void	SetbRunThread(bool const &_bSet) {bRunThread = _bSet;}
		void	EndThread(){bRunThread = false;}
		
		HANDLE	GetHandle() const {return hThread;}
		void	SetHandle(HANDLE const &_handle) {hThread = _handle;}
		
	protected:
		virtual bool run() = 0;		//	return true�� �Լ� �ݺ� ȣ��, false�� thread ����. 
		virtual bool Init() = 0;	//	return true�̸� ����, false�� ����.
		virtual void exit() = 0;
		HANDLE	hThread;
		bool	bRunThread;
	};

	typedef std::list<CThread*>	CONT_pThread;

	class CThreadMgr
	{
	public:
		static CThreadMgr& getInstance()
		{
			static CThreadMgr tempThreadMgr;
			return tempThreadMgr;
		}
		~CThreadMgr();

		HANDLE			Start(CThread * _pBFThread);		// �����带 ������.
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
		S_CS				m_cs;
	};
#define BF_THREAD_MGR	BF::CThreadMgr::getInstance()
}