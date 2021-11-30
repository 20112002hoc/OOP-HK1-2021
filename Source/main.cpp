#include "TrainData.h"
#include "Search.h"
#include <fcntl.h>  
#include <io.h>


int main() {
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_U8TEXT);
	//train();

	Searching search;
	bool again = 0;
	do {
		int choice = 0;
		wstring tokens;
		wcout << L"Chọn Anh - Việt nhấn 0.\n";
		wcout << L"Chọn Việt - Anh nhấn 1.\n";
		wcin >> choice;

		if (choice == 0) {
			do {
				again = 0;
				wcout << L"Mời bạn nhập từ khóa: ";

				wcin.ignore();
				getline(wcin, tokens);
				search.EngToViet(tokens);
				wcout << L"\n\n-----------------------------------------\nNhập lại nhấn 1.\nNhấn 0 để thoát.\n";
				wcin >> again;
			} while (again);
		}
		else {
			do {
				again = 0;
				wcout << L"Mời bạn nhập từ khóa: ";

				wcin.ignore();
				getline(wcin, tokens);
				search.VietToEng(tokens);
				wcout << L"\n\n-----------------------------------------\nNhập lại nhấn 1.\nNhấn 0 để thoát.\n";
				wcin >> again;
			} while (again);
		}
		wcout << L"Bạn có muốn dịch nữa?\n";
		wcout << L"\n\n-----------------------------------------\nNhập lại nhấn 1.\nNhấn 0 để thoát.\n";
		wcin >> again;
	} while (again);


	return 0;
}