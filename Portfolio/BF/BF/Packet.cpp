#include "stdafx.h"
#include "Log.h"
#include "Packet.h"
#include "Range.h"

namespace BF
{
#pragma region	������/�Ҹ���
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
		GetData�� �ִ� D_SEND_LIMIT_SIZE + (sizeof(ULONG64)*3)ũ�⸸ŭ �����͸� ���´�.
		Packet�� ��ü ����� D_SEND_LIMIT_SIZE�� ������� �ִ� �����ŭ���� �����Ͽ� return �Ѵ�.
		������ ���3���� �� �����ͷ� �̷���� �ִ�.
		���1. PacketType
		���2. ���� ������ ����� D_SEND_LIMIT_SIZE�� �Ѿ ��� �����ϱ� ���� ��Ŷ ��ȣ��.
			   0�ϰ�� �ܵ�packet. 0 �̻��� ��� ���ҵ���Ÿ
		���3. �����ϴ� ������ ������.
	*/
	char* CPacket::GetData()
	{
		if(mCont_Data.empty() || mCont_Data.size() == mui_RTRealPos)	//	��Ŷ�� �����Ͱ� ���ų�, ��� �����Ͱ� ����ȭ�Ǿ� �ݳ��Ǿ��� ���.
			return nullptr;

		ULONG64 const nULONG64Size	= sizeof(ULONG64);
		ULONG64 nDataSize			= GetRTRemnantSize();	//	�����ؾ��� ���� ũ�⸦ ������.
		int nRTNumber				= 0;
		int nTotalNumber			= 0;
		int const nLocalSize		= static_cast<int>(mui_RTDataPos);
		/*	
			m_uiRTRealPos�� ������� ������ ������ Size�̹Ƿ� ���� ���� ��ȣ�� �ȴ�.
			m_ContData.Size() / D_SEND_LIMIT_SIZE�� 0�ϰ��(���� �ʿ䰡 ���� ���) 0
			���� �ʿ䰡 ������� ���� ������ ������(m_uiRTRealPos) / ���۰��� ������(D_SEND_LIMIT_SIZE) + 1�� ��Ŷ ��ȣ�� �Ǿ�
			��ȣ������ �����Ѵ�.
		*/
		ULONG64 unRTNumber = 0;		// unRTNumber ��ȣ�� 0�ϰ�� 0.
		int const nAllDataSize = GetAllDataSize();
		if (D_SEND_LIMIT_SIZE < nAllDataSize)	//	������ �ʿ䰡 �ִ� �������� ��� ������ ����.
		{
			nRTNumber		= (static_cast<int>(mui_RTRealPos) / D_SEND_LIMIT_SIZE) + 1;
			nTotalNumber	= ((nAllDataSize % D_SEND_LIMIT_SIZE) == 0) ? (nAllDataSize / D_SEND_LIMIT_SIZE) : ((nAllDataSize / D_SEND_LIMIT_SIZE) + 1);
			unRTNumber ^= nRTNumber;	//	���� �ѹ����� ����
			unRTNumber <<= sizeof(ULONG64) / 2 * 8;	//	ULONG64�� ����ũ�⸸ŭ ����Ʈ�Ѵ�.
			unRTNumber ^= nTotalNumber; //	��ü �ѹ����� ����
		}

		//	�����ؾ��� ���� ũ�Ⱑ �ѹ��� ������ ũ�⸦ �Ѿ ��� �̹��� ���۰���ũ�⸸ ������.
		if (D_SEND_LIMIT_SIZE < nDataSize)
		{
			nDataSize = D_SEND_LIMIT_SIZE;
		}

		//	mb_Lock�� �Ȱɷ��ִ� ���� ����ȭ�� �����ϴ� ���. ReturnData�� ��üũ�⸦ �غ��Ѵ�.
		if(false == mb_Lock)
		{
			mb_Lock = true;	//	����ȭ�� ���۵Ǿ����� ���� �Ǵ�.
			ReturnData.resize(nLocalSize + GetDivideAllRTSize());	//	��ü ����� �����Ѵ�.
		}
		::memcpy(&ReturnData[nLocalSize], &mui_PacketType, nULONG64Size);									//	���1. PacketType
		::memcpy(&ReturnData[nLocalSize + nULONG64Size], &unRTNumber, nULONG64Size);						//	���2. PacketNumber. 0���ϰ�� ������Ŷ. 1 �̻��ϰ�� ���ҵ� ��Ŷ�̴�.
		::memcpy(&ReturnData[nLocalSize + static_cast<LONG>(nULONG64Size * 2)], &nDataSize, nULONG64Size);	//	���3. DataSize.	������ ������ ������.
		::memcpy(&ReturnData[nLocalSize + static_cast<LONG>(nULONG64Size * 3)], &mCont_Data[static_cast<size_t>(mui_RTRealPos)], static_cast<size_t>(nDataSize)); //	���� ������

		mui_RTDataPos += static_cast<LONG32>(nDataSize + (nULONG64Size * 3));	//	������ ��ġ�� ����.
		mui_RTRealPos += nDataSize;		// ������ ���� ������.
		
		//	��ü �������� ����ȭ�� ������ ���. ���� Ǭ��.
		if(GetAllDataSize() == mui_RTRealPos)
			mb_Lock = false;

		return &ReturnData[nLocalSize];
	}

