#include "stdafx.h"
#include "Log.h"
#include "Packet.h"
#include "Range.h"

namespace BF
{
#pragma region	생성자/소멸자
	CPacket::CPacket(void)
		:	mui_PacketType(0)
		,	mui_PullDataPos(0)
		,	mui_RTDataPos(0)
		,	mui_RTRealPos(0)
		,	mui_RealAddSize(0)
		,	mb_Lock(false)
	{
	}

	CPacket::CPacket(int const &_iPacketType)
		:	mui_PacketType( _iPacketType )
		,	mui_PullDataPos(0)
		,	mui_RTDataPos(0)
		,	mui_RTRealPos(0)
		,	mui_RealAddSize(0)
		,	mb_Lock(false)
	{
	}

	CPacket::CPacket(CPacket const &_Packet)
		:	mui_PacketType( _Packet.mui_PacketType )
		,	mui_PullDataPos( _Packet.mui_PullDataPos )
		,	mui_RTDataPos(_Packet.mui_RTDataPos)
		,	mui_RTRealPos(_Packet.mui_RTRealPos)
		,	mCont_Data( _Packet.mCont_Data )
		,	mui_RealAddSize(_Packet.mui_RealAddSize)
		,	mb_Lock(_Packet.mb_Lock)
	{
	}

	CPacket::~CPacket(void)
	{
		Clear();
	}

