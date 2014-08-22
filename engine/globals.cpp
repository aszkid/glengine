#include "engine/globals.hpp"

std::wstring engine::cstr_to_wstr(const std::string str)
{
	const size_t len = str.size();
	std::wstring wstr(len, L'#');
	mbstowcs(&wstr[0], &str[0], len);
	return wstr;
	
	/*std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
	return conv.from_bytes(str);*/
	
	/*std::wstring wstr;
	wstr.assign(str.begin(), str.end());
	return wstr;*/
}
