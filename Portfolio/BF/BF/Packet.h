#pragma once

#include <hash_map>
#include <list>
#include <windows.h>
#include "common.h"

namespace BF
{
	DEFTYPE_INT(D_Max_Key_pChar_SIze, 50)

		namespace E_PACKET_ERROR
	{
		enum Enum
		{
			NotError,
			NonSize,
		};
	}
#pragma pack(1)
	/*
		패킷타입은 따로 구분되어 관리된다. GetPacketType을 사용하여 얻어와 구분할 수 있다.
		데이터를 집어넣을때는 Append와 << 뺄 때는 Pull과 >>를 사용한다.
		직렬화된 데이터를 얻을때는 GetData를 사용하며 직렬화된 데이터의 총 길이는 GetReturnDataSize를 사용한다.
		패킷을 사용하여 직렬화된 데이터를 패킷에 집어넣을 때에는 AddData를 사용한다.
	*/
	class CPacket
	{
		typedef std::vector<char>	CONT_STR;
	public:
		CPacket(void);
		CPacket(int const &_iPacketType);
		CPacket(CPacket const &_Packet);
		~CPacket(void);

		//////////////////////////////////////////////////////////////////////////
		///	Clear Packet													   ///
		//////////////////////////////////////////////////////////////////////////
		void Clear();

		//////////////////////////////////////////////////////////////////////////
		///	GetData															   ///
		//////////////////////////////////////////////////////////////////////////
		char*		GetData();

		//////////////////////////////////////////////////////////////////////////
		///	Get Packet information											   ///
		//////////////////////////////////////////////////////////////////////////
		ULONG64	const	GetPacketType() const;
		int const		GetReturnDataSize() const;
		E_PACKET_ERROR::Enum		AddData(char * _strData);
	private:
		bool		CheckSize(unsigned int _iSize) const;
		bool		CheckSize(ULONG64 _iSize) const;
		int const	GetDataSize() const;
		void		Reserve(ULONG64 const reserve_size);

	public:
		//////////////////////////////////////////////////////////////////////////
		///	Append Data														   ///
		//////////////////////////////////////////////////////////////////////////
		void Append(void const *pData, ULONG64 const iDataSize);

		void Append(int &_Data);
		void Append(int const &_Data);
		void Append(unsigned int &_Data);
		void Append(short &_Data);
		void Append(__int64 &_Data);
		void Append(ULONG64 &_Data);
		void Append(ULONG64 const &_Data);
		void Append(float &_Data);
		void Append(double &_Data);
		void Append(DWORD &_Data);
		void Append(char &_Data);
		void Append(char const &_Data);
		void Append(wchar_t &_Data);
		void Append(wchar_t const &_Data);

		void Append(char const *pData);
		void Append(char *pData);
		void Append(wchar_t const *pData);
		void Append(wchar_t *pData);

		template< typename T_INPUT >
		void Append( T_INPUT const &pData)
		{
			ULONG64 const uiSize = sizeof( T_INPUT );
			Append( (void const*)&pData, uiSize );
		}

		template<>
		void Append(CPacket const& input)
		{
			if( this == &input)
			{
				return;
			}

			ULONG64 const data_size = input.GetDataSize();
			ULONG64 const in_size = data_size - input.m_uiDataPos;
			if( in_size )
			{
				Reserve( GetDataSize() + in_size );

				Append( &input.m_ContData.at( static_cast<unsigned int const>(input.m_uiDataPos) ), in_size );
			}
		}

		template<typename T_VALUE>
		void Append(std::vector<T_VALUE> const &_ContData)
		{
			ULONG64 unSize = _ContData.size();
			this->Append(unSize);
			for(auto _data : _ContData)
			{
				*this << _data;
			}
		}

		template<>
		void Append(std::string const & _Data)
		{
			if(_Data.empty())
				return;
			ULONG64 unSize = _Data.length();
			if(0 == unSize)
				return;
			this->Append(unSize);

			int const nPrevSize = m_ContData.size();
			int const nDataSize = static_cast<LONG>(unSize) * sizeof(std::string::value_type);
			m_ContData.resize(nPrevSize + nDataSize);
			::memcpy(&m_ContData[nPrevSize], &_Data[0], nDataSize);			
		}

		template<>
		void Append(std::wstring const &_Data)
		{
			if(_Data.empty())
				return;
			ULONG64 unSize = _Data.length();
			this->Append(unSize);

			int const nPrevSize = m_ContData.size();
			int const nDataSize = static_cast<LONG>(unSize) * sizeof(std::wstring::value_type);
			m_ContData.resize(nPrevSize + nDataSize);
			::memcpy(&m_ContData[nPrevSize], &_Data[0], nDataSize);
		}

		template<typename T_VALUE>
		void Append(std::list<T_VALUE> const &_ContData)
		{
			ULONG64 unSize = _ContData.size();
			*this << unSize;

			for(auto _data : _ContData)
			{
				*this << _data;
			}
		}

		template<typename T_KEY, typename T_VALUE>
		void Append(std::map<T_KEY, T_VALUE> const &_MapData)
		{
			ULONG64 unSize = _MapData.size();
			*this << unSize;

			for(auto Data : _MapData)
			{
				*this << Data.first;
				*this << Data.second;
			}
		}

		//////////////////////////////////////////////////////////////////////////
		///	Pull Data														   ///
		//////////////////////////////////////////////////////////////////////////
		bool Pull(void *pData, ULONG64 const iDataSize);

