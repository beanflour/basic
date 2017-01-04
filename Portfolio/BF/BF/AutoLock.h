#pragma once

#include "common.h"

namespace BF
{
	namespace ELockType
	{
		enum Enum
		{
			eAutoLock,
			eAreaLock,
		};
	}

	struct S_CS
	{
		S_CS()
		{
			InitializeCriticalSection(&m_cs);
		}
		~S_CS()
		{
			DeleteCriticalSection(&m_cs);
		}
		CRITICAL_SECTION m_cs;
	};

	class CAutoLock
	{
		
	public:
		CAutoLock(S_CS &_cs, ELockType::Enum const _LockType = ELockType::eAutoLock)
			: CS(_cs)
		{
			InitializeCriticalSection(&CS.m_cs);

			if(ELockType::eAutoLock == _LockType)
				EnterCriticalSection(&CS.m_cs);
		}
		~CAutoLock()
		{
			LeaveCriticalSection(&CS.m_cs);
		}

		void Lock()
		{
			EnterCriticalSection(&CS.m_cs);
		}

		void UnLock()
		{
			LeaveCriticalSection(&CS.m_cs);
		}
	private:
		S_CS &CS;
	};
}