#include "FileHandling.h"
bool file::operator<(file const& other) const {
    return CompareFileTime(&time, &other.time) == 1;
}

wostream& operator<<(std::wostream& os, file const& f) {
    SYSTEMTIME st;
    FileTimeToSystemTime(&f.time, &st);
    return os << setw(20) << f.name << L"\t" << st.wHour << L":" << st.wMinute << L":" << st.wSecond << L" " << st.wYear << L"/" << st.wMonth << L"/" << st.wDay;
}

wstring file::getFileName() {
    return this->name;
}
vector<wstring> file::SortDate(vector<wstring> inputs) {
    vector<file> files;

    transform(inputs.begin(), inputs.end(),
        back_inserter(files),
        [](const wstring& fname) {
            WIN32_FIND_DATA d;
            HANDLE h = FindFirstFile(fname.c_str(), &d);
            FindClose(h);
            return d;
        }
    );

    std::sort(files.begin(), files.end());
    vector<wstring> res;
    for (int i = 0; i < files.size(); i++)
    {
        res.push_back(files[i].getFileName());
    }
    return res;
}

wstring file::readAFile(const wstring& dir) {
    wifstream fin(dir);
    if (fin.fail())
        return L"";
    fin.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));
    wstringstream ss;
    ss << fin.rdbuf();

    return ss.str();

}