		bool Pull(int &_Data);
		bool Pull(ULONG32 &_Data);
		bool Pull(short &_Data);
		bool Pull(__int64 &_Data);
		bool Pull(ULONG64 &_Data);
		bool Pull(float &_Data);
		bool Pull(double &_Data);
		bool Pull(DWORD &_Data);
		bool Pull(char &_Data);
		bool Pull(wchar_t &_Data);

		/*
			char*와 wchar_t형으로 데이터를 받는것은 주의해야 한다.
			미리 빼올 용량 이상의 데이터를 확보하고 있다는 확신이 있어야 함.
			아니면 string과 wstring을 사용하자.
		*/
		bool Pull(char *pData, ULONG64 const iDataMaxSize);
		bool Pull(char *pData);
		bool Pull(wchar_t *pData, ULONG64 const iDataMaxSize);
		bool Pull(wchar_t *pData);

		template < typename T_OUTPUT >
		bool Pull(T_OUTPUT &_OutPut)
		{
			ULONG64 const iOutPut_Size = sizeof( T_OUTPUT );
			return Pull(&_OutPut, iOutPut_Size);
		}

		template<typename T_VALUE>
		bool Pull(std::vector<T_VALUE> &_ContData)
		{
			ULONG64 unSize = 0;
			*this >> unSize;
			if(0 == unSize)
				return false;

			_ContData.resize(static_cast<ULONG32>(unSize));
			for(int unIndex = 0; unIndex < static_cast<int>(unSize); unIndex++)
			{
				std::vector<T_VALUE>::value_type tempValue;
				*this >> tempValue;
				_ContData[unIndex] = tempValue;
			}
			return true;
		}

		template<typename T_VALUE>
		bool Pull(std::list<T_VALUE> &_ContData)
		{
			ULONG64 unSize = 0;
			*this >> unSize;
			if(0 == unSize)
				return false;

			_ContData.clear();
			for(int unIndex : range(0, static_cast<int>(unSize)))
			{
				std::list<T_VALUE>::value_type tempValue;
				*this >> tempValue;
				_ContData.push_back(tempValue);
			}
			return true;
		}

		template<typename T_KEY, typename T_VALUE>
		bool Pull(std::map<T_KEY, T_VALUE> &_MapData)
		{
			ULONG64 unSize = 0;
			*this >> unSize;
			if(0 == unSize)
				return false;

			_MapData.clear();
			for(ULONG64 unCount : range(static_cast<ULONG64>(0), unSize))
			{
				T_KEY		key;		//	T_KEY가 char*일 때의 대처방법이 필요함. 그냥 이대로 진행하면 메모리 할당이 되지 않은 포인터에 값을 집어넣게 됨.
				T_VALUE		value;

				*this >> key;
				*this >> value;
				_MapData.insert(std::map<T_KEY,T_VALUE>::value_type(key, value));
			}
			return true;
		}

		template<>
		bool Pull(std::string &_str)
		{
			if(!CheckSize(sizeof(ULONG64)))
				return false;

			_str.clear();
			ULONG64 unLength = 0;
			*this >> unLength;
			if(!CheckSize(unLength))
				return false;
			_str.resize(static_cast<ULONG32>(unLength));

			return this->Pull(&_str[0], unLength);
		}

		template<>
		bool Pull(std::wstring &_str)
		{
			if(!CheckSize(sizeof(ULONG64)))
				return false;

			_str.clear();
			ULONG64 unLength = 0;
			*this >> unLength;
			if(0 == unLength)
				return false;
			_str.resize(static_cast<ULONG32>(unLength));

			return this->Pull(&_str[0], unLength);
		}

		//////////////////////////////////////////////////////////////////////////
		///	Operator >>														   ///
		//////////////////////////////////////////////////////////////////////////
		CPacket& operator >>(bool&					_Data);
		CPacket& operator >>(int&					_Data);
		CPacket& operator >>(unsigned int&			_Data);
		CPacket& operator >>(short&					_Data);
		CPacket& operator >>(unsigned short			_Data);
		CPacket& operator >>(__int64&				_Data);
		CPacket& operator >>(ULONG64&				_Data);
		CPacket& operator >>(float&					_Data);
		CPacket& operator >>(double&				_Data);
		CPacket& operator >>(DWORD&					_Data);
		CPacket& operator >>(char&					_Data);
		CPacket& operator >>(wchar_t&				_Data);
		CPacket& operator >>(char*					pData);
		CPacket& operator >>(std::string&			pData);
		CPacket& operator >>(wchar_t*				pData);
		CPacket& operator >>(std::wstring&			pData);

		//////////////////////////////////////////////////////////////////////////
		///	Operator <<														   ///
		//////////////////////////////////////////////////////////////////////////
		CPacket& operator <<(bool					_Data);
		CPacket& operator <<(int					_Data);
		CPacket& operator <<(unsigned int			_Data);
		CPacket& operator <<(short					_Data);
		CPacket& operator <<(unsigned short			_Data);
		CPacket& operator <<(__int64				_Data);
		CPacket& operator <<(ULONG64				_Data);
		CPacket& operator <<(float					_Data);
		CPacket& operator <<(double					_Data);
		CPacket& operator <<(DWORD&					_Data);
		CPacket& operator <<(char&					_Data);
		CPacket& operator <<(wchar_t&				_Data);
		CPacket& operator <<(char*					pData);
		CPacket& operator <<(std::string const&		pData);
		CPacket& operator <<(wchar_t*				pData);
		CPacket& operator <<(const std::wstring&	pData);

	private:
		ULONG64				m_uiPacketType;
		ULONG64				m_uiDataPos;
		CONT_STR			m_ContData, ReturnData;
	};
#pragma pack()
}