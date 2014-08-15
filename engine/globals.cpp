#include "engine/globals.hpp"

std::wstring engine::cstr_to_wstr(const char *str)
{
	const size_t len = std::strlen(str);
	std::wstring wstr(len, L'#');
	mbstowcs(&wstr[0], str, len);
	return wstr;
}
