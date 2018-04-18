#include "stdafx.h"
#include "PoolMgr.h"
#include "Range.h"
#include "Log.h"

namespace BF
{
	CPoolMgr::CPoolMgr(UINT _nMaxSize, EPoolType::Enum _eDataType/* = EPoolType::Object*/)
		: me_DataType(_eDataType)
	{
		InitPool(_nMaxSize);
	}
	CPoolMgr::~CPoolMgr()
	{
		AllDelete();
	}

	bool	CPoolMgr::InitPool(UINT const &_nMaxSize, bool const &_b_Reset/* = false*/)
	{
		CAutoLock lock(m_cs);
		//	전체 삭제를 원하면서 컨테이너가 비어있지 않을 경우.
		if (_b_Reset && (NULL != mCont_Ptr.empty() && (NULL != mCont_UsePtr.empty()) && (NULL != mCont_UseQueue.empty()) && (NULL != mCont_WaitQueue.empty())))
			AllDelete();
		if (NULL != _nMaxSize && D_RETURN_FAIL > _nMaxSize)
		{
			this->mCont_WaitQueue.resize(_nMaxSize, D_RETURN_FAIL);
			//	데이터 넣을 공간만 확보
			this->mCont_Ptr.reserve(_nMaxSize);
			this->mCont_UsePtr.reserve(_nMaxSize);
			this->mCont_UseQueue.reserve(_nMaxSize);

			return true;
		}

		return false;
	}

	//	대기큐에 오브젝트를 설정하는 것. 실사용 가능한 상태가 아님.
	void CPoolMgr::AddWaitObject(CPoolBase * pObject)
	{
		CAutoLock lock(m_cs);
		mCont_Ptr.push_back(pObject);
		//	미리 만들어놓은 대기큐 매칭큐의 숫자를 넘어갔을 경우. 2배로 늘림
		if(mCont_Ptr.size() > mCont_WaitQueue.size())
			mCont_WaitQueue.resize(mCont_WaitQueue.size() * 2, D_RETURN_FAIL);
	}

	//	대기큐에 오브젝트를 배열로 설정. 실사용 가능한 상태가 아님.
	void CPoolMgr::AddWaitObjectArray(CPoolBase *_pObjectArray[], UINT const & _unSize)
	{
		for(UINT unIndex = 0; _unSize > unIndex; ++unIndex)
		{
			AddWaitObject(_pObjectArray[unIndex]);
		}
	}

	/*
		대기큐에 대기하고있던 데이터를 사용큐로 옮겨오는 역할.
		실제 생성은 아니며 룰을 지정해서 원하는 데이터를 지정해서 실행시킬 수 있다.
	*/
	CPoolBase* CPoolMgr::GetNewObject(LPVOID _p /*= nullptr*/, pSetRule pRuleFunc /*= nullptr*/)
	{
		CPoolBase* pReturn = nullptr;

		CAutoLock lock(m_cs);
		UINT const unCntMaxSize = mCont_Ptr.size();
		//for (UINT unIndex = 0; unCntMaxSize > unIndex; ++unIndex)
		for(UINT unIndex : range(unCntMaxSize))
		{
			if (D_RETURN_FAIL == mCont_WaitQueue[unIndex])	//	사용되고있지 않을 때.
			{
				//	생성룰이 있을 경우.
				if (pRuleFunc)
				{
					//	생성룰에 맞지 않을 때는 그냥 넘어감.
					if (false == pRuleFunc(mCont_Ptr[unIndex]))
						continue;
				}
				//	1. 사용하기 위해 초기화. Enter를 실행하고 결과값이 0이 아닐경우 풀에 배치 실패. nullptr 반환
				if (false == mCont_Ptr[unIndex]->Enter(_p))
				{
					BF_LOG.AddLog("BF.CPoolMgr::GetNewObject/ Enter Fail");
					return pReturn;
				}
				//	2. 사용큐에 옮김
				mCont_UsePtr.push_back(mCont_Ptr[unIndex]);
				//	3. 사용큐에 대기큐 주소를 넣음
				mCont_UseQueue.push_back(unIndex);
				//	4. 대기큐에 사용큐 주소를 넣음 (추가한 사용큐의 주소는 항상 Size - 1)
				mCont_WaitQueue[unIndex] = mCont_UseQueue.size() - 1;
				//	5. 바깥으로 보내줄 포인터값 저장	(UseValuePtr.back()이나 &Value[unIndex]나 상관없음)
				pReturn = mCont_UsePtr.back();
				break;
			}
		}

		return pReturn;
	}

	/*
	사용큐에서 데이터를 순서대로 가져오기 위한 함수.
	*/
	CPoolBase* CPoolMgr::GetObject(UINT const &_Index)
	{
		//	1. index가 사용큐 숫자 안쪽인 경우.
		CAutoLock lock(m_cs);
		if (_Index < mCont_UsePtr.size())
		{
			return mCont_UsePtr[_Index];
		}

		return nullptr;
	}

	CPoolBase * CPoolMgr::operator[](UINT _index)
	{
		CAutoLock lock(m_cs);
		if (_index < mCont_UsePtr.size())
		{
			return mCont_UsePtr[_index];
		}

		return nullptr;
	}

