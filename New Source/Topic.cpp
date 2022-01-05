#pragma once
#include"Topic.h"

Topic::Topic()
{

}
Topic::Topic(QString topic)
{
	m_topicName = topic;
}
void Topic::setTopic(QString topic)
{
	m_topicName = topic;
	if (!m_image.empty())
	{
		m_image.resize(0);
	}
	if (!m_meaning.empty())
	{
		m_meaning.resize(0);
	}
	load();
}

QString Topic::getTopic()
{
	return m_topicName;
}
vector<QString> Topic::getImage()
{
	return m_image;
}
QString Topic::getImageAt(int index)
{
	if (index >= 0 && index < m_image.size())
	{
		return m_image[index];
	}
	return "";
}
QString Topic::getMeaningAt(int index)
{
	if (index >= 0 && index < m_image.size())
	{
		return m_meaning[index];
	}
	return "";
}

void Topic::load()
{

	QFile f("Data_img/" + m_topicName + "/" + m_topicName + ".txt");
	f.open(QFile::ReadOnly);
	
	QTextStream read(&f);
	read.setEncoding(QStringConverter::Utf8);
	for (int i = 0; i < NUMBER_OF_PICTURE; i++)
	{
		QString token;
		read >> token;
		QString meaning;
		meaning = token.section("_", 1);
		for (int i = 0; i < meaning.length(); i++)
		{
			if (meaning[i] == '_')
			{
				meaning.replace("_", " ");
			}
		}
		token.remove(token.indexOf("_", 0), token.length());

		m_image.push_back(token);
		m_meaning.push_back(meaning);

	}
}

