#include "stdafx.h"
#include "Packet.h"
#include "Range.h"

namespace BF
{
#pragma region	생성자/소멸자
	CPacket::CPacket(void)
		:	m_uiPacketType(0)
		,	m_uiDataPos(0)
	{
	}

	CPacket::CPacket(int const &_iPacketType)
		:	m_uiPacketType( _iPacketType )
		,	m_uiDataPos(0)
	{
	}

	CPacket::CPacket(CPacket const &_Packet)
		:	m_uiPacketType( _Packet.m_uiPacketType )
		,	m_uiDataPos( _Packet.m_uiDataPos )
		,	m_ContData( _Packet.m_ContData )
	{
	}

	CPacket::~CPacket(void)
	{
	}
#pragma endregion

#pragma region Append
	void CPacket::Append(int &_Data)
	{
		int const nPrevSize = m_ContData.size();
		m_ContData.resize(nPrevSize + sizeof(int));
		memcpy(&m_ContData[nPrevSize], &_Data, sizeof(int));
	}
	void CPacket::Append(int const &_Data)
	{
		int const nPrevSize = m_ContData.size();
		m_ContData.resize(nPrevSize + sizeof(int));
		memcpy(&m_ContData[nPrevSize], &_Data, sizeof(int));
	}
	void CPacket::Append(ULONG32 &_Data)
	{
		int const nPrevSize = m_ContData.size();
		m_ContData.resize(nPrevSize + sizeof(ULONG32));
		memcpy(&m_ContData[nPrevSize], &_Data, sizeof(ULONG32));
	}
	void CPacket::Append(short &_Data)
	{
		int const nPrevSize = m_ContData.size();
		m_ContData.resize(nPrevSize + sizeof(short));
		memcpy(&m_ContData[nPrevSize], &_Data, sizeof(short));
	}
	void CPacket::Append(__int64 &_Data)
	{
		int const nPrevSize = m_ContData.size();
		m_ContData.resize(nPrevSize + sizeof(__int64));
		memcpy(&m_ContData[nPrevSize], &_Data, sizeof(__int64));
	}
	void CPacket::Append(ULONG64 &_Data)
	{
		int const nPrevSize = m_ContData.size();
		m_ContData.resize(nPrevSize + sizeof(ULONG64));
		memcpy(&m_ContData[nPrevSize], &_Data, sizeof(ULONG64));
	}
	void CPacket::Append(ULONG64 const &_Data)
	{
		int const nPrevSize = m_ContData.size();
		m_ContData.resize(nPrevSize + sizeof(ULONG64));
		memcpy(&m_ContData[nPrevSize], &_Data, sizeof(ULONG64));
	}
	void CPacket::Append(float &_Data)
	{
		int const nPrevSize = m_ContData.size();
		m_ContData.resize(nPrevSize + sizeof(float));
		memcpy(&m_ContData[nPrevSize], &_Data, sizeof(float));
	}
	void CPacket::Append(double &_Data)
	{
		int const nPrevSize = m_ContData.size();
		m_ContData.resize(nPrevSize + sizeof(double));
		memcpy(&m_ContData[nPrevSize], &_Data, sizeof(double));
	}
	void CPacket::Append(DWORD &_Data)
	{
		int const nPrevSize = m_ContData.size();
		m_ContData.resize(nPrevSize + sizeof(DWORD));
		memcpy(&m_ContData[nPrevSize], &_Data, sizeof(DWORD));
	}
	void CPacket::Append(char &_Data)
	{
		int const nPrevSize = m_ContData.size();
		m_ContData.resize(nPrevSize + sizeof(char));
		memcpy(&m_ContData[nPrevSize], &_Data, sizeof(char));
	}
	void CPacket::Append(char const &_Data)
	{
		int const nPrevSize = m_ContData.size();
		m_ContData.resize(nPrevSize + sizeof(char));
		memcpy(&m_ContData[nPrevSize], &_Data, sizeof(char));
	}
	void CPacket::Append(wchar_t &_Data)
	{
		int const nPrevSize = m_ContData.size();
		m_ContData.resize(nPrevSize + sizeof(wchar_t));
		memcpy(&m_ContData[nPrevSize], &_Data, sizeof(wchar_t));
	}
	void CPacket::Append(wchar_t const &_Data)
	{
		int const nPrevSize = m_ContData.size();
		m_ContData.resize(nPrevSize + sizeof(wchar_t));
		memcpy(&m_ContData[nPrevSize], &_Data, sizeof(wchar_t));
	}
	/*void CPacket::Append(char *pData)
	{
		m_ContData.resize(m_ContData.size() + sizeof(char));
		memcpy(&m_ContData[m_ContData.size()], pData, sizeof(double));
	}
	void CPacket::Append(char const *pData)
	{
		m_ContData.resize(m_ContData.size() + sizeof(char));
		memcpy(&m_ContData[m_ContData.size()], pData, sizeof(double));
	}*/

