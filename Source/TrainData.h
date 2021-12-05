#pragma once
#define _HAS_STD_BYTE 0
#include<string>
#include <fstream>
#include <codecvt>
#include <iostream>
#include <sstream>
#include<direct.h>
using namespace std;

#define FILE_ANH_VIET "Data/Anh-Viet.txt"
#define FILE_VIET_ANH "Data/Viet-Anh.txt"
#define ANH_VIET "Dictionary/Anh-Viet"
#define VIET_ANH "Dictionary/Viet-Anh"
void train();
string ws2s(const wstring& wstr);