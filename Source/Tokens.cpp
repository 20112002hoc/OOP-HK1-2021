#include "Tokens.h"
#include "Tokens.h"
void Tokens::removeExtraSpace(wstring& s) {
	while (!s.empty() && s[0] == L' ')
		s.erase(0, 1);
	while (!s.empty() && s[s.length() - 1] == L' ')
		s.erase(s.length() - 1, 1);
	// Hoc 1  2   3
	if (s.empty())
		return;
	for (int i = 1;i < s.length() - 2; i++)
		if (s[i] == L' ' && s[i + 1] == L' ')
			s.erase(i--, 1);
}

void Tokens::toLower(wstring& s){
	transform(s.begin(), s.end(), s.begin(), tolower);
}
void Tokens::stringHandling(wstring& s) {
	Tokens::removeExtraSpace(s);
	Tokens::toLower(s);
}