	void CPacket::Clear()
	{
		mb_Lock			= false;
		mui_PacketType	= 0;
		mui_PullDataPos	= 0;
		mui_RealAddSize	= 0;
		mui_RTDataPos	= 0;
		mui_RTRealPos	= 0;
		mCont_Data.clear();
		ReturnData.clear();
	}
#pragma endregion

#pragma region Append
	void CPacket::Append(int &_Data)
	{
		if (mb_Lock)
			return;
		int const nAppendSize	= sizeof(int);
		mCont_Data.resize(static_cast<ULONG32>(mui_RealAddSize) + nAppendSize);
		memcpy(&mCont_Data[static_cast<ULONG32>(mui_RealAddSize)], &_Data, nAppendSize);
		mui_RealAddSize += nAppendSize;
	}
	void CPacket::Append(int const &_Data)
	{
		if (mb_Lock)
			return;
		int const nAppendSize	= sizeof(int);
		mCont_Data.resize(static_cast<ULONG32>(mui_RealAddSize) + nAppendSize);
		memcpy(&mCont_Data[static_cast<ULONG32>(mui_RealAddSize)], &_Data, nAppendSize);
		mui_RealAddSize += nAppendSize;
	}
	void CPacket::Append(ULONG32 &_Data)
	{
		if (mb_Lock)
			return;
		int const nAppendSize	= sizeof(ULONG32);
		mCont_Data.resize(static_cast<ULONG32>(mui_RealAddSize) + nAppendSize);
		memcpy(&mCont_Data[static_cast<ULONG32>(mui_RealAddSize)], &_Data, nAppendSize);
		mui_RealAddSize += nAppendSize;
	}
	void CPacket::Append(short &_Data)
	{
		if (mb_Lock)
			return;
		int const nAppendSize	= sizeof(short);
		mCont_Data.resize(static_cast<ULONG32>(mui_RealAddSize) + nAppendSize);
		memcpy(&mCont_Data[static_cast<ULONG32>(mui_RealAddSize)], &_Data, nAppendSize);
		mui_RealAddSize += nAppendSize;
	}
	void CPacket::Append(__int64 &_Data)
	{
		if (mb_Lock)
			return;
		int const nAppendSize	= sizeof(__int64);
		mCont_Data.resize(static_cast<ULONG32>(mui_RealAddSize) + nAppendSize);
		memcpy(&mCont_Data[static_cast<ULONG32>(mui_RealAddSize)], &_Data, nAppendSize);
		mui_RealAddSize += nAppendSize;
	}
	void CPacket::Append(ULONG64 &_Data)
	{
		if (mb_Lock)
			return;
		int const nAppendSize = sizeof(ULONG64);
		mCont_Data.resize(static_cast<ULONG32>(mui_RealAddSize) + nAppendSize);
		memcpy(&mCont_Data[static_cast<ULONG32>(mui_RealAddSize)], &_Data, nAppendSize);
		mui_RealAddSize += nAppendSize;
	}
	void CPacket::Append(ULONG64 const &_Data)
	{
		if (mb_Lock)
			return;
		int const nAppendSize = sizeof(ULONG64);
		mCont_Data.resize(static_cast<ULONG32>(mui_RealAddSize) + nAppendSize);
		memcpy(&mCont_Data[static_cast<ULONG32>(mui_RealAddSize)], &_Data, nAppendSize);
		mui_RealAddSize += nAppendSize;
	}
	void CPacket::Append(float &_Data)
	{
		if (mb_Lock)
			return;
		int const nAppendSize = sizeof(float);
		mCont_Data.resize(static_cast<ULONG32>(mui_RealAddSize) + nAppendSize);
		memcpy(&mCont_Data[static_cast<ULONG32>(mui_RealAddSize)], &_Data, nAppendSize);
		mui_RealAddSize += nAppendSize;
	}
	void CPacket::Append(double &_Data)
	{
		if (mb_Lock)
			return;
		int const nAppendSize = sizeof(double);
		mCont_Data.resize(static_cast<ULONG32>(mui_RealAddSize) + nAppendSize);
		memcpy(&mCont_Data[static_cast<ULONG32>(mui_RealAddSize)], &_Data, nAppendSize);
		mui_RealAddSize += nAppendSize;
	}
	void CPacket::Append(DWORD &_Data)
	{
		if (mb_Lock)
			return;
		int const nAppendSize = sizeof(DWORD);
		mCont_Data.resize(static_cast<ULONG32>(mui_RealAddSize) + nAppendSize);
		memcpy(&mCont_Data[static_cast<ULONG32>(mui_RealAddSize)], &_Data, nAppendSize);
		mui_RealAddSize += nAppendSize;
	}
	void CPacket::Append(char &_Data)
	{
		if (mb_Lock)
			return;
		int const nAppendSize = sizeof(char);
		mCont_Data.resize(static_cast<ULONG32>(mui_RealAddSize) + nAppendSize);
		memcpy(&mCont_Data[static_cast<ULONG32>(mui_RealAddSize)], &_Data, nAppendSize);
		mui_RealAddSize += nAppendSize;
	}
	void CPacket::Append(char const &_Data)
	{
		if (mb_Lock)
			return;
		int const nAppendSize = sizeof(char);
		mCont_Data.resize(static_cast<ULONG32>(mui_RealAddSize) + nAppendSize);
		memcpy(&mCont_Data[static_cast<ULONG32>(mui_RealAddSize)], &_Data, nAppendSize);
		mui_RealAddSize += nAppendSize;
	}
	void CPacket::Append(wchar_t &_Data)
	{
		if (mb_Lock)
			return;
		int const nAppendSize = sizeof(wchar_t);
		mCont_Data.resize(static_cast<ULONG32>(mui_RealAddSize) + nAppendSize);
		memcpy(&mCont_Data[static_cast<ULONG32>(mui_RealAddSize)], &_Data, nAppendSize);
		mui_RealAddSize += nAppendSize;
	}
	void CPacket::Append(wchar_t const &_Data)
	{
		if (mb_Lock)
			return;
		int const nAppendSize = sizeof(wchar_t);
		mCont_Data.resize(static_cast<ULONG32>(mui_RealAddSize) + nAppendSize);
		memcpy(&mCont_Data[static_cast<ULONG32>(mui_RealAddSize)], &_Data, nAppendSize);
		mui_RealAddSize += nAppendSize;
	}

	void	CPacket::Append(void const *pData, ULONG64 const iDataSize)
	{
		if (mb_Lock)
			return;
		this->Append(iDataSize);

		int const nAppendSize = static_cast<int>(iDataSize);
		mCont_Data.resize(static_cast<ULONG32>(mui_RealAddSize) + nAppendSize);
		memcpy(&mCont_Data[static_cast<ULONG32>(mui_RealAddSize)], pData, nAppendSize);
		mui_RealAddSize += nAppendSize;
	}