	void	CPacket::Append(void const *pData, ULONG64 const iDataSize)
	{
		//*this << iDataSize;
		this->Append(iDataSize);

		int const nPrevSize	= m_ContData.size();
		m_ContData.resize(nPrevSize + static_cast<int>(iDataSize));
		memcpy(&m_ContData[nPrevSize], pData, static_cast<int>(iDataSize));
	}

	void	CPacket::Append(char const *pData)
	{
		ULONG64 const iDataSize = strlen( pData );
		*this << iDataSize;
		
		int const nPrevSize = m_ContData.size();
		m_ContData.resize(nPrevSize + static_cast<int>(iDataSize));
		memcpy(&m_ContData[nPrevSize], pData, static_cast<int>(iDataSize));
	}

	void	CPacket::Append(char *pData)
	{
		ULONG64 const iDataSize = strlen( pData );
		*this << iDataSize;

		int const nPrevSize = m_ContData.size();
		m_ContData.resize(nPrevSize + static_cast<int>(iDataSize));
		memcpy(&m_ContData[nPrevSize], pData, static_cast<int>(iDataSize));
	}

	void	CPacket::Append(wchar_t const *pData)
	{
		ULONG64 const iDataSize = wcslen( pData );
		*this << iDataSize;

		int const nPrevSize = m_ContData.size();
		m_ContData.resize(nPrevSize + (static_cast<int>(iDataSize) * sizeof(wchar_t)));
		memcpy(&m_ContData[nPrevSize], pData, (static_cast<int>(iDataSize) * sizeof(wchar_t)));
	}

	void	CPacket::Append(wchar_t *pData)
	{
		ULONG64 const iDataSize = wcslen( pData );
		*this << iDataSize;

		int const nPrevSize = m_ContData.size();
		m_ContData.resize(nPrevSize + (static_cast<int>(iDataSize) * sizeof(wchar_t)));
		memcpy(&m_ContData[nPrevSize], pData, (static_cast<int>(iDataSize) * sizeof(wchar_t)));
	}
#pragma endregion

#pragma region Pull
	bool	CPacket::Pull(void *pData, ULONG64 const iDataSize)
	{
		if( false == CheckSize(iDataSize))
			return false;

		memcpy( pData, &m_ContData[ static_cast<LONG>(m_uiDataPos) ] , static_cast<LONG>(iDataSize) );

		m_uiDataPos += iDataSize;
		return true;
	}

