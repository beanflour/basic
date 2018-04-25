#pragma once

#include <windows.h>
//#include <hash_map>
#include <map>
#include <list>
#include <vector>
#include "common.h"


namespace BF
{
	DEFTYPE_INT(D_Max_Key_pChar_SIze, 50)
	DEFTYPE_INT(D_SEND_LIMIT_SIZE, 999)	// 한번에 전송 가능한 데이터 size. 1024 - (ULONG64 * 3) - 1 SIZE.
		namespace E_PACKET_ERROR
	{
		enum Enum
		{
			Error,
			NonSize,
			Remnant,
			Complete,
		};
	}
#pragma pack(1)
	/*
		패킷타입은 따로 구분되어 관리된다. GetPacketType을 사용하여 얻어와 구분할 수 있다.
		데이터를 집어넣을때는 Append와 << 뺄 때는 Pull과 >>를 사용한다.
		직렬화된 데이터를 얻을때는 GetDivideCount를 사용하여 몇개로 분할되는지 확인하고.
		GetRTLocalSize()를 사용하여 전송할 크기를 구한다음 GetData를 사용하며 직렬화된 데이터얻어온다.
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
		//	packet 전체 초기화. 동적할당 해제는 하지 않는다.
		void Clear();

		//////////////////////////////////////////////////////////////////////////
		///	GetData															   ///
		//////////////////////////////////////////////////////////////////////////
		/*
		GetData는 최대 D_SEND_LIMIT_SIZE + (sizeof(ULONG64)*3)크기만큼 데이터를 얻어온다.
		Packet의 전체 사이즈가 D_SEND_LIMIT_SIZE를 넘을경우 최대 사이즈만큼으로 분할하여 return 한다.
		구조는 헤더3개와 실 데이터로 이루어져 있다.
		헤더1. PacketType
		헤더2. 전송 데이터 사이즈가 D_SEND_LIMIT_SIZE를 넘어갈 경우 조립하기 위한 패킷 번호다.
		0일경우 단독packet. 0 이상일 경우 분할데이타
		헤더3. 전송하는 데이터 사이즈.
		*/
		char*		GetData();
		/*
		현재 GetData()를 사용하면 갖고 오게 될 사이즈
		GetData()보다 앞에 사용되어야 한다.
		*/
		int const	GetRTLocalSize() const;

		// D_SEND_LIMIT_SIZE와 관계없이 전체 데이터를 직렬화하여 가져온다. 헤드 구조는 같다.
		char*		GetAllData();
		//	Packet에 들어간 전체 데이터 size를 받는다.
		int const	GetAllDataSize() const; 

		//	전송 가능한 위치 변경가능. 디폴트는 0
		bool		SetRTDataPos(ULONG64 const &_Pos = 0);
		//	현재까지 전송한 크기값.
		ULONG64		GetRTDataPos() const;
		//	들어있는 데이터들이 몇개로 분할하여 전송해야 하는지 반환한다.
		int const	GetDivideCount() const;
		//	현재까지 호출된 GetData()횟수. 이것이 GetDivideCount보다 작다면 GetData()를 더 호출해주어야 한다.
		int const	GetCallDataCount() const;
		//////////////////////////////////////////////////////////////////////////
		///	AddData															   ///
		//////////////////////////////////////////////////////////////////////////
		/*
		직렬화된 데이터를 집어넣는데 사용한다.
		BF::CPacket의 GetData나 GetAllData를 사용하여 얻어온 char*만 사용가능하다. 임의의 포인터를 넣으면 런타임 에러가 날 수 있다.
		return값이 E_PACKET_ERROR::Complete일 때에만 Pull이나 Append를 사용할 수 있다.
		*/
		E_PACKET_ERROR::Enum		AddData(char * _strData);


		//////////////////////////////////////////////////////////////////////////
		///	Get Packet information											   ///
		//////////////////////////////////////////////////////////////////////////
		//	패킷 타입을 변경한다.
		void			SetPacketType(ULONG64 const &_pType);
		//	패킷 타입을 가져온다.
		ULONG64	const	GetPacketType() const;
		//	전송할 남은 패킷 사이즈.
		int const		GetRTRemnantSize() const;
		//	직렬화할 전체 사이즈. GetAllData()를 사용하였을 때 갖고오게될 데이터의 사이즈와 같다.
		int const		GetAllRTDataSize() const;
	private:
		//	패킷에 데이터가 없거나, 현재 빠져나간 데이터 + 빼갈 데이터의 양이 전체 데이터의 사이즈를 초과할 경우, 빼갈 데이터 양이 0일경우 false
		bool		CheckSize(unsigned int _iSize) const;
		bool		CheckSize(ULONG64 _iSize) const;
		//	데이터 컨테이너의 capacity를 미리 확보한다.
		void		Reserve(ULONG64 const reserve_size);
		//	전체 데이터 크기를 분할하였을때의 총 데이터 크기를 반환한다. 분할되는 갯수 * 헤드사이즈만큼 추가된다.
		int const	GetDivideAllRTSize() const;