	void	CPacket::Append(char const *pData)
	{
		if (mb_Lock)
			return;
		ULONG64 const iDataSize = strlen( pData );
		*this << iDataSize;
		
		int const nAppendSize = static_cast<int>(iDataSize);
		mCont_Data.resize(static_cast<ULONG32>(mui_RealAddSize) + nAppendSize);
		memcpy(&mCont_Data[static_cast<ULONG32>(mui_RealAddSize)], pData, nAppendSize);
		mui_RealAddSize += nAppendSize;
	}

	void	CPacket::Append(char *pData)
	{
		if (mb_Lock)
			return;
		ULONG64 const iDataSize = strlen( pData );
		*this << iDataSize;

		int const nAppendSize = static_cast<int>(iDataSize);
		mCont_Data.resize(static_cast<ULONG32>(mui_RealAddSize) + nAppendSize);
		memcpy(&mCont_Data[static_cast<ULONG32>(mui_RealAddSize)], pData, nAppendSize);
		mui_RealAddSize += nAppendSize;
	}

	void	CPacket::Append(wchar_t const *pData)
	{
		if (mb_Lock)
			return;
		ULONG64 const iDataSize = wcslen( pData );
		*this << iDataSize;

		int const nAppendSize = static_cast<int>(iDataSize) * sizeof(wchar_t);
		mCont_Data.resize(static_cast<ULONG32>(mui_RealAddSize) + nAppendSize);
		memcpy(&mCont_Data[static_cast<ULONG32>(mui_RealAddSize)], pData, nAppendSize);
		mui_RealAddSize += nAppendSize;
	}

	void	CPacket::Append(wchar_t *pData)
	{
		if (mb_Lock)
			return;
		ULONG64 const iDataSize = wcslen( pData );
		*this << iDataSize;

		int const nAppendSize = static_cast<int>(iDataSize) * sizeof(wchar_t);
		mCont_Data.resize(static_cast<ULONG32>(mui_RealAddSize) + nAppendSize);
		memcpy(&mCont_Data[static_cast<ULONG32>(mui_RealAddSize)], pData, nAppendSize);
		mui_RealAddSize += nAppendSize;
	}
#pragma endregion

#pragma region Pull
	bool	CPacket::Pull(void *pData, ULONG64 const iDataSize)
	{
		if(false == mb_Lock && false == CheckSize(iDataSize))
			return false;

		memcpy( pData, &mCont_Data[ static_cast<LONG>(mui_PullDataPos) ] , static_cast<LONG>(iDataSize) );

		mui_PullDataPos += iDataSize;
		return true;
	}

	bool CPacket::Pull(int &_Data)
	{
		if(false == mb_Lock && CheckSize(sizeof(int)))
		{
			_Data = *reinterpret_cast<int const *>(&mCont_Data[static_cast<LONG>(mui_PullDataPos)]);
			mui_PullDataPos += sizeof(int);
		}
		else
			return false;

		return true;
	}
	bool CPacket::Pull(ULONG32 &_Data)
	{
		if(false == mb_Lock && CheckSize(sizeof(ULONG32)))
		{
			_Data = *reinterpret_cast<ULONG32 const *>(&mCont_Data[static_cast<LONG>(mui_PullDataPos)] );
			mui_PullDataPos += sizeof(ULONG32);
		}
		else
			return false;
		return true;
	}
	bool CPacket::Pull(short &_Data)
	{
		if(false == mb_Lock && CheckSize(sizeof(short)))
		{
			_Data = *reinterpret_cast<short const *>(&mCont_Data[static_cast<LONG>(mui_PullDataPos)]);
			mui_PullDataPos += sizeof(short);
		}
		else
			return false;
		return true;
	}
	bool CPacket::Pull(__int64 &_Data)
	{
		if(false == mb_Lock && CheckSize(sizeof(__int64)))
		{
			_Data = *reinterpret_cast<__int64 const *>(&mCont_Data[static_cast<LONG>(mui_PullDataPos)]);
			mui_PullDataPos += sizeof(__int64);
		}
		else
			return false;
		return true;
	}
	bool CPacket::Pull(ULONG64 &_Data)
	{
		if(false == mb_Lock && CheckSize(sizeof(ULONG64)))
		{
			_Data = *reinterpret_cast<ULONG64 const *>(&mCont_Data[static_cast<LONG>(mui_PullDataPos)] );
			mui_PullDataPos += sizeof(ULONG64);
		}
		else
			return false;
		return true;
	}
	bool CPacket::Pull(float &_Data)
	{
		if(false == mb_Lock && CheckSize(sizeof(float)))
		{
			_Data = *reinterpret_cast<float const *>(&mCont_Data[static_cast<LONG>(mui_PullDataPos)]);
			mui_PullDataPos += sizeof(float);
		}
		else
			return false;
		return true;
	}
	bool CPacket::Pull(double &_Data)
	{
		if(false == mb_Lock && CheckSize(sizeof(double)))
		{
			_Data = *reinterpret_cast<double const *>(&mCont_Data[static_cast<LONG>(mui_PullDataPos)]);
			mui_PullDataPos += sizeof(double);
		}
		else
			return false;
		return true;
	}
	bool CPacket::Pull(DWORD &_Data)
	{
		if(false == mb_Lock && CheckSize(sizeof(DWORD)))
		{
			_Data = *reinterpret_cast<DWORD const *>(&mCont_Data[static_cast<LONG>(mui_PullDataPos)]);
			mui_PullDataPos += sizeof(DWORD);
		}
		else
			return false;
		return true;
	}
	bool CPacket::Pull(char &_Data)
	{
		if(false == mb_Lock && CheckSize(sizeof(char)))
		{
			_Data = *reinterpret_cast<char const *>(&mCont_Data[static_cast<LONG>(mui_PullDataPos)]);

			mui_PullDataPos += sizeof(char);
		}
		else
			return false;
		return true;
	}
	bool CPacket::Pull(wchar_t &_Data)
	{
		if(false == mb_Lock && CheckSize(sizeof(wchar_t)))
		{
			_Data = *reinterpret_cast<wchar_t const *>(&mCont_Data[static_cast<LONG>(mui_PullDataPos)]);

			mui_PullDataPos += sizeof(wchar_t);
		}
		else
			return false;
		return true;
	}

