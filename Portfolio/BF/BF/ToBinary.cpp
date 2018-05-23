#include "stdafx.h"
#include "ToBinary.h"

namespace BF
{
	int CToBinary::ToIntBinary(char * _pstrValue)
	{
		int const nStrLen = strlen(_pstrValue);
		if (0 == nStrLen)
			return 0;

		return ToIntReturn<char*>(_pstrValue, nStrLen);
	}
	int CToBinary::ToIntBinary(wchar_t *_pwstrValue)
	{
		int const nwstrLen = wcslen(_pwstrValue);
		if (0 == nwstrLen)
			return 0;

		return ToIntReturn<wchar_t*>(_pwstrValue, nwstrLen);
	}
	int CToBinary::ToIntBinary(std::string const &_strValue)
	{
		if (_strValue.empty())
			return 0;

		return ToIntReturn<std::string>(_strValue, _strValue.size());
	}
	int CToBinary::ToIntBinary(std::wstring const &_wstrValue)
	{
		if (_wstrValue.empty())
			return 0;

		return ToIntReturn<std::wstring>(_wstrValue, _wstrValue.size());
	}

	__int64 CToBinary::ToInt64Binary(char *_pstrValue)
	{
		unsigned int const nstrLen = strlen(_pstrValue);
		if (0 == nstrLen)
			return 0;

		return ToInt64Return<char*>(_pstrValue, nstrLen);
	}
	__int64 CToBinary::ToInt64Binary(wchar_t *_pwstrValue)
	{
		unsigned int const nstrLen = wcslen(_pwstrValue);
		if (0 == nstrLen)
			return 0;
		return ToInt64Return<wchar_t *>(_pwstrValue, nstrLen);
	}
	__int64 CToBinary::ToInt64Binary(std::string const &_strValue)
	{
		if (_strValue.empty())
			return 0;

		return ToInt64Return<std::string>(_strValue, _strValue.size());
	}
	__int64 CToBinary::ToInt64Binary(std::wstring const &_wstrValue)
	{
		if (_wstrValue.empty())
			return 0;

		return ToInt64Return<std::wstring>(_wstrValue, _wstrValue.size());
	}
}