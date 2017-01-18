#pragma once


#include <string>
#include <stdarg.h>

namespace BF
{

	std::string format_arg_list(const char *fmt, va_list args);

	std::string format(const char *fmt, ...);
	/*std::string format(std::string const &str, ...);*/
}