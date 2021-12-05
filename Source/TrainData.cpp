#include "TrainData.h"
int min(int& a, int& b) {
    return a < b ? a : b;
}
wstring Anh_Viet() {
    return L" /";
}
wstring Viet_Anh() {
    return L"";
}
int pos_token(wstring s) {
    int res = min(s.find(L" /"), s.find(L'\0'));
    return res == -1 ? s.length() : res;
}
string ws2s(const wstring& wstr)
{
    using convert_typeX = codecvt_utf8<wchar_t>;
    wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.to_bytes(wstr);
}
void buildDict(const char* name, bool A_V)
{
    wifstream wif(name);
    wif.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));
    // tao folder dictionary


    if (!A_V) {
        if (_mkdir(ANH_VIET) == -1)
            return;
    }
    else {
        if (_mkdir(VIET_ANH) == -1)
            return;
    }

    
    while (!wif.eof()) {
        wstring ws; 
        getline(wif, ws);
        int pos_sep = pos_token(ws);
        if (pos_sep == 0 || pos_sep > ws.length())
            continue;
 
       wstringstream ss;
       if(!A_V)
           ss << ANH_VIET << "/" << ws.substr(1, pos_sep - 1) << ".txt";
       else
           ss << VIET_ANH << "/" << ws.substr(1, pos_sep - 1) << ".txt";

       const wstring file_dir = ss.str();
        ofstream token(file_dir);
        if (token.fail())
            wcout << 1 << endl;
        wstring meaning;

        token << "Pronounce: " << ws2s(ws.substr(pos_sep)) << endl;
        do {
            getline(wif, meaning);
            token << ws2s(meaning) << endl;
        } while (meaning != L"");

    }


}

void train() {
    if (_mkdir("Dictionary") == -1)
        return;
    buildDict(FILE_ANH_VIET, 0);
    buildDict(FILE_VIET_ANH, 1);
}