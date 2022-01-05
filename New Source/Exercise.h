#pragma once
#include <string>
#include <vector>
using namespace std;
#define NUM_OF_TOPIC 10
#define NUM_OF_QUES_IN_PRAC 5
#define NUM_OF_QUES_IN_TEST 10
#define NUM_OF_TOPIC_VOCAB 7		//thêm vào
extern const string topic[];	
extern const string topicVocab[];	//thêm vào
class Question {
protected:
	string _ques;
	string _key;
	int8_t _topicVocab;
public:
	Question(string, string);
	Question(const Question*);
	const string getQues();
	const string getKey();
	int gettopicVocab();
	bool check(string ans);
	virtual const string getOption(int num);
};

class FillingBlank : public Question {
public:
	FillingBlank(string, string);
	FillingBlank(const FillingBlank*);
};

class MultipleChoice : public Question {
protected:
	string _opt[4];
public:
	MultipleChoice(string, string, string, string, string, string);
	MultipleChoice(const MultipleChoice* q);
	const string getOption(int num);
};

class Exercise {
protected:
	vector<Question*> _ques;
public:
	~Exercise();
	void load(string path);
	static void separateWord(string& s);
	void addQuestion(Question*);
	Question* getCopyQuestion(int index);
	int getSize();
	const string getQues(int index);
	const string getKey(int index);
	const string getOpt(int index, int num);
	int gettopicVocab(int index);

};



class Grammar {
protected:	 //sửa lại proteced
	//vector<Theory> _theory;
	vector<Exercise*> _exer;
public:
	Grammar();
	~Grammar();
	virtual void load();
	virtual Exercise* createPracQuiz(int index);	//them vao virtual
	virtual Exercise* createTestQuiz();				//them vao virtual
	static const string quesCode(int index, int num);


};

class GrammarVocab : public Grammar
{
public:
	GrammarVocab();
	void load();
	Exercise* createTestQuiz();
};