	bool	CPacket::Pull(char *pData, ULONG64 const iDataPullSize)
	{
		if(false == mb_Lock && CheckSize(iDataPullSize * sizeof(char)))
		{
			memcpy(pData, &mCont_Data[static_cast<LONG>(mui_PullDataPos)], static_cast<LONG>(iDataPullSize));
			pData[iDataPullSize] = '\0';

			mui_PullDataPos += iDataPullSize;
			return true;
		}
		else
			return false;
		return false;
	}

	bool CPacket::Pull(char *pData)
	{
		if(mb_Lock && !CheckSize(sizeof(ULONG64)))
			return false;

		ULONG64 iDataSize = 0;
		*this >> iDataSize;
		if(!CheckSize(iDataSize))
			return false;

		return this->Pull(pData, iDataSize);
	}
	bool	CPacket::Pull(wchar_t *pData, ULONG64 const iDataPullSize)
	{
		if(false == mb_Lock && CheckSize(iDataPullSize * sizeof(wchar_t)))
		{
			::memcpy(pData, &mCont_Data[static_cast<LONG32>(mui_PullDataPos)], static_cast<ULONG32>(iDataPullSize) * sizeof(wchar_t));
			pData[iDataPullSize] = L'\0';
			mui_PullDataPos += (iDataPullSize * sizeof(wchar_t));

			return true;
		}

		return false;
	}
	bool	CPacket::Pull(wchar_t *pData)
	{
		if(mb_Lock && !CheckSize(sizeof(ULONG64)))
			return false;

		ULONG64	uiLength = 0;
		*this >> uiLength;
		if(0 == uiLength)
			return false;

		return this->Pull(pData, uiLength);
	}
#pragma endregion

#pragma region GetData
	/*
		GetData는 최대 D_SEND_LIMIT_SIZE + (sizeof(ULONG64)*3)크기만큼 데이터를 얻어온다.
		Packet의 전체 사이즈가 D_SEND_LIMIT_SIZE를 넘을경우 최대 사이즈만큼으로 분할하여 return 한다.
		구조는 헤더3개와 실 데이터로 이루어져 있다.
		헤더1. PacketType
		헤더2. 전송 데이터 사이즈가 D_SEND_LIMIT_SIZE를 넘어갈 경우 조립하기 위한 패킷 번호다.
			   0일경우 단독packet. 0 이상일 경우 분할데이타
		헤더3. 전송하는 데이터 사이즈.
	*/
	char* CPacket::GetData()
	{
		if(mCont_Data.empty() || mCont_Data.size() == mui_RTRealPos)	//	패킷에 데이터가 없거나, 모든 데이터가 직렬화되어 반납되었을 경우.
			return nullptr;

		ULONG64 const nULONG64Size	= sizeof(ULONG64);
		ULONG64 nDataSize			= GetRTRemnantSize();	//	전송해야할 남은 크기를 가져옴.
		int nRTNumber				= 0;
		int nTotalNumber			= 0;
		int const nLocalSize		= static_cast<int>(mui_RTDataPos);
		/*	
			m_uiRTRealPos는 현재까지 전송한 데이터 Size이므로 나눈 몫이 번호가 된다.
			m_ContData.Size() / D_SEND_LIMIT_SIZE가 0일경우(나눌 필요가 없을 경우) 0
			나눌 필요가 있을경우 실제 전송한 데이터(m_uiRTRealPos) / 전송가능 사이즈(D_SEND_LIMIT_SIZE) + 1이 패킷 번호가 되어
			번호순으로 조립한다.
		*/
		ULONG64 unRTNumber = 0;		// unRTNumber 번호가 0일경우 0.
		int const nAllDataSize = GetAllDataSize();
		if (D_SEND_LIMIT_SIZE < nAllDataSize)	//	분할할 필요가 있는 데이터일 경우 수정에 들어간다.
		{
			nRTNumber		= (static_cast<int>(mui_RTRealPos) / D_SEND_LIMIT_SIZE) + 1;
			nTotalNumber	= ((nAllDataSize % D_SEND_LIMIT_SIZE) == 0) ? (nAllDataSize / D_SEND_LIMIT_SIZE) : ((nAllDataSize / D_SEND_LIMIT_SIZE) + 1);
			unRTNumber ^= nRTNumber;	//	현재 넘버값을 넣음
			unRTNumber <<= sizeof(ULONG64) / 2 * 8;	//	ULONG64의 절반크기만큼 시프트한다.
			unRTNumber ^= nTotalNumber; //	전체 넘버값을 넣음
		}

		//	전송해야할 남은 크기가 한번에 전송할 크기를 넘어갈 경우 이번엔 전송가능크기만 전송함.
		if (D_SEND_LIMIT_SIZE < nDataSize)
		{
			nDataSize = D_SEND_LIMIT_SIZE;
		}

		//	mb_Lock이 안걸려있는 경우는 직렬화를 시작하는 경우. ReturnData의 전체크기를 준비한다.
		if(false == mb_Lock)
		{
			mb_Lock = true;	//	직렬화가 시작되었을때 락을 건다.
			ReturnData.resize(nLocalSize + GetDivideAllRTSize());	//	전체 사이즈를 정비한다.
		}
		::memcpy(&ReturnData[nLocalSize], &mui_PacketType, nULONG64Size);									//	헤드1. PacketType
		::memcpy(&ReturnData[nLocalSize + nULONG64Size], &unRTNumber, nULONG64Size);						//	헤드2. PacketNumber. 0번일경우 단일패킷. 1 이상일경우 분할된 패킷이다.
		::memcpy(&ReturnData[nLocalSize + static_cast<LONG>(nULONG64Size * 2)], &nDataSize, nULONG64Size);	//	헤드3. DataSize.	전송할 데이터 사이즈.
		::memcpy(&ReturnData[nLocalSize + static_cast<LONG>(nULONG64Size * 3)], &mCont_Data[static_cast<size_t>(mui_RTRealPos)], static_cast<size_t>(nDataSize)); //	실제 데이터

		mui_RTDataPos += static_cast<LONG32>(nDataSize + (nULONG64Size * 3));	//	전송한 위치를 변경.
		mui_RTRealPos += nDataSize;		// 전송한 실제 데이터.
		
		//	전체 데이터의 직렬화가 끝났을 경우. 락을 푼다.
		if(GetAllDataSize() == mui_RTRealPos)
			mb_Lock = false;

		return &ReturnData[nLocalSize];
	}

