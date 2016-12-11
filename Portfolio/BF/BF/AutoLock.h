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

	class CAutoLock
	{
		
	public:
		CAutoLock(ELockType::Enum const _LockType = ELockType::eAutoLock)
		{
			InitializeCriticalSection(&m_cs);

			if(ELockType::eAutoLock == _LockType)
				EnterCriticalSection(&m_cs);
		}
		~CAutoLock()
		{
			LeaveCriticalSection(&m_cs);
		}

		void Lock()
		{
			EnterCriticalSection(&m_cs);
		}

		void UnLock()
		{
			LeaveCriticalSection(&m_cs);
		}
	private:
		CRITICAL_SECTION m_cs;
	};
}