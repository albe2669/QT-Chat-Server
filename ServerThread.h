#pragma once

#include "Message.h"

#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include <QVector>

class ServerThread : public QThread
{
	Q_OBJECT

public:
	explicit ServerThread(qintptr, QObject* parent = 0);
	void run();
	void sendMessage(Message*, QString);
	qintptr getSocketDescriptor();

	QString name = "";
	QVector<Message*> messages;

signals:
	void error(QTcpSocket::SocketError socketError);

public slots:
	void readyRead();
	void disconnected();

private:
	QTcpSocket* socket;
	qintptr socketDescriptor;
	QObject* parent;
};