	bool CPacket::Pull(int &_Data)
	{
		/*ULONG64 const nCSize = sizeof(int);
		if(false == CheckSize(nCSize))
			return false;

		memcpy(&_Data, &m_ContData[static_cast<LONG>(m_uiDataPos)], nCSize);
		m_uiDataPos += nCSize;*/

		if(CheckSize(sizeof(int)))
		{
			_Data = *reinterpret_cast<int const *>(&m_ContData[static_cast<LONG>(m_uiDataPos)]);
			m_uiDataPos += sizeof(int);
		}

		return true;
	}
	bool CPacket::Pull(ULONG32 &_Data)
	{
		/*ULONG64 const nCSize = sizeof(ULONG32);
		if(false == CheckSize(nCSize))
		return false;

		memcpy(&_Data, &m_ContData[static_cast<ULONG32>(m_uiDataPos)], nCSize);
		m_uiDataPos += nCSize;*/
		
		if(CheckSize(sizeof(ULONG32)))
		{
			_Data = *reinterpret_cast<ULONG32 const *>(&m_ContData[static_cast<LONG>(m_uiDataPos)] );
			m_uiDataPos += sizeof(ULONG32);
		}
		return true;
	}
	bool CPacket::Pull(short &_Data)
	{
		/*ULONG64 const nCSize = sizeof(short);
		if(false == CheckSize(nCSize))
			return false;

		memcpy(&_Data, &m_ContData[static_cast<ULONG32>(m_uiDataPos)], nCSize);
		m_uiDataPos += nCSize;*/

		if(CheckSize(sizeof(short)))
		{
			_Data = *reinterpret_cast<short const *>(&m_ContData[static_cast<LONG>(m_uiDataPos)]);
			m_uiDataPos += sizeof(short);
		}
		return true;
	}
	bool CPacket::Pull(__int64 &_Data)
	{
		/*ULONG64 const nCSize = sizeof(__int64);
		if(false == CheckSize(nCSize))
			return false;

		memcpy(&_Data, &m_ContData[static_cast<ULONG32>(m_uiDataPos)], nCSize);
		m_uiDataPos += nCSize;*/
		if(CheckSize(sizeof(__int64)))
		{
			_Data = *reinterpret_cast<__int64 const *>(&m_ContData[static_cast<LONG>(m_uiDataPos)]);
			m_uiDataPos += sizeof(__int64);
		}
		return true;
	}
	bool CPacket::Pull(ULONG64 &_Data)
	{
		/*ULONG64 const nCSize = sizeof(ULONG64);
		if(false == CheckSize(nCSize))
			return false;

		memcpy(&_Data, &m_ContData[static_cast<ULONG32>(m_uiDataPos)], nCSize);
		m_uiDataPos += nCSize;*/
		if(CheckSize(sizeof(ULONG64)))
		{
			_Data = *reinterpret_cast<ULONG64 const *>(&m_ContData[static_cast<LONG>(m_uiDataPos)] );
			m_uiDataPos += sizeof(ULONG64);
		}
		return true;
	}
	bool CPacket::Pull(float &_Data)
	{
		/*ULONG64 const nCSize = sizeof(float);
		if(false == CheckSize(nCSize))
			return false;

		memcpy(&_Data, &m_ContData[static_cast<ULONG32>(m_uiDataPos)], nCSize);
		m_uiDataPos += nCSize;*/
		if(CheckSize(sizeof(float)))
		{
			_Data = *reinterpret_cast<float const *>(&m_ContData[static_cast<LONG>(m_uiDataPos)]);
			m_uiDataPos += sizeof(float);
		}
		return true;
	}
	bool CPacket::Pull(double &_Data)
	{
		/*ULONG64 const nCSize = sizeof(double);
		if(false == CheckSize(nCSize))
			return false;

		memcpy(&_Data, &m_ContData[static_cast<ULONG32>(m_uiDataPos)], nCSize);
		m_uiDataPos += nCSize;*/
		if(CheckSize(sizeof(double)))
		{
			_Data = *reinterpret_cast<double const *>(&m_ContData[static_cast<LONG>(m_uiDataPos)]);
			m_uiDataPos += sizeof(double);
		}
		return true;
	}
	bool CPacket::Pull(DWORD &_Data)
	{
		/*ULONG64 const nCSize = sizeof(DWORD);
		if(false == CheckSize(nCSize))
			return false;

		memcpy(&_Data, &m_ContData[static_cast<ULONG32>(m_uiDataPos)], nCSize);
		m_uiDataPos += nCSize;*/
		if(CheckSize(sizeof(DWORD)))
		{
			_Data = *reinterpret_cast<DWORD const *>(&m_ContData[static_cast<LONG>(m_uiDataPos)]);
			m_uiDataPos += sizeof(DWORD);
		}
		return true;
	}
	bool CPacket::Pull(char &_Data)
	{
		/*ULONG64 const nCSize = sizeof(char);
		if(!CheckSize(nCSize))
			return false;

		memcpy(&_Data, &m_ContData[static_cast<ULONG32>(m_uiDataPos)], nCSize);
		m_uiDataPos += nCSize;*/
		if(CheckSize(sizeof(char)))
		{
			//memcpy(&_Data, &m_ContData[static_cast<LONG>(m_uiDataPos)], sizeof(char));
			_Data = *reinterpret_cast<char const *>(&m_ContData[static_cast<LONG>(m_uiDataPos)]);

			m_uiDataPos += sizeof(char);
		}
		return true;
	}
	bool CPacket::Pull(wchar_t &_Data)
	{
		/*ULONG64 const nCSize = sizeof(wchar_t);
		if(!CheckSize(nCSize))
			return false;
		memcpy(&_Data, &m_ContData[static_cast<ULONG32>(m_uiDataPos)], nCSize);
		m_uiDataPos += nCSize;*/
		if(CheckSize(sizeof(wchar_t)))
		{
			//memcpy(&_Data, &m_ContData[static_cast<LONG>(m_uiDataPos)], sizeof(wchar_t));
			_Data = *reinterpret_cast<wchar_t const *>(&m_ContData[static_cast<LONG>(m_uiDataPos)]);

			m_uiDataPos += sizeof(wchar_t);
		}
		return true;
	}

