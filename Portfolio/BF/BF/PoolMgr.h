#pragma once

#include <vector>
#include <Windows.h>
#include "PoolBase.h"
#include "AutoLock.h"

namespace BF
{
	typedef std::vector<int>		CONT_BOOL;
	typedef std::vector<CPoolBase*> CONT_POOLBASEPTR;

	typedef bool (*pSetRule)(CPoolBase*);
#define D_RETURN_FAIL 2147483646

	namespace EPoolType
	{
		enum Enum
		{
			Object,	//	��������
			Heap,	//	�����Ҵ� ������
		};
	}
	/*
		- ������ ������ Ŭ����.
		��� ������ ������ ����.
		1. PoolMgr�� �����Ҷ� �����Ҵ��� �ʿ��� �����͸� ������������� �ƴ��� ���Ѵ�.
			- �޸� ������ ���ֱ� �����̸� �ΰ����� ���� ������� ������ �߻��Ѵ�.
		1. CPoolBase�� ��ӹ��� �����͸� ť�� ����� �� �ִ�.
		2. ����ڴ� ���ť�� ��ϵ� �����Ϳ��� ���� �� �� �ִ�.
		3. ���ť�� ���ο� �����͸� ����ϴ°�� Enter�� ȣ��ȴ�.
		4. ���ť���� �����͸� �����Ϸ� �� �� ���� ������ �Ǵ°��� �ƴ϶� ���ť�� �̵��Ǹ� Exit�� ȣ��ȴ�
		5. ���ť���� ť index�� ť�� �� �޸������� ���� �� �� �ִ�.
		6. AllDelete�� ��� ���� �����Ѵ�. ��, �����Ҵ� �������� ��� �޸� �������� ���ش�. 
	*/
	class CPoolMgr
	{
	public:
		CPoolMgr(UINT _nMaxSize, EPoolType::Enum _eDataType = EPoolType::Object);
		~CPoolMgr();

		bool	InitPool(UINT const &_nMaxSize, bool const &_b_Reset = false);

		void	AddWaitObject(CPoolBase* pObject);
		void	AddWaitObjectArray(CPoolBase *_pObjectArray[], UINT const &_unSize);

		/*	
			���ť���� ���ť�� �̵���Ű�� �Լ�.
			�Ű������� ���� ������ ���ť�� 0���������� ������� �̵���.
			�Ű�����1�� �ʱ�ȭ ���� �����͸� �ְ���� LPVOID�� ����ȯ�ؼ� �ʱ�ȭ�� Ȱ���Ѵ�. �ȳ־�� ��.
			�Ű�����2�� �Լ� �����ͷ� bool name(CPoolBase*)���� �Լ��� ����Ҽ� ������
			���ٸ� ����Ҷ��� [](CPoolBase *_pPoolBase)->bool{}�������� ��� �����ϴ�.
			�־��� �Լ� �����ʹ� ��Ģ����. return true�� �ش��ϴ� �����͸� ���ť�� �̵���Ų��.
			�̰��� ����Ͽ� ���ϴ� �����͸� ���ť�� �̵� �����ϴ�.
		*/
		CPoolBase* GetNewObject(LPVOID _p = nullptr, pSetRule pRuleFunc = nullptr);
		/*	
			GetNewObject�� ���������� ��Ģ�� �ش��ϴ� ������Ʈ�� ���ť���� ���ť�� �ű��.
			����Ʈ �Ű������� ����.
			��Ģ�� �ش��ϴ� ��� ���ť �����͸� ���ť�� �ű��.( �ϳ��� �ű�°� �ƴ�)
		*/
		bool	DelObjects(pSetRule pRulFunc);
		//	���ť���� �ش� index�� �ش��ϴ� �����͸� �������� ���� �Լ�
		CPoolBase* GetObject(UINT const &_Index);
		CPoolBase* operator [](UINT i) ;
		//	������Ʈ ����(��������̳ʿ��� �� �����̳ʷ� �ű�)
		void	DelObject(CPoolBase const * const _obj);
		//	�̰� ���� ���� ������ ������ index�� �����ؼ� ����.
		void	DelObject(UINT const &_unIndex);


		//	��ü ����. �ƿ� ���ť �����ͱ��� �����Ѵ�.
		void	AllDelete();
		
		void	SetWaitLimitSize(UINT const &_un_MaxLimit);
		size_t	GetWaitLimitSize() const;

		UINT GetWaitSize() const;
		UINT GetUseSize() const;
		UINT GetObjectNumber(CPoolBase const * const _obj) const;

	private:
		EPoolType::Enum			me_DataType;

		CONT_POOLBASEPTR		mCont_Ptr;
		CONT_POOLBASEPTR		mCont_UsePtr;
								//	���ť ��Īť. ��Ī�Ǵ� ���ť�� �����Ͱ� ���� ��������� �ƴ����� �˷���.
		CONT_BOOL				mCont_WaitQueue;
								//	���ť ��Īť.	��Ī�Ǵ� ���ť�� �������� ��� �����̳� ��ġ�� �˷���.
		CONT_BOOL				mCont_UseQueue;

		BF::S_CS				m_cs;
	};


}