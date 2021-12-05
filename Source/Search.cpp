#include "Search.h"
void Search(const char* s, wstring& tokens) {
	Tokens::stringHandling(tokens);
	wstringstream dir;
	dir << s << '/' << tokens << ".txt";
	wifstream fin(dir.str());
	if (fin.fail()) {
		wcout << "Not found!!!" << endl;
		Searching::isFound = 0;
		return;
	}
	fin.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));
	wstringstream ss;
	ss << fin.rdbuf();
	wcout << ss.str();

	Searching::isFound = 1;
}
void Searching::EngToViet(wstring& tokens) {

	Search(ANH_VIET, tokens);
}
void Searching::VietToEng(wstring& tokens) {
	Search(VIET_ANH, tokens);
}