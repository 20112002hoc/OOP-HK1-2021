#include "StringHandling.h"

string Tokens::ws2s(const wstring& wstr)
{
	using convert_typeX = codecvt_utf8<wchar_t>;
	wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.to_bytes(wstr);
}

void Tokens::removeExtraSpace(wstring& s) {
	while (s[0] == ' ') s.erase(0, 1);
	if (!s.empty()) {
		int len = s.length();
		if (len < 1) return;
		while (s[len - 1] == ' ') {
			s.erase(len - 1, 1); len--;
		}

		int i = 1;
		while (i < len - 1) {
			if (s[i] == ' ' && s[i + 1] == ' ') {
				s.erase(i, 1); len--;
			}
			else i++;
		}
	}
}



void Tokens::toLower(wstring& s) {
	transform(s.begin(), s.end(), s.begin(), tolower);
}
void Tokens::stringHandling(wstring& s) {
	Tokens::removeExtraSpace(s);

	Tokens::toLower(s);
}