	//	오브젝트 삭제(실제 데이터 삭제는 아니며 사용컨테이너에서 총 컨테이너로 옮김)
	void	CPoolMgr::DelObject(CPoolBase const * const _obj)
	{
		CAutoLock lock(m_cs);
		int const nCntSize = mCont_UsePtr.size();
		//for (int nIndex = 0; nCntSize > nIndex; ++nIndex)
		for(int nIndex : range(nCntSize))
		{
			if (_obj == mCont_UsePtr[nIndex])
			{
				//	1. 뒤로 돌리기 전에 데이터 정리
				mCont_UsePtr[nIndex]->Exit();
				//	2. 대기큐에서 사용가능으로 돌린다.
				mCont_WaitQueue[mCont_UseQueue[nIndex]] = D_RETURN_FAIL;
				//	3. 사용큐의 맨 마지막 데이터를 현재위치로 복사한다
				mCont_UsePtr[nIndex] = mCont_UsePtr.back();
				mCont_UseQueue[nIndex] = mCont_UseQueue.back();
				//	4. 옮겨온 데이터의 위치를 대기큐에 복사한다.
				mCont_WaitQueue[mCont_UseQueue[nIndex]] = nIndex;
				//	4. 사용큐의 맨 마지막 데이터(복사되어 현재 2개인 데이터)를 삭제한다
				mCont_UsePtr.pop_back();
				mCont_UseQueue.pop_back();

				break;
			}
		}
	}
	
	//	이게 사용될 일은 없을것 같지만 index로 접근해서 삭제.
	void	CPoolMgr::DelObject(UINT const &_unIndex)
	{
		if (_unIndex < mCont_UsePtr.size())
			DelObject(mCont_UsePtr[_unIndex]);
	}

	//	모든 데이터 삭제.
	void	CPoolMgr::AllDelete()
	{
		CAutoLock lock(m_cs);
		if (EPoolType::Heap == me_DataType)
		{
			for (auto pValue : mCont_Ptr)
			{
				delete pValue;
			}
		}

		mCont_Ptr.clear();
		mCont_UsePtr.clear();
		mCont_WaitQueue.clear();
		mCont_UseQueue.clear();
	}

	/*
		기존 데이터를 유지한채 최대 갯수를 수정한다. 
		기존 데이터를 삭제하고 최대겟수를 세팅하고싶을 경우 AllDelete 후에 InitPool을 새로 호출하고나 InitPool의 두번재 인자를 true로 호출한다.
	*/
	void CPoolMgr::SetWaitLimitSize(UINT const &_un_MaxLimit)
	{
		InitPool(_un_MaxLimit);
	}

	UINT CPoolMgr::GetWaitSize() const
	{
		return mCont_Ptr.size();
	}

	UINT CPoolMgr::GetUseSize() const
	{
		return mCont_UsePtr.size();
	}

	UINT CPoolMgr::GetObjectNumber(CPoolBase const * const _obj) const
	{
		UINT unReturn = D_RETURN_FAIL;

		UINT unCntSize = mCont_UsePtr.size();
		//for (UINT unIndex = 0; unCntSize > unIndex; ++unIndex)
		for(UINT unIndex : range(unCntSize))
		{
			if (_obj == mCont_UsePtr[unIndex])
			{
				unReturn = unIndex;
				break;
			}
		}

		return unReturn;
	}
	size_t	CPoolMgr::GetWaitLimitSize() const
	{
		return mCont_Ptr.capacity();
	}

	bool	CPoolMgr::DelObjects(pSetRule pRulFunc)
	{
		CAutoLock lock(m_cs);
		int const nCntSize = mCont_UsePtr.size();
		//for (int nIndex = 0; nCntSize > nIndex; ++nIndex)
		for (int nIndex : range(0, nCntSize))
		{
			if (pRulFunc(mCont_UsePtr[nIndex]))
			{
				//	1. 뒤로 돌리기 전에 데이터 정리
				mCont_UsePtr[nIndex]->Exit();
				//	2. 대기큐에서 사용가능으로 돌린다.
				mCont_WaitQueue[mCont_UseQueue[nIndex]] = D_RETURN_FAIL;
				//	3. 사용큐의 맨 마지막 데이터를 현재위치로 복사한다
				mCont_UsePtr[nIndex] = mCont_UsePtr.back();
				mCont_UseQueue[nIndex] = mCont_UseQueue.back();
				//	4. 옮겨온 데이터의 위치를 대기큐에 복사한다.
				mCont_WaitQueue[mCont_UseQueue[nIndex]] = nIndex;
				//	4. 사용큐의 맨 마지막 데이터(복사되어 현재 2개인 데이터)를 삭제한다
				mCont_UsePtr.pop_back();
				mCont_UseQueue.pop_back();

				/*
					stl 컨테이너들의 값이 변경되었으므로 더이상 검색하거나 기존 데이터로 재사용시 문제가 생김
					재귀함수로 한번 더 호출하여 지운 결과가 없을때까지 전체 삭제.
				*/
				if(false == DelObjects(pRulFunc))
					return true;

				return true;
			}
		}
		return false;
	}
}