	// D_SEND_LIMIT_SIZE와 관계없는 전체 데이터를 직렬화하여 가져온다. 헤드 구조는 같다.
	char* CPacket::GetAllData()
	{
		if(mCont_Data.empty())
			return nullptr;

		ULONG64 const nULONG64Size	= sizeof(ULONG64);
		ULONG64 const nDataSize		= mCont_Data.size();
		ULONG64 const unRTNumber	= 0;

		ReturnData.clear();
		ReturnData.resize(static_cast<size_t>((nULONG64Size * 3) + nDataSize));
		::memcpy(&ReturnData[0], &mui_PacketType, nULONG64Size);
		::memcpy(&ReturnData[nULONG64Size], &unRTNumber, nULONG64Size);
		::memcpy(&ReturnData[static_cast<LONG>(nULONG64Size * 2)], &nDataSize, nULONG64Size);
		::memcpy(&ReturnData[static_cast<LONG>(nULONG64Size * 3)], &mCont_Data[0], static_cast<size_t>(nDataSize));
		return &ReturnData[0];
	}

	//	들어있는 데이터들이 몇개로 분할하여 전송해야 하는지.
	int const CPacket::GetDivideCount() const
	{
		if(mCont_Data.empty())
			return 0;

		int const nAllDataSize = GetAllDataSize();
		int const nDivideCount = ((nAllDataSize % D_SEND_LIMIT_SIZE) == 0) ? (nAllDataSize / D_SEND_LIMIT_SIZE) : ((nAllDataSize / D_SEND_LIMIT_SIZE) + 1);

		return nDivideCount;
	}

