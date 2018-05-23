#pragma once

#include <string>

namespace BF
{
	class CToBinary
	{
	public:
		static int ToIntBinary(char * _pstrValue);
		static int ToIntBinary(wchar_t *_pwstrValue);
		static int ToIntBinary(std::string const &_strValue);
		static int ToIntBinary(std::wstring const &_wstrValue);

		static __int64 ToInt64Binary(char *_pstrValue);
		static __int64 ToInt64Binary(wchar_t *_pwstrValue);
		static __int64 ToInt64Binary(std::string const &_strValue);
		static __int64 ToInt64Binary(std::wstring const &_wstrValue);
	private:
		template <typename T>
		static int ToIntReturn(T _pstr, int const &nSize)
		{
			int nReturn = 0;
			for (int nIndex = nSize - 1, nMulti = 1; 0 <= nIndex; --nIndex, nMulti *= 2)
			{
				if ('1' == _pstr[nIndex])
				{
					nReturn += nMulti;
				}
				else if ('0' != _pstr[nIndex])
				{
					return 0;
				}
			}

			return nReturn;
		}
		template <typename T>
		static __int64 ToInt64Return(T _pstr, unsigned int const &nSize)
		{
			__int64 nReturn = 0;
			__int64 nMulti = 1;
			for (unsigned int nIndex = nSize - 1; 0 <= nIndex; --nIndex, nMulti *= 2)
			{
				if ('1' == _pstr[nIndex])
				{
					nReturn += nMulti;
				}
				else if ('0' != _pstr[nIndex])
				{
					return 0;
				}
			}

			return nReturn;
		}
	};
}