	public:
		//////////////////////////////////////////////////////////////////////////
		///	Append Data														   ///
		//////////////////////////////////////////////////////////////////////////
		//	Packet에 데이터를 집어넣는데 사용한다. Append(집어넣을 데이터)형이나 Packet << 집어넣을 데이터의 형태로 사용 가능하다.
		void Append(void const *pData, ULONG64 const iDataSize);

		void Append(int &_Data);
		void Append(int const &_Data);
		void Append(ULONG32 &_Data);
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
			if(mb_Lock)
				return;
			ULONG64 const uiSize = sizeof( T_INPUT );
			Append( (void const*)&pData, uiSize );
		}

		template<>
		void Append(CPacket const& input)
		{
			if(mb_Lock && this == &input)
			{
				return;
			}

			ULONG64 const data_size = input.GetAllDataSize();
			ULONG64 const in_size = data_size - input.mui_PullDataPos;
			if( in_size )
			{
				Reserve( GetAllDataSize() + in_size );

				Append( &input.mCont_Data.at( static_cast<unsigned int const>(input.mui_PullDataPos) ), in_size );
			}
		}

		template<typename T_VALUE>
		void Append(std::vector<T_VALUE> const &_ContData)
		{
			if(mb_Lock)
				return ;
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
			if(mb_Lock && _Data.empty())
				return;
			ULONG64 unSize = _Data.length();
			if(0 == unSize)
				return;
			this->Append(unSize);

			int const nDataSize = static_cast<LONG>(unSize) * sizeof(std::string::value_type);
			mCont_Data.resize(static_cast<ULONG32>(mui_RealAddSize) + nDataSize);
			::memcpy(&mCont_Data[static_cast<ULONG32>(mui_RealAddSize)], &_Data[0], nDataSize);
			mui_RealAddSize += nDataSize;
		}

		template<>
		void Append(std::wstring const &_Data)
		{
			if(mb_Lock && _Data.empty())
				return;
			ULONG64 unSize = _Data.length();
			this->Append(unSize);

			int const nDataSize = static_cast<LONG>(unSize) * sizeof(std::wstring::value_type);
			mCont_Data.resize(static_cast<ULONG32>(mui_RealAddSize) + nDataSize);
			::memcpy(&mCont_Data[static_cast<ULONG32>(mui_RealAddSize)], &_Data[0], nDataSize);
			mui_RealAddSize += nDataSize;
		}

		template<typename T_VALUE>
		void Append(std::list<T_VALUE> const &_ContData)
		{
			if (mb_Lock)
				return;
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
			if (mb_Lock)
				return;
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
		/*
			Packet에서 데이터를 빼는데 사용한다. Pull(받아올 데이터)형이나 Packet >> 받아올 데이터의 형태로 사용 가능하다.
			Pull의 경우 성공여부를 반환받을수 있으며 Append한 데이터의 순서대로 Pull해주어야 제대로된 값을 받아올 수 있다.
		*/
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
			if(mb_Lock)
				return false;
			ULONG64 const iOutPut_Size = sizeof( T_OUTPUT );
			return Pull(&_OutPut, iOutPut_Size);
		}

		template<typename T_VALUE>
		bool Pull(std::vector<T_VALUE> &_ContData)
		{
			ULONG64 unSize = 0;
			*this >> unSize;
			if(mb_Lock && 0 == unSize)
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
			if(mb_Lock && 0 == unSize)
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
			if(mb_Lock && 0 == unSize)
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
			if(mb_Lock && !CheckSize(sizeof(ULONG64)))
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
			if(mb_Lock && !CheckSize(sizeof(ULONG64)))
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
		ULONG64				mui_PacketType;		//	Packet 타입.
		ULONG64				mui_PullDataPos;	//	Pull한 데이터 위치
		ULONG64				mui_RTDataPos;		//	직렬화에 쓰이는 위치. ReturnData에서 다음 데이터가 들어갈 위치를 표시한다.
		ULONG64				mui_RTRealPos;		//	직렬화에 쓰인 현재 데이터 위치. mCont_Data에서 다음 데이터를 가져올 위치를 표시한다.
		ULONG64				mui_RealAddSize;	//	현재 들어간 실제 데이터 size. Append와 AddData에서 쓰인다
		CONT_STR			mCont_Data, ReturnData;
		bool				mb_Lock;			//	직렬화 작업중에 Append나 Pull을 할수 없도록 한다.
	};
#pragma pack()
}