	bool	CPacket::Pull(char *pData, ULONG64 const iDataPullSize)
	{
		//if(false == CheckSize(iDataMaxSize))
		//	return false;
		//
		//return this->Pull(pData);

		if(CheckSize(iDataPullSize * sizeof(char)))
		{
			memcpy(pData, &m_ContData[static_cast<LONG>(m_uiDataPos)], static_cast<LONG>(iDataPullSize));
			pData[iDataPullSize] = '\0';

			m_uiDataPos += iDataPullSize;
			return true;
		}
		return false;
	}

	bool CPacket::Pull(char *pData)
	{
		if(!CheckSize(sizeof(ULONG64)))
			return false;

		ULONG64 iDataSize = 0;
		*this >> iDataSize;
		if(!CheckSize(iDataSize))
			return false;

		return this->Pull(pData, iDataSize);
	}
	bool	CPacket::Pull(wchar_t *pData, ULONG64 const iDataPullSize)
	{
		if(CheckSize(iDataPullSize * sizeof(wchar_t)))
		{
			/*for(ULONG64 uiCount : range(static_cast<ULONG64>(0), iDataPullSize))
			{
				wchar_t wcGetData = 0;
				*this >> wcGetData;
				pData[uiCount] = wcGetData;
			}*/
			::memcpy(pData, &m_ContData[static_cast<LONG32>(m_uiDataPos)], static_cast<ULONG32>(iDataPullSize) * sizeof(wchar_t));
			pData[iDataPullSize] = L'\0';
			m_uiDataPos += (iDataPullSize * sizeof(wchar_t));

			return true;
		}

		return false;
	}
	bool	CPacket::Pull(wchar_t *pData)
	{
		if(!CheckSize(sizeof(ULONG64)))
			return false;

		ULONG64	uiLength = 0;
		*this >> uiLength;
		if(0 == uiLength)
			return false;

		return this->Pull(pData, uiLength);
	}
#pragma endregion

#pragma region GetData
	//char const*	CPacket::GetData()
	char* CPacket::GetData()
	{
		if(m_ContData.empty())
			return nullptr;

		ULONG64 const nULONG64Size = sizeof(ULONG64);
		ULONG64 const nDataSize = GetDataSize();
		ReturnData.clear();
		ReturnData.resize(nULONG64Size + nULONG64Size + GetDataSize());
		::memcpy(&ReturnData[0], &m_uiPacketType, sizeof(ULONG64));
		::memcpy(&ReturnData[nULONG64Size], &nDataSize, nULONG64Size);
		::memcpy(&ReturnData[static_cast<LONG>(nULONG64Size + nULONG64Size)], &m_ContData[0], static_cast<size_t>(nDataSize));

		return &ReturnData[0];
	}

