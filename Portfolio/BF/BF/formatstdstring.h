#pragma once


#include <string>
#include <stdarg.h>

namespace BF
{

	std::string format_arg_list(const char *fmt, va_list args);
	std::string format(const char *fmt, ...);

	std::wstring format_arg_list(const wchar_t *fmt, va_list args);
	std::wstring format(const wchar_t *fms, ...);
}