	// D_SEND_LIMIT_SIZE�� ������� ��ü �����͸� ����ȭ�Ͽ� �����´�. ��� ������ ����.
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

	//	����ִ� �����͵��� ��� �����Ͽ� �����ؾ� �ϴ���.
	int const CPacket::GetDivideCount() const
	{
		if(mCont_Data.empty())
			return 0;

		int const nAllDataSize = GetAllDataSize();
		int const nDivideCount = ((nAllDataSize % D_SEND_LIMIT_SIZE) == 0) ? (nAllDataSize / D_SEND_LIMIT_SIZE) : ((nAllDataSize / D_SEND_LIMIT_SIZE) + 1);

		return nDivideCount;
	}

	//	���� ������ ��ġ ���氡��. ����Ʈ�� 0
	bool CPacket::SetRTDataPos(ULONG64 const & _Pos /* = 0*/)
	{
		if(_Pos < mCont_Data.size())
			mui_RTRealPos = _Pos;
		return false;
	}

	//	������� ������ ũ�Ⱚ.
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
		����ȭ�� �����͸� ����ִµ� ����Ѵ�.
		BF::CPacket�� GetData�� GetAllData�� ����Ͽ� ���� char*�� ��밡���ϴ�. ������ �����͸� ������ ��Ÿ�� ������ �� �� �ִ�.
		return���� E_PACKET_ERROR::Complete�� ������ Pull�̳� Append�� ����� �� �ִ�.
	*/
	E_PACKET_ERROR::Enum CPacket::AddData(char * _strData)
	{
		if (nullptr == _strData)
		{
			BF_LOG.AddLog("CPacket::AddData(...) �Ű������� �����.");
			return E_PACKET_ERROR::Error;
		}

		LONG const nULONG64Size		= sizeof(ULONG64);
		ULONG64 const uiPacketType	= *reinterpret_cast<ULONG64 const *>(&_strData[0]);					//	��ŶŸ��
		ULONG64 uiNumber			= *reinterpret_cast<ULONG64 const *>(&_strData[nULONG64Size]);		//	����Ÿ �ѹ�. 0�ϰ�� ������Ŷ. �ƴҰ�� ���ҵ�����.
		ULONG64 const uiDataSize	= *reinterpret_cast<ULONG64 const *>(&_strData[nULONG64Size * 2]);	//	���� ������ Size.
		int nNumber = 0, nTotalNumber = 0;

		if (0 == uiDataSize)	//	���� DataSize�� 0�ϰ�� ��.
			return E_PACKET_ERROR::NonSize;

		if (false == mb_Lock)	//	���� �Ȱɷ� �ִٴ°� ó������ AddData�� ȣ��Ǿ��ٴ� �ǹ�.
		{
			this->Clear();		//	���� Packet�� ����.
			mb_Lock = true;		//	���� �Ǵ�.
		}
		if (uiNumber)
		{
			//	�� nTotalNumber���� ������Ŷ�� nNumber��° ��Ŷ�̶�� ��.
			nTotalNumber ^= uiNumber;				//	���ҵ� ��ü ����
			uiNumber >>= sizeof(ULONG64) / 2 * 8;
			nNumber ^= uiNumber;					//	���� ��Ŷ�� ��ȣ.

			if (mCont_Data.size() < static_cast<size_t>(D_SEND_LIMIT_SIZE * nTotalNumber))
				mCont_Data.resize(
					nTotalNumber * D_SEND_LIMIT_SIZE	//	������ �� Size.
				);
		}
		else
		{
			nNumber = 1;	//	���� memcpy���� &m_ContData[0]���� ����� ���� ������.
			mCont_Data.resize(static_cast<ULONG32>(uiDataSize));
		}

		::memcpy(&mCont_Data[(nNumber - 1) * D_SEND_LIMIT_SIZE]	//	(��ȣ -1 * D_SEND_LIMIT_SIZE) ��ġ���� 
				, &_strData[nULONG64Size * 3]						//	��������� �ں���.
				, static_cast<size_t>(uiDataSize));					//	������ �����ŭ ����.

		mui_PacketType = uiPacketType;	//	�޾Ƴ��� ��ŶŸ�� ����.

		mui_RealAddSize += uiDataSize;	//	���� Add�� ������ ũ��.
		int const nApply = ((mui_RealAddSize % D_SEND_LIMIT_SIZE) == 0) ? (static_cast<int>(mui_RealAddSize) / D_SEND_LIMIT_SIZE) : ((static_cast<int>(mui_RealAddSize) / D_SEND_LIMIT_SIZE) + 1);
		if(uiNumber == 0 || nApply == nTotalNumber)		//	������Ŷ�̰ų� �۾��� ��Ŷ�� ��ü��ŭ�� ���
		{
			mb_Lock		= false;				//	��Ŷ ������ �Ϸ�Ǿ����Ƿ� ���� Ǭ��.
			return E_PACKET_ERROR::Complete;	//	�ϼ��� ��Ŷ���� �˸�.
		}

		return E_PACKET_ERROR::Remnant;		//	���� �ϼ����� ���� ��Ŷ���� �˸�.
	}
#pragma endregion

#pragma region Packet Information
	//	��Ŷ Ÿ���� �����Ѵ�.
	void CPacket::SetPacketType(ULONG64 const & _pType)
	{
		this->mui_PacketType = _pType;
	}
	//	��Ŷ Ÿ���� �����´�.
	ULONG64 const	CPacket::GetPacketType() const
	{
		return mui_PacketType;
	}
	//	������ ���� ��Ŷ ������.
	int const CPacket::GetRTRemnantSize() const
	{
		return GetAllDataSize() - static_cast<int>(mui_RTRealPos);
	}
	/* 
		���� GetData()�� ����ϸ� ���� ���� �� ������
		GetData()���� �տ� ���Ǿ�� �Ѵ�.
	*/
	int const CPacket::GetRTLocalSize() const
	{
		int nSize = GetRTRemnantSize();
		if(D_SEND_LIMIT_SIZE < nSize)
			nSize = D_SEND_LIMIT_SIZE;
		return nSize + (sizeof(ULONG64) * 3);
	}
	//	����ȭ�� ��ü ������. GetAllData()�� ����Ͽ��� �� ������Ե� �������� ������� ����.
	int const	CPacket::GetAllRTDataSize() const
	{
		return ((sizeof(ULONG64) * 3) + GetAllDataSize());
	}

	bool		CPacket::CheckSize(unsigned int _iSize) const
	{
		//	��Ŷ�� �����Ͱ� ���ų�, ���� �������� ������ + ���� �������� ���� ��ü �������� ����� �ʰ��� ���, ���� ������ ���� 0�ϰ�� false
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
	//	Packet�� �� ��ü ������ size�� �޴´�.
	int const	CPacket::GetAllDataSize() const
	{
		return mCont_Data.size();
	}
	//	������ �����̳��� capacity�� �̸� Ȯ���Ѵ�.
	void CPacket::Reserve(ULONG64 const reserve_size)
	{
		if( 0 < reserve_size )
		{
			mCont_Data.reserve( static_cast<LONG>(reserve_size) );
		}
	}
	//	��ü ������ ũ�⸦ �����Ͽ������� �� ������ ũ�⸦ ��ȯ�Ѵ�. ���ҵǴ� ���� * �������ŭ �߰��ȴ�.
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