	E_PACKET_ERROR::Enum CPacket::AddData(char * _strData)
	{
		LONG const nULONG64Size = sizeof(ULONG64);
		m_uiDataPos = 0;	//	새로운 데이터로 채워졌으니 기존에 읽엇던 정보를 초기화함.
		m_ContData.clear();
	
		m_uiPacketType = *reinterpret_cast<ULONG64 const *>(&_strData[0]);
		ULONG64 uiDataSize = *reinterpret_cast<ULONG64 const *>(&_strData[nULONG64Size]);
		if(!uiDataSize)
			return E_PACKET_ERROR::NonSize;

		m_ContData.resize(static_cast<ULONG32>(uiDataSize));
		::memcpy(&m_ContData[0], &_strData[nULONG64Size + nULONG64Size], static_cast<size_t>(uiDataSize));
		return E_PACKET_ERROR::NotError;
	}
	/*char* CPacket::GetData()
	{
	return m_ContData.empty() ? NULL : &m_ContData[0];
	}*/
#pragma endregion

#pragma region Packet Information
	ULONG64 const	CPacket::GetPacketType() const
	{
		return m_uiPacketType;
	}
	int const	CPacket::GetReturnDataSize() const
	{
		return ((sizeof(ULONG64) * 2) + GetDataSize());
	}

	bool		CPacket::CheckSize(unsigned int _iSize) const
	{
		//	패킷에 데이터가 없거나, 현재 빠져나간 데이터 + 빼갈 데이터의 양이 전체 데이터의 사이즈를 초과할 경우, 빼갈 데이터 양이 0일경우 false
		if(m_ContData.empty() || m_uiDataPos + _iSize > m_ContData.size() || 0 >= _iSize)		
			return false;

		return true;
	}

	bool		CPacket::CheckSize(ULONG64 _iSize) const
	{
		if(m_ContData.empty() || m_uiDataPos + _iSize > m_ContData.size() || 0 == _iSize)
			return false;

		return true;
	}

	int const	CPacket::GetDataSize() const
	{
		//return ( m_ContData.size() - static_cast<LONG>(m_uiDataPos) );
		return m_ContData.size();
	}

	void CPacket::Reserve(ULONG64 const reserve_size)
	{
		if( 0 < reserve_size )
		{
			m_ContData.reserve( static_cast<LONG>(reserve_size) );
		}
	}
#pragma endregion

#pragma region Operator >>
	CPacket&	CPacket::operator >>(bool&	_Data)
	{
		/*if( CheckSize(sizeof(bool)))
		{
			_Data = *reinterpret_cast<bool const*>(&m_ContData[static_cast<LONG>(m_uiDataPos)]);
			m_uiDataPos += sizeof(bool);
		}*/
		this->Pull(_Data);
		return *this;
	}
	CPacket&	CPacket::operator >>(int&	_Data)
	{
		/*if( CheckSize( sizeof( int ) ) )
		{
			_Data = *reinterpret_cast<int*>(&m_ContData[static_cast<LONG>(m_uiDataPos)]);
			m_uiDataPos += sizeof(int);
		}*/
		this->Pull(_Data);
		return *this;
	}
	CPacket& CPacket::operator >>(unsigned int&	_Data)
	{
		/*if(CheckSize(sizeof(unsigned int)))
		{
		_Data = *reinterpret_cast<unsigned int const *>(&m_ContData[static_cast<LONG>(m_uiDataPos)]);
		m_uiDataPos += sizeof(unsigned int);
		}*/
		this->Pull(_Data);
		return *this;
	}
	CPacket& CPacket::operator >>(short& _Data)
	{
		/*if(CheckSize(sizeof(short)))
		{
			_Data = *reinterpret_cast<short const *>(&m_ContData[static_cast<LONG>(m_uiDataPos)]);
			m_uiDataPos += sizeof(short);
		}*/
		this->Pull(_Data);
		return *this;
	}
	CPacket& CPacket::operator >>(unsigned short _Data)
	{
		/*if(CheckSize(sizeof(unsigned short)))
		{
			_Data = *reinterpret_cast<unsigned short const *>(&m_ContData[static_cast<LONG>(m_uiDataPos)]);
			m_uiDataPos += sizeof(unsigned short);
		}*/
		this->Pull(_Data);
		return *this;
	}
	CPacket& CPacket::operator >>(__int64&			_Data)
	{
		/*if(CheckSize(sizeof(__int64)))
		{
			_Data = *reinterpret_cast<__int64 const *>(&m_ContData[static_cast<LONG>(m_uiDataPos)]);
			m_uiDataPos += sizeof(__int64);
		}*/
		this->Pull(_Data);
		return *this;
	}
	CPacket& CPacket::operator >>(ULONG64&	_Data)
	{
		/*if(CheckSize(sizeof(ULONG64)))
		{
			_Data = *reinterpret_cast<ULONG64 const *>(&m_ContData[static_cast<LONG>(m_uiDataPos)] );
			m_uiDataPos += sizeof(ULONG64);
		}*/
		this->Pull(_Data);
		return *this;
	}
	CPacket& CPacket::operator >>(float& _Data)
	{
		/*if(CheckSize(sizeof(float)))
		{
			_Data = *reinterpret_cast<float const *>(&m_ContData[static_cast<LONG>(m_uiDataPos)]);
			m_uiDataPos += sizeof(float);
		}*/
		this->Pull(_Data);
		return *this;
	}
	CPacket& CPacket::operator >>(double& _Data)
	{
		/*if(CheckSize(sizeof(double)))
		{
			_Data = *reinterpret_cast<double const *>(&m_ContData[static_cast<LONG>(m_uiDataPos)]);
			m_uiDataPos += sizeof(double);
		}*/
		this->Pull(_Data);
		return *this;
	}
	CPacket& CPacket::operator >>(DWORD& _Data)
	{
		/*if(CheckSize(sizeof(DWORD)))
		{
			_Data = *reinterpret_cast<DWORD const *>(&m_ContData[static_cast<LONG>(m_uiDataPos)]);
			m_uiDataPos += sizeof(DWORD);
		}*/
		this->Pull(_Data);
		return *this;
	}
	CPacket& CPacket::operator >>(char&	_Data)
	{
		//if(CheckSize(sizeof(char)))
		//{
		//	//memcpy(&_Data, &m_ContData[static_cast<LONG>(m_uiDataPos)], sizeof(char));
		//	_Data = *reinterpret_cast<char const *>(&m_ContData[static_cast<LONG>(m_uiDataPos)]);
		//
		//	m_uiDataPos += sizeof(char);
		//}
		this->Pull(_Data);
		return *this;
	}
	CPacket& CPacket::operator >>(wchar_t& _Data)
	{
		//if(CheckSize(sizeof(wchar_t)))
		//{
		//	//memcpy(&_Data, &m_ContData[static_cast<LONG>(m_uiDataPos)], sizeof(wchar_t));
		//	_Data = *reinterpret_cast<wchar_t const *>(&m_ContData[static_cast<LONG>(m_uiDataPos)]);
		//
		//	m_uiDataPos += sizeof(wchar_t);
		//}
		this->Pull(_Data);
		return *this;
	}