	//	전송 가능한 위치 변경가능. 디폴트는 0
	bool CPacket::SetRTDataPos(ULONG64 const & _Pos /* = 0*/)
	{
		if(_Pos < mCont_Data.size())
			mui_RTRealPos = _Pos;
		return false;
	}

	//	현재까지 전송한 크기값.
	ULONG64 CPacket::GetRTDataPos() const
	{
		return mui_RTRealPos;
	}
	int const CPacket::GetCallDataCount() const
	{
		if(0 != mui_RTRealPos)
			return ((static_cast<int>(mui_RTRealPos) / D_SEND_LIMIT_SIZE) + 1);

		return 0;
	}
	/*
		직렬화된 데이터를 집어넣는데 사용한다.
		BF::CPacket의 GetData나 GetAllData를 사용하여 얻어온 char*만 사용가능하다. 임의의 포인터를 넣으면 런타임 에러가 날 수 있다.
		return값이 E_PACKET_ERROR::Complete일 때에만 Pull이나 Append를 사용할 수 있다.
	*/
	E_PACKET_ERROR::Enum CPacket::AddData(char * _strData)
	{
		if (nullptr == _strData)
		{
			BF_LOG.AddLog("CPacket::AddData(...) 매개변수가 비었다.");
			return E_PACKET_ERROR::Error;
		}

		LONG const nULONG64Size		= sizeof(ULONG64);
		ULONG64 const uiPacketType	= *reinterpret_cast<ULONG64 const *>(&_strData[0]);					//	패킷타입
		ULONG64 uiNumber			= *reinterpret_cast<ULONG64 const *>(&_strData[nULONG64Size]);		//	데이타 넘버. 0일경우 단일패킷. 아닐경우 분할데이터.
		ULONG64 const uiDataSize	= *reinterpret_cast<ULONG64 const *>(&_strData[nULONG64Size * 2]);	//	실제 데이터 Size.
		int nNumber = 0, nTotalNumber = 0;

		if (0 == uiDataSize)	//	받은 DataSize가 0일경우 끝.
			return E_PACKET_ERROR::NonSize;

		if (false == mb_Lock)	//	락이 안걸려 있다는건 처음으로 AddData가 호출되었다는 의미.
		{
			this->Clear();		//	현재 Packet을 비우고.
			mb_Lock = true;		//	락을 건다.
		}
		if (uiNumber)
		{
			//	총 nTotalNumber개의 분할패킷중 nNumber번째 패킷이라는 뜻.
			nTotalNumber ^= uiNumber;				//	분할된 전체 갯수
			uiNumber >>= sizeof(ULONG64) / 2 * 8;
			nNumber ^= uiNumber;					//	현재 패킷의 번호.

			if (mCont_Data.size() < static_cast<size_t>(D_SEND_LIMIT_SIZE * nTotalNumber))
				mCont_Data.resize(
					nTotalNumber * D_SEND_LIMIT_SIZE	//	이전에 들어간 Size.
				);
		}
		else
		{
			nNumber = 1;	//	밑의 memcpy에서 &m_ContData[0]으로 만들기 위한 보정값.
			mCont_Data.resize(static_cast<ULONG32>(uiDataSize));
		}

		::memcpy(&mCont_Data[(nNumber - 1) * D_SEND_LIMIT_SIZE]	//	(번호 -1 * D_SEND_LIMIT_SIZE) 위치에서 
				, &_strData[nULONG64Size * 3]						//	헤더사이즈 뒤부터.
				, static_cast<size_t>(uiDataSize));					//	데이터 사이즈만큼 복사.

		mui_PacketType = uiPacketType;	//	받아놓은 패킷타입 복사.

		mui_RealAddSize += uiDataSize;	//	실제 Add된 데이터 크기.
		int const nApply = ((mui_RealAddSize % D_SEND_LIMIT_SIZE) == 0) ? (static_cast<int>(mui_RealAddSize) / D_SEND_LIMIT_SIZE) : ((static_cast<int>(mui_RealAddSize) / D_SEND_LIMIT_SIZE) + 1);
		if(uiNumber == 0 || nApply == nTotalNumber)		//	단일패킷이거나 작업한 패킷이 전체만큼일 경우
		{
			mb_Lock		= false;				//	패킷 구성이 완료되었으므로 락을 푼다.
			return E_PACKET_ERROR::Complete;	//	완성된 패킷임을 알림.
		}

		return E_PACKET_ERROR::Remnant;		//	아직 완성되지 않은 패킷임을 알림.
	}
#pragma endregion

#pragma region Packet Information
	//	패킷 타입을 변경한다.
	void CPacket::SetPacketType(ULONG64 const & _pType)
	{
		this->mui_PacketType = _pType;
	}
	//	패킷 타입을 가져온다.
	ULONG64 const	CPacket::GetPacketType() const
	{
		return mui_PacketType;
	}
	//	전송할 남은 패킷 사이즈.
	int const CPacket::GetRTRemnantSize() const
	{
		return GetAllDataSize() - static_cast<int>(mui_RTRealPos);
	}
	/* 
		현재 GetData()를 사용하면 갖고 오게 될 사이즈
		GetData()보다 앞에 사용되어야 한다.
	*/
	int const CPacket::GetRTLocalSize() const
	{
		int nSize = GetRTRemnantSize();
		if(D_SEND_LIMIT_SIZE < nSize)
			nSize = D_SEND_LIMIT_SIZE;
		return nSize + (sizeof(ULONG64) * 3);
	}
	//	직렬화할 전체 사이즈. GetAllData()를 사용하였을 때 갖고오게될 데이터의 사이즈와 같다.
	int const	CPacket::GetAllRTDataSize() const
	{
		return ((sizeof(ULONG64) * 3) + GetAllDataSize());
	}

