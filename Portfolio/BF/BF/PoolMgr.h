#pragma once

#include <vector>
#include <Windows.h>
#include "PoolBase.h"

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
			Object,	//	지역변수
			Heap,	//	동적할당 데이터
		};
	}
	/*
		- 데이터 관리용 클래스.
		사용 조건은 다음과 같다.
		1. PoolMgr를 생성할때 동적할당이 필요한 데이터만 집어넣을것인지 아닌지 정한다.
			- 메모리 해제를 해주기 위함이며 두가지를 섞어 넣을경우 에러가 발생한다.
		1. CPoolBase를 상속받은 데이터만 큐에 등록할 수 있다.
		2. 사용자는 사용큐에 등록된 데이터에만 접근 할 수 있다.
		3. 사용큐에 새로운 데이터를 등록하는경우 Enter가 호출된다.
		4. 사용큐에서 데이터를 삭제하려 할 때 실제 삭제가 되는것이 아니라 대기큐로 이동되며 Exit가 호출된다
		5. 사용큐에는 큐 index와 큐에 들어간 메모리정보로 접근 할 수 있다.
		6. AllDelete의 경우 정말 삭제한다. 단, 동적할당 데이터의 경우 메모리 해제까지 해준다. 
	*/
	class CPoolMgr
	{
	public:
		CPoolMgr(UINT _nMaxSize, EPoolType::Enum _eDataType = EPoolType::Object);
		~CPoolMgr();

		bool	InitPool(UINT const &_nMaxSize, bool const &_b_Reset = false);

		void	AddWaitObject(CPoolBase* pObject);
		void	AddWaitObjectArray(CPoolBase *_pObjectArray[], UINT const &_unSize);

		CPoolBase* GetNewObject(pSetRule pRuleFunc = nullptr);
		// 사용큐에서 해당 index에 해당하는 데이터를 가져오기 위한 함수
		CPoolBase* GetObject(UINT const &_Index);
		//	오브젝트 삭제(사용컨테이너에서 총 컨테이너로 옮김)
		void	DelObject(CPoolBase const * const _obj);
		//	이게 사용될 일은 없을것 같지만 index로 접근해서 삭제.
		void	DelObject(UINT const &_unIndex);

		//	전체 삭제. 아예 대기큐 데이터까지 삭제한다.
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
								//	대기큐 매칭큐. 매칭되는 대기큐에 데이터가 현재 사용중인지 아닌지를 알려줌.
		CONT_BOOL				mCont_WaitQueue;
								//	사용큐 매칭큐.	매칭되는 사용큐의 데이터의 대기 컨테이너 위치를 알려줌.
		CONT_BOOL				mCont_UseQueue;
	};


}