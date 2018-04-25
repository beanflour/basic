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
	DEFTYPE_INT(D_SEND_LIMIT_SIZE, 999)	// �ѹ��� ���� ������ ������ size. 1024 - (ULONG64 * 3) - 1 SIZE.
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
		��ŶŸ���� ���� ���еǾ� �����ȴ�. GetPacketType�� ����Ͽ� ���� ������ �� �ִ�.
		�����͸� ����������� Append�� << �� ���� Pull�� >>�� ����Ѵ�.
		����ȭ�� �����͸� �������� GetDivideCount�� ����Ͽ� ��� ���ҵǴ��� Ȯ���ϰ�.
		GetRTLocalSize()�� ����Ͽ� ������ ũ�⸦ ���Ѵ��� GetData�� ����ϸ� ����ȭ�� �����;��´�.
		��Ŷ�� ����Ͽ� ����ȭ�� �����͸� ��Ŷ�� ������� ������ AddData�� ����Ѵ�.
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
		//	packet ��ü �ʱ�ȭ. �����Ҵ� ������ ���� �ʴ´�.
		void Clear();

		//////////////////////////////////////////////////////////////////////////
		///	GetData															   ///
		//////////////////////////////////////////////////////////////////////////
		/*
		GetData�� �ִ� D_SEND_LIMIT_SIZE + (sizeof(ULONG64)*3)ũ�⸸ŭ �����͸� ���´�.
		Packet�� ��ü ����� D_SEND_LIMIT_SIZE�� ������� �ִ� �����ŭ���� �����Ͽ� return �Ѵ�.
		������ ���3���� �� �����ͷ� �̷���� �ִ�.
		���1. PacketType
		���2. ���� ������ ����� D_SEND_LIMIT_SIZE�� �Ѿ ��� �����ϱ� ���� ��Ŷ ��ȣ��.
		0�ϰ�� �ܵ�packet. 0 �̻��� ��� ���ҵ���Ÿ
		���3. �����ϴ� ������ ������.
		*/
		char*		GetData();
		/*
		���� GetData()�� ����ϸ� ���� ���� �� ������
		GetData()���� �տ� ���Ǿ�� �Ѵ�.
		*/
		int const	GetRTLocalSize() const;

		// D_SEND_LIMIT_SIZE�� ������� ��ü �����͸� ����ȭ�Ͽ� �����´�. ��� ������ ����.
		char*		GetAllData();
		//	Packet�� �� ��ü ������ size�� �޴´�.
		int const	GetAllDataSize() const; 

		//	���� ������ ��ġ ���氡��. ����Ʈ�� 0
		bool		SetRTDataPos(ULONG64 const &_Pos = 0);
		//	������� ������ ũ�Ⱚ.
		ULONG64		GetRTDataPos() const;
		//	����ִ� �����͵��� ��� �����Ͽ� �����ؾ� �ϴ��� ��ȯ�Ѵ�.
		int const	GetDivideCount() const;
		//	������� ȣ��� GetData()Ƚ��. �̰��� GetDivideCount���� �۴ٸ� GetData()�� �� ȣ�����־�� �Ѵ�.
		int const	GetCallDataCount() const;
		//////////////////////////////////////////////////////////////////////////
		///	AddData															   ///
		//////////////////////////////////////////////////////////////////////////
		/*
		����ȭ�� �����͸� ����ִµ� ����Ѵ�.
		BF::CPacket�� GetData�� GetAllData�� ����Ͽ� ���� char*�� ��밡���ϴ�. ������ �����͸� ������ ��Ÿ�� ������ �� �� �ִ�.
		return���� E_PACKET_ERROR::Complete�� ������ Pull�̳� Append�� ����� �� �ִ�.
		*/
		E_PACKET_ERROR::Enum		AddData(char * _strData);


		//////////////////////////////////////////////////////////////////////////
		///	Get Packet information											   ///
		//////////////////////////////////////////////////////////////////////////
		//	��Ŷ Ÿ���� �����Ѵ�.
		void			SetPacketType(ULONG64 const &_pType);
		//	��Ŷ Ÿ���� �����´�.
		ULONG64	const	GetPacketType() const;
		//	������ ���� ��Ŷ ������.
		int const		GetRTRemnantSize() const;
		//	����ȭ�� ��ü ������. GetAllData()�� ����Ͽ��� �� ������Ե� �������� ������� ����.
		int const		GetAllRTDataSize() const;
	private:
		//	��Ŷ�� �����Ͱ� ���ų�, ���� �������� ������ + ���� �������� ���� ��ü �������� ����� �ʰ��� ���, ���� ������ ���� 0�ϰ�� false
		bool		CheckSize(unsigned int _iSize) const;
		bool		CheckSize(ULONG64 _iSize) const;
		//	������ �����̳��� capacity�� �̸� Ȯ���Ѵ�.
		void		Reserve(ULONG64 const reserve_size);
		//	��ü ������ ũ�⸦ �����Ͽ������� �� ������ ũ�⸦ ��ȯ�Ѵ�. ���ҵǴ� ���� * �������ŭ �߰��ȴ�.
		int const	GetDivideAllRTSize() const;

	public:
		//////////////////////////////////////////////////////////////////////////
		///	Append Data														   ///
		//////////////////////////////////////////////////////////////////////////
		//	Packet�� �����͸� ����ִµ� ����Ѵ�. Append(������� ������)���̳� Packet << ������� �������� ���·� ��� �����ϴ�.
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
			Packet���� �����͸� ���µ� ����Ѵ�. Pull(�޾ƿ� ������)���̳� Packet >> �޾ƿ� �������� ���·� ��� �����ϴ�.
			Pull�� ��� �������θ� ��ȯ������ ������ Append�� �������� ������� Pull���־�� ����ε� ���� �޾ƿ� �� �ִ�.
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
			char*�� wchar_t������ �����͸� �޴°��� �����ؾ� �Ѵ�.
			�̸� ���� �뷮 �̻��� �����͸� Ȯ���ϰ� �ִٴ� Ȯ���� �־�� ��.
			�ƴϸ� string�� wstring�� �������.
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
				T_KEY		key;		//	T_KEY�� char*�� ���� ��ó����� �ʿ���. �׳� �̴�� �����ϸ� �޸� �Ҵ��� ���� ���� �����Ϳ� ���� ����ְ� ��.
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
		ULONG64				mui_PacketType;		//	Packet Ÿ��.
		ULONG64				mui_PullDataPos;	//	Pull�� ������ ��ġ
		ULONG64				mui_RTDataPos;		//	����ȭ�� ���̴� ��ġ. ReturnData���� ���� �����Ͱ� �� ��ġ�� ǥ���Ѵ�.
		ULONG64				mui_RTRealPos;		//	����ȭ�� ���� ���� ������ ��ġ. mCont_Data���� ���� �����͸� ������ ��ġ�� ǥ���Ѵ�.
		ULONG64				mui_RealAddSize;	//	���� �� ���� ������ size. Append�� AddData���� ���δ�
		CONT_STR			mCont_Data, ReturnData;
		bool				mb_Lock;			//	����ȭ �۾��߿� Append�� Pull�� �Ҽ� ������ �Ѵ�.
	};
#pragma pack()
}