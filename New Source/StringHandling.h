#pragma once
#define _HAS_STD_BYTE 0
#include<string>
#include <algorithm>
#include <codecvt>
using namespace std;

class Tokens {
public:
	static void removeExtraSpace(wstring& s);
	static void toLower(wstring& s);
	static void stringHandling(wstring& s);
	static string ws2s(const wstring& wstr);
};
