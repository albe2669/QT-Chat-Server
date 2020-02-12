#pragma once

#include <QString>
#include <QDateTime>

class Message
{
public:
	Message(qintptr, QByteArray);
	Message(qintptr, QByteArray, QDateTime);

	QByteArray content;
	QDateTime date = QDateTime::currentDateTime();
	qintptr sender;
	
	bool logged = false;
};

