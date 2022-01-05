#pragma once
#include <vector>
#include <string>
using namespace std;
#define NUM_OF_TOP_RESULT 5

class Result {
private:
	wstring _user;
	int _score;
	int _time;
public:
	Result(wstring, int, int);
	wstring User();
	int Score();
	int Time();
	static vector<Result> loadTopRanking();
	vector<Result> insert(vector<Result> rank);
	void save();
};
