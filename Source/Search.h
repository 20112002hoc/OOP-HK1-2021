#pragma once
#define _HAS_STD_BYTE 0
#include "TrainData.h"
#include <iostream>
#include <string>
#include "Tokens.h"
using namespace std;

class Searching {
public:
	friend void Search(const char* A_V_V_A, wstring& s);
	void VietToEng(wstring& s);
	void EngToViet(wstring& s);
	static int isFound;
};