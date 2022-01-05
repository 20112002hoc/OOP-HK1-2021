#include "User.h"

User::User(const wstring& s) {
	_id = s;
	_mkdir("Users");
	wstring dir = L"Users/" + s;
	_mkdir(Tokens::ws2s(dir).c_str());
	dir += L"/History";
	_mkdir(Tokens::ws2s(dir).c_str());
	dir.erase(dir.length() - 7);
	dir += L"ImportantWords";
	_mkdir(Tokens::ws2s(dir).c_str());
}

void saveHistory(wstring id, bool check, wstring dir) {
	wstring checkMax = L"Users/" + id + L"/History";
	vector<wstring> files;

	for (auto& p : filesystem::recursive_directory_iterator(Tokens::ws2s(checkMax).c_str()))
	{
		wstring temp = filesystem::absolute(p.path()).wstring();
		files.push_back(temp);
	}
	if (files.size() >= 5) {
		files = file::SortDate(files);
		wstring lastFile = checkMax + L"/" + files[files.size() - 1];
		DeleteFile(lastFile.c_str());
	}

	wstring fsrc, fdst;
	fdst = L"Users/" + id + L"/History/" + dir + L".txt";
	if (check == 0)
		fsrc = L"Dictionary/Anh-Viet/" + dir + L".txt";
	else
		fsrc = L"Dictionary/Viet-Anh/" + dir + L".txt";
	ifstream src(fsrc, ios::binary);
	ofstream dst(fdst, ios::binary);
	dst << src.rdbuf();

}
wstring User::search(wstring t, int check) {
	Searching s;
	s.isFound = 0;
	wstring res = L"NULL";
	if (check == 0)
		res = s.EngToViet(t);
	else
		res = s.VietToEng(t);

	if (s.isFound)
		saveHistory(this->_id, check, t);



	return res;
}

void User::showHistory() {
	wstring dir = L"Users/" + this->_id + L"/History";
	vector<wstring> files;
	for (auto& p : filesystem::recursive_directory_iterator(Tokens::ws2s(dir).c_str()))
	{
		wstring temp = filesystem::absolute(p.path()).wstring();
		files.push_back(temp);
	}
	files = file::SortDate(files);
	wcout << setfill(L' ') << setw(70) << L"----------------------------" << endl;
	wcout << setfill(L' ') << setw(62) << L"HISTORY:" << endl;
	wcout << setfill(L' ') << setw(70) << L"----------------------------" << endl;
	for (int i = 0; i < files.size(); i++) {
		wstring temp = files[i];
		//  "hoc123.txt";
		temp.erase(temp.length() - 4);
		wcout << i << L". " << temp << endl;
	}
	wcout << L"Bạn có muốn coi lại từ cũ không?" << endl;
	wcout << L"Chọn 0 -> 4 để coi lại, q để thoát" << endl;
	bool out = 0;
	do {
		wchar_t choose;
		wcin >> choose;
		switch (choose) {
		case L'0':
			wcout << "-------------------------------------------" << endl;
			wcout << file::readAFile(dir + L"/" + files[0]) << endl;
			wcout << "-------------------------------------------" << endl;
			break;
		case L'1':
			wcout << "-------------------------------------------" << endl;
			wcout << file::readAFile(dir + L"/" + files[1]) << endl;
			wcout << "-------------------------------------------" << endl;
			break;
		case L'2':
			wcout << "-------------------------------------------" << endl;
			wcout << file::readAFile(dir + L"/" + files[2]) << endl;
			wcout << "-------------------------------------------" << endl;
			break;
		case L'3':
			wcout << "-------------------------------------------" << endl;
			wcout << file::readAFile(dir + L"/" + files[3]) << endl;
			wcout << "-------------------------------------------" << endl;
			break;
		case L'4':
			wcout << "-------------------------------------------" << endl;
			wcout << file::readAFile(dir + L"/" + files[4]) << endl;
			wcout << "-------------------------------------------" << endl;
			break;
		default:
			out = 1;
		}
	} while (!out);
}

void User::setId(const wstring& s) {
	_id = s;
}