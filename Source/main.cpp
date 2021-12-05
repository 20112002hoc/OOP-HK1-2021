#include "TrainData.h"
#include <fcntl.h>  
#include <io.h>
#include "User.h"
#include "File.h"
::byte;
int Searching::isFound = 0;
int main() {
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_U8TEXT);

	//train();
	wstring id;
	wcout << L"Mời bạn nhập ID: ";
	wcin >> id;
	User u1(id);
	bool out = 0;
	do {
		out = 0;
		int choose;
		wcout << L"Chọn 0 để Thoát: " << endl;
		wcout << L"Chọn 1 để tra từ: " << endl;
		wcout << L"Chọn 2 để xem lịch sử tra: " << endl;
		wcin >> choose;
		switch (choose) {
		case 1:
			u1.search(); break;
		case 2:
			u1.showHistory(); break;
		default:
			out = 1;
		}

	} while (!out);

	
	return 0;
}