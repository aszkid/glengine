#include "engine/globals.hpp"

/*#include <locale>
#include <codecvt>// - just VC++ and maybe clang++*/

#include <boost/locale.hpp>
#include <locale>

std::wstring engine::cstr_to_wstr(const std::string str)
{
	/*const size_t len = str.size();
	std::wstring wstr(len, L'#');
	mbstowcs(&wstr[0], &str[0], len);
	return wstr;*/
	
	/*std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	return conv.from_bytes(str);*/
	
	/*std::wstring wstr;
	wstr.assign(str.begin(), str.end());
	return wstr;*/
	
	return boost::locale::conv::utf_to_utf<wchar_t>(str);
}
