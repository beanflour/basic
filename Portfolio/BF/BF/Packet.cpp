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
		Clear();
	}
	void CPacket::Clear()
	{
		m_uiPacketType = 0;
		m_uiDataPos = 0;
		m_ContData.clear();
		ReturnData.clear();
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
	//void CPacket::Append(unsigned int & _Data)
	//{
	//	int const nPrevSize = m_ContData.size();
	//	m_ContData.resize(nPrevSize + sizeof(unsigned int));
	//	memcpy(&m_ContData[nPrevSize], &_Data, sizeof(unsigned int));
	//}
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

	void	CPacket::Append(void const *pData, ULONG64 const iDataSize)
	{
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
		if(CheckSize(sizeof(int)))
		{
			_Data = *reinterpret_cast<int const *>(&m_ContData[static_cast<LONG>(m_uiDataPos)]);
			m_uiDataPos += sizeof(int);
		}

		return true;
	}
	bool CPacket::Pull(ULONG32 &_Data)
	{
		if(CheckSize(sizeof(ULONG32)))
		{
			_Data = *reinterpret_cast<ULONG32 const *>(&m_ContData[static_cast<LONG>(m_uiDataPos)] );
			m_uiDataPos += sizeof(ULONG32);
		}
		return true;
	}
	bool CPacket::Pull(short &_Data)
	{
		if(CheckSize(sizeof(short)))
		{
			_Data = *reinterpret_cast<short const *>(&m_ContData[static_cast<LONG>(m_uiDataPos)]);
			m_uiDataPos += sizeof(short);
		}
		return true;
	}
	bool CPacket::Pull(__int64 &_Data)
	{
		if(CheckSize(sizeof(__int64)))
		{
			_Data = *reinterpret_cast<__int64 const *>(&m_ContData[static_cast<LONG>(m_uiDataPos)]);
			m_uiDataPos += sizeof(__int64);
		}
		return true;
	}
	bool CPacket::Pull(ULONG64 &_Data)
	{
		if(CheckSize(sizeof(ULONG64)))
		{
			_Data = *reinterpret_cast<ULONG64 const *>(&m_ContData[static_cast<LONG>(m_uiDataPos)] );
			m_uiDataPos += sizeof(ULONG64);
		}
		return true;
	}
	bool CPacket::Pull(float &_Data)
	{
		if(CheckSize(sizeof(float)))
		{
			_Data = *reinterpret_cast<float const *>(&m_ContData[static_cast<LONG>(m_uiDataPos)]);
			m_uiDataPos += sizeof(float);
		}
		return true;
	}
	bool CPacket::Pull(double &_Data)
	{
		if(CheckSize(sizeof(double)))
		{
			_Data = *reinterpret_cast<double const *>(&m_ContData[static_cast<LONG>(m_uiDataPos)]);
			m_uiDataPos += sizeof(double);
		}
		return true;
	}
	bool CPacket::Pull(DWORD &_Data)
	{
		if(CheckSize(sizeof(DWORD)))
		{
			_Data = *reinterpret_cast<DWORD const *>(&m_ContData[static_cast<LONG>(m_uiDataPos)]);
			m_uiDataPos += sizeof(DWORD);
		}
		return true;
	}
	bool CPacket::Pull(char &_Data)
	{
		if(CheckSize(sizeof(char)))
		{
			_Data = *reinterpret_cast<char const *>(&m_ContData[static_cast<LONG>(m_uiDataPos)]);

			m_uiDataPos += sizeof(char);
		}
		return true;
	}
	bool CPacket::Pull(wchar_t &_Data)
	{
		if(CheckSize(sizeof(wchar_t)))
		{
			_Data = *reinterpret_cast<wchar_t const *>(&m_ContData[static_cast<LONG>(m_uiDataPos)]);

			m_uiDataPos += sizeof(wchar_t);
		}
		return true;
	}

	bool	CPacket::Pull(char *pData, ULONG64 const iDataPullSize)
	{
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