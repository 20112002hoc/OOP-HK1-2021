#include "Search.h"
void Search(const char* s, const wstring& tokens) {
	wstringstream dir;
	dir << s << '/' << tokens << ".txt";
	wifstream fin(dir.str());
	if (fin.fail()) {
		wcout << "Not found!!!" << endl;
		return;
	}
	fin.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));
	wstringstream ss;
	ss << fin.rdbuf();
	wcout << ss.str();
}
void Searching::EngToViet(const wstring& tokens) {

	Search(ANH_VIET, tokens);
}
void Searching::VietToEng(const wstring& tokens) {
	Search(VIET_ANH, tokens);
}