	CPacket& CPacket::operator >>(char* pData)
	{
		/*if(CheckSize(sizeof(ULONG64)))
		{
			ULONG64 iStrSize = 0;
			*this >> iStrSize;

			if(CheckSize(iStrSize))
			{
				memcpy(pData, &m_ContData[static_cast<LONG>(m_uiDataPos)], static_cast<LONG>(iStrSize));
				pData[iStrSize] = '\0';
				m_uiDataPos += iStrSize;
			}
		}*/
		this->Pull(pData);
		return *this;
	}
	CPacket& CPacket::operator >>(wchar_t* pData)
	{
		//if(CheckSize(sizeof(ULONG64)))
		//{
		//	ULONG64	iStrSize = 0;
		//	*this >> iStrSize;
		//
		//	if(CheckSize(iStrSize * sizeof(wchar_t)))
		//	{
		//		//for( ULONG64 uiCount = 0; iStrSize > uiCount ; ++uiCount )
		//		for(ULONG64 unCount : range(static_cast<ULONG64>(0), iStrSize))
		//		{
		//			wchar_t uiData = 0;
		//			*this >> uiData;
		//			pData[unCount] =uiData;
		//		}
		//		pData[iStrSize] = L'\0';
		//
		//		m_uiDataPos += (iStrSize *sizeof(wchar_t));
		//	}				
		//}
		this->Pull(pData);
		return *this;
	}
	CPacket& CPacket::operator >>(std::string &strData)
	{
		/*if(CheckSize(sizeof(ULONG64)))
		{
			ULONG64	iStrSize = 0;
			*this >> iStrSize;

			strData.clear();
			strData.resize(static_cast<ULONG32>(iStrSize));
			if(CheckSize(iStrSize))
			{
				strData.assign(GetData() + static_cast<LONG>(m_uiDataPos), static_cast<LONG>(iStrSize));
				m_uiDataPos += iStrSize;
			}
		}*/
		this->Pull(strData);
		return *this;
	}
	CPacket& CPacket::operator >>(std::wstring & wstrData)
	{
		//if(CheckSize(sizeof(ULONG64)))
		//{
		//	ULONG64	iStrSize = 0;
		//	*this >> iStrSize;
		//
		//	wstrData.clear();
		//	wstrData.resize(static_cast<ULONG32>(iStrSize));
		//
		//	if (CheckSize(iStrSize * sizeof(wchar_t)))
		//	{
		//		//for (ULONG64 uiCount = 0; uiCount < iStrSize; ++uiCount)
		//		for(ULONG64 unCount : range(static_cast<ULONG64>(0), iStrSize))
		//		{
		//			wchar_t wcData = 0;
		//			*this >> wcData;
		//			wstrData[static_cast<ULONG32>(unCount)] = wcData;
		//		}
		//		wstrData[static_cast<ULONG32>(iStrSize)] = L'\0';
		//		m_uiDataPos += (iStrSize * sizeof(wchar_t));
		//	}
		//}

		this->Pull(wstrData);
		return *this;
	}
#pragma endregion

#pragma region operator <<
	CPacket& CPacket::operator <<(bool _Data)
	{
		//*this << static_cast<unsigned int>(pData);
		Append(_Data);
		return *this;
	}
	CPacket& CPacket::operator <<(int _Data)
	{
		//Append(&pData, sizeof(pData));
		Append(_Data);
		return *this;
	}
	CPacket& CPacket::operator <<(unsigned int _Data)
	{
		//Append(&pData, sizeof(pData));
		Append(_Data);
		return *this;
	}
	CPacket& CPacket::operator <<(short _Data)
	{
		//Append(&pData, sizeof(pData));
		Append(_Data);
		return *this;
	}
	CPacket& CPacket::operator <<(unsigned short _Data)
	{
		//Append(&pData, sizeof(pData));
		Append(_Data);
		return *this;
	}
	CPacket& CPacket::operator <<(__int64 _Data)
	{
		//Append(&pData, sizeof(pData));
		Append(_Data);
		return *this;
	}
	CPacket& CPacket::operator <<(ULONG64 _Data)
	{
		//Append(&pData, sizeof(pData));
		Append(_Data);
		return *this;
	}
	CPacket& CPacket::operator <<(float _Data)
	{
		//Append(&pData, sizeof(pData));
		Append(_Data);
		return *this;
	}
	CPacket& CPacket::operator <<(double _Data)
	{
		//Append(&pData, sizeof(pData));
		Append(_Data);
		return *this;
	}
	CPacket& CPacket::operator <<(DWORD& _Data)
	{
		//Append(&pData, sizeof(pData));
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
		/*ULONG64	uiLength = 0;
		for( const char *c = pData; '\0' != *c ; ++c)
			++uiLength;
		*this << uiLength;
		Append(pData, uiLength*sizeof(char));*/
		Append(pData);
		return *this;
	}
	CPacket& CPacket::operator <<(std::string const & _strData)
	{
		/*ULONG64 uiLength = static_cast<ULONG64>(pData.size());
		*this << uiLength;

		if (uiLength > 0)
		{
			Append(pData.c_str(), uiLength * sizeof(std::string::value_type));
		}*/
		Append(_strData);
		return *this;
	}
	CPacket& CPacket::operator <<(wchar_t* pData)
	{
		/*ULONG64 uiLength = 0;
		 for (const wchar_t* c = pData; *c != L'\0'; ++c)
		 ++uiLength;
		 *this << uiLength;

		 for (const wchar_t* c = pData; *c != L'\0'; ++c)
		 *this << static_cast<__int64>(*c);*/
		 Append(pData);
		return *this;
	}
	CPacket& CPacket::operator <<(std::wstring const & _wstrData)
	{
		/*ULONG64 uiLength = static_cast<ULONG64>(pData.size());
		*this << uiLength;

		if (uiLength > 0)
		{
		for (std::wstring::const_iterator c = pData.begin(); c != pData.end(); ++c)
		*this << static_cast<__int64>(*c);
		}*/
		Append(_wstrData);
		return *this;
	}
#pragma endregion
}