	bool		CPacket::CheckSize(unsigned int _iSize) const
	{
		//	패킷에 데이터가 없거나, 현재 빠져나간 데이터 + 빼갈 데이터의 양이 전체 데이터의 사이즈를 초과할 경우, 빼갈 데이터 양이 0일경우 false
		if(mCont_Data.empty() || mui_PullDataPos + _iSize > /*m_ContData.size()*/mui_RealAddSize || 0 >= _iSize)		
			return false;

		return true;
	}

	bool		CPacket::CheckSize(ULONG64 _iSize) const
	{
		if(mCont_Data.empty() || mui_PullDataPos + _iSize > /*m_ContData.size()*/mui_RealAddSize || 0 == _iSize)
			return false;

		return true;
	}
	//	Packet에 들어간 전체 데이터 size를 받는다.
	int const	CPacket::GetAllDataSize() const
	{
		return mCont_Data.size();
	}
	//	데이터 컨테이너의 capacity를 미리 확보한다.
	void CPacket::Reserve(ULONG64 const reserve_size)
	{
		if( 0 < reserve_size )
		{
			mCont_Data.reserve( static_cast<LONG>(reserve_size) );
		}
	}
	//	전체 데이터 크기를 분할하였을때의 총 데이터 크기를 반환한다. 분할되는 갯수 * 헤드사이즈만큼 추가된다.
	int const CPacket::GetDivideAllRTSize() const
	{
		int const nHeadSize		= sizeof(ULONG64) * 3;
		int const nAllDataSize	= GetAllDataSize();
		int const nHeadCount	= GetDivideCount();
		return ((nHeadSize * nHeadCount) + nAllDataSize);
	}
#pragma endregion

#pragma region Operator >>
	CPacket&	CPacket::operator >>(bool&	_Data)
	{
		this->Pull(_Data);
		return *this;
	}
	CPacket&	CPacket::operator >>(int&	_Data)
	{
		this->Pull(_Data);
		return *this;
	}
	CPacket& CPacket::operator >>(unsigned int&	_Data)
	{
		this->Pull(_Data);
		return *this;
	}
	CPacket& CPacket::operator >>(short& _Data)
	{
		this->Pull(_Data);
		return *this;
	}
	CPacket& CPacket::operator >>(unsigned short _Data)
	{
		this->Pull(_Data);
		return *this;
	}
	CPacket& CPacket::operator >>(__int64&			_Data)
	{
		this->Pull(_Data);
		return *this;
	}
	CPacket& CPacket::operator >>(ULONG64&	_Data)
	{
		this->Pull(_Data);
		return *this;
	}
	CPacket& CPacket::operator >>(float& _Data)
	{
		this->Pull(_Data);
		return *this;
	}
	CPacket& CPacket::operator >>(double& _Data)
	{
		this->Pull(_Data);
		return *this;
	}
	CPacket& CPacket::operator >>(DWORD& _Data)
	{
		this->Pull(_Data);
		return *this;
	}
	CPacket& CPacket::operator >>(char&	_Data)
	{
		this->Pull(_Data);
		return *this;
	}
	CPacket& CPacket::operator >>(wchar_t& _Data)
	{
		this->Pull(_Data);
		return *this;
	}

