#include "Search.h"

wstring Searching::Search(const char* s, wstring& tokens) {
	Tokens::stringHandling(tokens);
	wstringstream dir;
	dir << s << '/' << tokens << ".txt";
	wifstream fin(dir.str());
	if (fin.fail()) {
		isFound = 0;
		return L"NULL";
	}
	fin.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));
	wstringstream ss;
	ss << fin.rdbuf();


	isFound = 1;
	return ss.str();
}
wstring Searching::EngToViet(wstring& tokens) {

	return Search(ANH_VIET, tokens);
}
wstring Searching::VietToEng(wstring& tokens) {
	return Search(VIET_ANH, tokens);
}