#pragma once
#define _HAS_STD_BYTE 0
#include <string>
#include "Search.h"
#include <iomanip>
#include <filesystem>
#include <fstream>
#include <direct.h>
#include "FileHandling.h"
#include "StringHandling.h"
using namespace std;
class User {
private:
	wstring _id;
public:
	User() {
		_id = L"NULL";
	}
	User(int) {
		_id = L"NULL";
	}
	wstring id() {
		return _id;
	};
	User(const wstring& id);
	void setId(const wstring& s);
	wstring search(wstring s, int check);
	friend void saveHistory(bool check, wstring s);
	void showHistory();
};