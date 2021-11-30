#pragma once
#include "TrainData.h"
#include <iostream>
#include <string>
using namespace std;
class Searching {
public:
	friend void Search(const char* A_V_V_A,const wstring& s);
	void VietToEng(const wstring& s);
	void EngToViet(const wstring& s);
};