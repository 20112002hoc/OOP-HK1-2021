#pragma once
#define _HAS_STD_BYTE 0
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

class Tokens {
public:
	static void removeExtraSpace(wstring& s);
	static void toLower(wstring& s);
	static void stringHandling(wstring& s);

};