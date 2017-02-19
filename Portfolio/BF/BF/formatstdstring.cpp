#include "stdafx.h"
#include "formatstdstring.h"

#pragma warning(disable:4996)

namespace BF
{
	std::string format_arg_list(const char *fmt, va_list args)
	{
		if (!fmt) return "";
		int   result = -1, length = 256;
		char *buffer = nullptr;
		while (result == -1)
		{
			if (buffer) delete [] buffer;
			buffer = new char [length + 1];
			memset(buffer, 0, length + 1);
			result = _vsnprintf(buffer, length, fmt, args);
			length *= 2;
		}
		std::string s(buffer);
		delete [] buffer;
		return s;
	}
	std::wstring format_arg_list(const wchar_t *fmt, va_list args)
	{
		if (!fmt) return L"";
		int   result = -1, length = 256;
		wchar_t *buffer = nullptr;
		while (result == -1)
		{
			if (buffer) delete [] buffer;
			buffer = new wchar_t [length + 1];
			memset(buffer, 0, sizeof(wchar_t) *(length + 1));
			result = _vsnwprintf(buffer, length, fmt, args);
			length *= 2;
		}
		std::wstring s(buffer);
		delete [] buffer;
		return s;
	}

	std::string format(const char *fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		std::string s = format_arg_list(fmt, args);
		va_end(args);
		return s;
	}
	std::wstring format(const wchar_t *fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		std::wstring s = format_arg_list(fmt, args);
		va_end(args);
		return s;
	}

	//std::string format(std::string const &str, ...)
	//{
	//	va_list args;
	//	va_start(args, &str[0]);
	//	std::string s = format_arg_list(&str[0], args);
	//	va_end(args);
	//}
}