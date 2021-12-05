#pragma once
#define _HAS_STD_BYTE 0
#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>
#include "TrainData.h"
using namespace std;

class file {
    wstring name;
    FILETIME time;
public:
    bool operator<(file const& other) const;
    wstring getFileName();
    friend wostream& operator<<(wostream& os, file const& f);

    static vector<wstring> SortDate(vector<wstring> inputs);
    static wstring readAFile(const wstring&);
    file(WIN32_FIND_DATA const& d): time(d.ftCreationTime) {
        wstring temp(d.cFileName);
        name = temp;
    }

};
