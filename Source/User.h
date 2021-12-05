#pragma once
#define _HAS_STD_BYTE 0
#include <string>
#include "Search.h"
#include <iomanip>
#include <filesystem>
#include "File.h"
using namespace std;
class User {
private:
	wstring _id;
public:
	User(const wstring& id);
	void search();
	friend void saveHistory(bool check, wstring s);
	void showHistory();
};