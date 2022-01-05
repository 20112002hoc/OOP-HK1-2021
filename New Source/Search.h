#pragma once
#define _HAS_STD_BYTE 0
#define FILE_ANH_VIET "Data/Anh-Viet.txt"
#define FILE_VIET_ANH "Data/Viet-Anh.txt"
#define ANH_VIET "Dictionary/Anh-Viet"
#define VIET_ANH "Dictionary/Viet-Anh"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "StringHandling.h"
using namespace std;

class Searching {
public:
	wstring Search(const char* A_V_V_A, wstring& s);
	wstring VietToEng(wstring& s);
	wstring EngToViet(wstring& s);

	int isFound;
};