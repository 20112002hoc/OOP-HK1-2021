#include "Result.h"
#include <fstream>

Result::Result(wstring user, int score, int time)
{
	_user = user;
	_score = score;
	_time = time;
}

wstring Result::User()
{
	return wstring(_user);
}

int Result::Score()
{
	return _score;
}

int Result::Time()
{
	return _time;
}

vector<Result> Result::loadTopRanking()
{
	wifstream fin(".\\Users\\Ranking.txt");
	vector <Result> rank;
	while (!fin.eof()) {
		wstring user;
		int score;
		int time;
		fin >> user;
		fin >> score;
		fin >> time;
		rank.push_back(Result(user, score, time));
	}
	fin.close();
	return rank;
}

vector<Result> Result::insert(vector<Result> rank)
{
	int i = 0;
	while (rank[i]._score > this->_score || (rank[i]._score == this->_score && rank[i]._time < this->_time)) {
		i++;
		if (i == NUM_OF_TOP_RESULT) return rank;
	}
	rank.insert(rank.begin() + i, *this);
	rank.pop_back();
	return rank;
}

void Result::save()
{

	vector<Result> rank = this->insert(Result::loadTopRanking());
	remove("Users/Ranking.txt");
	wofstream fout("Users/Ranking.txt");
	for (int i = 0; i < NUM_OF_TOP_RESULT; i++) {
		fout << rank[i]._user << L" " << rank[i]._score << L" " << rank[i]._time << L"\n";
	}
	fout.close();
}