	CPacket& CPacket::operator >>(char* pData)
	{
		this->Pull(pData);
		return *this;
	}
	CPacket& CPacket::operator >>(wchar_t* pData)
	{
		this->Pull(pData);
		return *this;
	}
	CPacket& CPacket::operator >>(std::string &strData)
	{
		this->Pull(strData);
		return *this;
	}
	CPacket& CPacket::operator >>(std::wstring & wstrData)
	{
		this->Pull(wstrData);
		return *this;
	}
#pragma endregion

#pragma region operator <<
	CPacket& CPacket::operator <<(bool _Data)
	{
		Append(_Data);
		return *this;
	}
	CPacket& CPacket::operator <<(int _Data)
	{
		Append(_Data);
		return *this;
	}
	CPacket& CPacket::operator <<(unsigned int _Data)
	{
		Append(_Data);
		return *this;
	}
	CPacket& CPacket::operator <<(short _Data)
	{
		Append(_Data);
		return *this;
	}
	CPacket& CPacket::operator <<(unsigned short _Data)
	{
		Append(_Data);
		return *this;
	}
	CPacket& CPacket::operator <<(__int64 _Data)
	{
		Append(_Data);
		return *this;
	}
	CPacket& CPacket::operator <<(ULONG64 _Data)
	{
		Append(_Data);
		return *this;
	}
	CPacket& CPacket::operator <<(float _Data)
	{
		Append(_Data);
		return *this;
	}
	CPacket& CPacket::operator <<(double _Data)
	{
		Append(_Data);
		return *this;
	}
	CPacket& CPacket::operator <<(DWORD& _Data)
	{
		Append(_Data);
		return *this;
	}
	CPacket& CPacket::operator <<(char&	_Data)
	{
		Append(_Data);
		return *this;
	}
	CPacket& CPacket::operator <<(wchar_t& _Data)
	{
		Append(_Data);
		return *this;
	}
	CPacket& CPacket::operator <<(char* pData)
	{
		Append(pData);
		return *this;
	}
	CPacket& CPacket::operator <<(std::string const & _strData)
	{
		Append(_strData);
		return *this;
	}
	CPacket& CPacket::operator <<(wchar_t* pData)
	{
		 Append(pData);
		return *this;
	}
	CPacket& CPacket::operator <<(std::wstring const & _wstrData)
	{
		Append(_wstrData);
		return *this;
	}
#pragma endregion
}