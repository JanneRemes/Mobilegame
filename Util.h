
#ifndef UTIL_H
#define UTIL_H

#include <cstdarg>
#include <string>
#include <vector>

struct Util
{
	static std::string Format(const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		int length = vsnprintf(nullptr, 0, format, args);
		std::vector<char> buffer(length + 1);

		va_start(args, format);
		vsnprintf(buffer.data(), buffer.size(), format, args);
		return std::string(buffer.data());
	}
};

#endif
