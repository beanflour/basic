#include "stdafx.h"
#include "PoolMgr.h"

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
		//	��ü ������ ���ϸ鼭 �����̳ʰ� ������� ���� ���.
		if (_b_Reset && (NULL != mCont_Ptr.empty() && (NULL != mCont_UsePtr.empty()) && (NULL != mCont_UseQueue.empty()) && (NULL != mCont_WaitQueue.empty())))
			AllDelete();
		if (NULL != _nMaxSize && D_RETURN_FAIL > _nMaxSize)
		{
			this->mCont_WaitQueue.resize(_nMaxSize, D_RETURN_FAIL);
			//	������ ���� ������ Ȯ��
			this->mCont_Ptr.reserve(_nMaxSize);
			this->mCont_UsePtr.reserve(_nMaxSize);
			this->mCont_UseQueue.reserve(_nMaxSize);

			return true;
		}

		return false;
	}

	void CPoolMgr::AddWaitObject(CPoolBase * pObject)
	{
		mCont_Ptr.push_back(pObject);
		//	�̸� �������� ���ť ��Īť�� ���ڸ� �Ѿ�� ���. 2��� �ø�
		if(mCont_Ptr.size() > mCont_WaitQueue.size())
			mCont_WaitQueue.resize(mCont_WaitQueue.size() * 2, D_RETURN_FAIL);
	}

	void CPoolMgr::AddWaitObjectArray(CPoolBase *_pObjectArray[], UINT const & _unSize)
	{
		for(UINT unIndex = 0; _unSize > unIndex; ++unIndex)
		{
			AddWaitObject(_pObjectArray[unIndex]);
		}
	}

	/*
		���ť�� ����ϰ��ִ� �����͸� ���ť�� �Űܿ��� ����.
		���� ������ �ƴϸ� ���� �����ؼ� ���ϴ� �����͸� �����ؼ� �����ų �� �ִ�.
	*/
	CPoolBase* CPoolMgr::GetNewObject(pSetRule pRuleFunc /*= nullptr*/)
	{
		CPoolBase* pReturn = nullptr;
		UINT const unCntMaxSize = mCont_Ptr.size();
		for (UINT unIndex = 0; unCntMaxSize > unIndex; ++unIndex)
		{
			if (D_RETURN_FAIL == mCont_WaitQueue[unIndex])	//	���ǰ����� ���� ��.
			{
				//	�������� ���� ���.
				if (pRuleFunc)
				{
					//	�����꿡 ���� ���� ���� �׳� �Ѿ.
					if (false == pRuleFunc(mCont_Ptr[unIndex]))
						continue;
				}
				//	1. ����ϱ� ���� �ʱ�ȭ
				mCont_Ptr[unIndex]->Enter();
				//	2. ���ť�� �ű�
				mCont_UsePtr.push_back(mCont_Ptr[unIndex]);
				//	3. ���ť�� ���ť �ּҸ� ����
				mCont_UseQueue.push_back(unIndex);
				//	4. ���ť�� ���ť �ּҸ� ���� (�߰��� ���ť�� �ּҴ� �׻� Size - 1)
				mCont_WaitQueue[unIndex] = mCont_UseQueue.size() - 1;
				//	5. �ٱ����� ������ �����Ͱ� ����	(UseValuePtr.back()�̳� &Value[unIndex]�� �������)
				pReturn = mCont_UsePtr.back();
				break;
			}
		}

		return pReturn;
	}

	/*
	���ť���� �����͸� ������� �������� ���� �Լ�.
	*/
	CPoolBase* CPoolMgr::GetObject(UINT const &_Index)
	{
		//	1. index�� ���ť ���� ������ ���.
		if (_Index < mCont_UsePtr.size())
		{
			return mCont_UsePtr[_Index];
		}

		return nullptr;
	}

	//	������Ʈ ����(���� ������ ������ �ƴϸ� ��������̳ʿ��� �� �����̳ʷ� �ű�)
	void	CPoolMgr::DelObject(CPoolBase const * const _obj)
	{
		{
			int const nCntSize = mCont_UsePtr.size();
			for (int nIndex = 0; nCntSize > nIndex; ++nIndex)
			{
				if (_obj == mCont_UsePtr[nIndex])
				{
					//	1. �ڷ� ������ ���� ������ ����
					mCont_UsePtr[nIndex]->Exit();
					//	2. ���ť���� ��밡������ ������.
					mCont_WaitQueue[mCont_UseQueue[nIndex]] = D_RETURN_FAIL;
					//	3. ���ť�� �� ������ �����͸� ������ġ�� �����Ѵ�
					mCont_UsePtr[nIndex] = mCont_UsePtr.back();
					mCont_UseQueue[nIndex] = mCont_UseQueue.back();
					//	4. �Űܿ� �������� ��ġ�� ���ť�� �����Ѵ�.
					mCont_WaitQueue[mCont_UseQueue[nIndex]] = nIndex;
					//	4. ���ť�� �� ������ ������(����Ǿ� ���� 2���� ������)�� �����Ѵ�
					mCont_UsePtr.pop_back();
					mCont_UseQueue.pop_back();

					break;
				}
			}
		}
	}
	//	�̰� ���� ���� ������ ������ index�� �����ؼ� ����.
	void	CPoolMgr::DelObject(UINT const &_unIndex)
	{
		if (_unIndex < mCont_UsePtr.size())
			DelObject(mCont_UsePtr[_unIndex]);
	}

	void	CPoolMgr::AllDelete()
	{
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
		���� �����͸� ������ä �ִ� ������ �����Ѵ�. 
		���� �����͸� �����ϰ� �ִ�ټ��� �����ϰ����� ��� AllDelete �Ŀ� InitPool�� ���� ȣ���ϰ��� InitPool�� �ι��� ���ڸ� true�� ȣ���Ѵ�.
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
		for (UINT unIndex = 0; unCntSize > unIndex; ++unIndex)
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
}
