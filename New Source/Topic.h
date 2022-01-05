#pragma once

#include<vector>
#include<QString>
#include<QFile>
#include<QTextStream>

using namespace std;

#define NUMBER_OF_TOPIC 7
#define NUMBER_OF_PICTURE 10

class Topic
{
	QString m_topicName;
	vector<QString> m_image;
	vector<QString> m_meaning;

public:
	Topic();
	Topic(QString);

	void setTopic(QString);
	QString getTopic();

	vector<QString> getImage();
	QString getImageAt(int);
	QString getMeaningAt(int);
	void load();

};