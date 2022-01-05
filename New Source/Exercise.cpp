#include <iostream>
#include <fstream>
#include <time.h>
#include "Exercise.h"
using namespace std;

const string topic[] = { "Present Simple", "Present Continuous", "Present Perfect", "Past Simple", "Past Continuous", "Past Perfect", "Future Simple", "Future Continuous", "Future Perfect", "Future Near" };
const string topicVocab[] = { "Animal","Body","Food","Fruit","Job","Sport","Transport" };
Question::Question(string ques, string key)
{
	_ques = ques;
	_key = key;
	_topicVocab = -1;
}

Question::Question(const Question* q)
{
	this->_ques = q->_ques;
	this->_key = q->_key;
	this->_topicVocab = q->_topicVocab;
}

const string Question::getQues()
{
	return _ques;
}

const string Question::getKey()
{
	return _key;
}

int Question::gettopicVocab()
{
	return _topicVocab;
}

bool Question::check(string ans)
{
	return (ans == _key) ? 1 : 0;
}

const string Question::getOption(int num)
{
	return string();
}

FillingBlank::FillingBlank(string ques, string key) : Question(ques, key)
{
	_topicVocab = 1;
}

FillingBlank::FillingBlank(const FillingBlank* q) : Question::Question(q)
{
	_topicVocab = 1;
}

MultipleChoice::MultipleChoice(string ques, string key, string opt1, string opt2, string opt3, string opt4) : Question(ques, key)
{
	_opt[0] = opt1;
	_opt[1] = opt2;
	_opt[2] = opt3;
	_opt[3] = opt4;
	_topicVocab = 0;
}

MultipleChoice::MultipleChoice(const MultipleChoice* q) : Question::Question(q)
{
	_opt[0] = q->_opt[0];
	_opt[1] = q->_opt[1];
	_opt[2] = q->_opt[2];
	_opt[3] = q->_opt[3];
	_topicVocab = 0;
}

const string MultipleChoice::getOption(int num)
{
	return _opt[num];
}

Exercise::~Exercise()
{
	for (int i = 0; i < _ques.size(); i++) {
		delete _ques[i];
	}
}

void Exercise::load(string path)
{
	ifstream file(path);
	string ques, topicVocab, key;
	while (!file.eof()) {
		getline(file, ques);
		file >> topicVocab;
		if (topicVocab == "F") {
			file >> key;
			separateWord(key);
			FillingBlank* q = new FillingBlank(ques, key);
			_ques.push_back(q);
		}
		else if (topicVocab == "M") {
			string opt[4];
			file >> key;
			separateWord(key);
			for (int i = 0; i < 4; i++) {
				file >> opt[i];
				separateWord(opt[i]);
			}
			MultipleChoice* q = new MultipleChoice(ques, key, opt[0], opt[1], opt[2], opt[3]);
			_ques.push_back(q);
		}
		file.ignore();
	}
	file.close();
}

void Exercise::separateWord(string& s)
{
	int i = 0;
	while (i < s.length()) {
		if (s[i] == '_')
			s[i] = ' ';
		i++;
	}
}

void Exercise::addQuestion(Question* copy)
{
	this->_ques.push_back(copy);
}

Question* Exercise::getCopyQuestion(int index)
{
	if (this->_ques[index]->gettopicVocab() == 0) {
		Question* copy = new MultipleChoice((MultipleChoice*)this->_ques[index]);
		return copy;
	}
	else if (this->_ques[index]->gettopicVocab() == 1) {
		Question* copy = new FillingBlank((FillingBlank*)this->_ques[index]);
		return copy;
	}
	else return NULL;
}

int Exercise::getSize()
{
	return _ques.size();
}

const string Exercise::getQues(int index)
{
	return _ques[index]->getQues();
}

const string Exercise::getKey(int index)
{
	return _ques[index]->getKey();
}

const string Exercise::getOpt(int index, int num)
{
	return _ques[index]->gettopicVocab() == 0 ? _ques[index]->getOption(num) : "";
}

int Exercise::gettopicVocab(int index)
{
	return _ques[index]->gettopicVocab();
}

Grammar::Grammar()
{
	this->load();
}

Grammar::~Grammar()
{
	for (int i = 0; i < _exer.size(); i++) {
		delete _exer[i];
	}
}

void Grammar::load()
{
	for (int i = 0; i < NUM_OF_TOPIC; i++) {
		Exercise* ex = new Exercise;
		string t = topic[i];
		t.erase(t.find(" "), 1);
		ex->load(".\\DataExercise\\" + t + ".txt");
		_exer.push_back(ex);
	}
}

Exercise* Grammar::createPracQuiz(int index)
{
	Exercise* quiz = new Exercise;
	srand(time(NULL));
	string chosenQues = "";
	for (int i = 0; i < NUM_OF_QUES_IN_PRAC; i++) {
		int num = rand() % this->_exer[index]->getSize();
		if (chosenQues.find(quesCode(index, num)) == string::npos) {
			Question* q = this->_exer[index]->getCopyQuestion(num);
			quiz->addQuestion(q);
			chosenQues += quesCode(index, num);
		}
		else {
			i--;
		}
	}
	return quiz;
}

Exercise* Grammar::createTestQuiz()
{
	Exercise* quiz = new Exercise;
	srand(time(NULL));
	string chosenQues = "";
	for (int i = 0; i < NUM_OF_QUES_IN_TEST; i++) {
		int index = rand() % NUM_OF_TOPIC;
		int num = rand() % this->_exer[index]->getSize();
		if (chosenQues.find(quesCode(index, num)) == string::npos) {
			Question* q = this->_exer[index]->getCopyQuestion(num);
			quiz->addQuestion(q);
			chosenQues += quesCode(index, num);
		}
		else {
			i--;
		}
	}
	return quiz;
}

const string Grammar::quesCode(int index, int num)
{
	string quesCode = "";
	quesCode += char('A' + index);
	quesCode += to_string(num);
	return quesCode;
}
//thêm vào bởi tường

GrammarVocab::GrammarVocab()
{
	if (!this->_exer.empty()) this->_exer.resize(0);
	this->load();
}
void GrammarVocab::load()
{
	for (int i = 0; i < NUM_OF_TOPIC_VOCAB; i++)
	{
		Exercise* newExe = new Exercise();
		string t = topicVocab[i];
		newExe->load("DataExerciseVocab/" + t + ".txt");
		this->_exer.push_back(newExe);
	}
}
Exercise* GrammarVocab::createTestQuiz()
{
	Exercise* quiz = new Exercise;
	srand(time(NULL));
	string chosenQues = "";
	for (int i = 0; i < NUM_OF_QUES_IN_TEST; i++) {
		int index = rand() % NUM_OF_TOPIC_VOCAB;
		int num = rand() % this->_exer[index]->getSize();
		if (chosenQues.find(quesCode(index, num)) == string::npos) {
			Question* q = this->_exer[index]->getCopyQuestion(num);
			quiz->addQuestion(q);
			chosenQues += quesCode(index, num);
		}
		else {
			i--;
		}
	}
	return quiz;
}