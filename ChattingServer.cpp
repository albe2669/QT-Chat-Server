#include "ChattingServer.h"
#include "ServerThread.h"

#include <QTcpSocket>
#include <QHostAddress>
#include <QTcpServer>

ChattingServer::ChattingServer(QObject *parent)
	: QTcpServer(parent)
{
}

void ChattingServer::startServer() {
	if (!this->listen(QHostAddress::Any, 1234)) {
		qDebug() << "Server was unable to start listening";
	} else {
		qDebug() << "Waiting for clients";
	}
}

void ChattingServer::incomingConnection(qintptr handle) {
	qDebug() << handle << " is connecting...";

	ServerThread* thread = new ServerThread(handle, this);
	
	this->threads.append(thread);
	
	(void)connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	
	thread->start();
}

void ChattingServer::spreadMessage(Message* message, QString name) {
	qDebug() << "Socket descriptor: " << message->sender;
	for (int i = 0; i < this->threads.size(); i++) {
		ServerThread* thread = this->threads.at(i);
		qDebug() << "Thread descriptor: " << thread->getSocketDescriptor();

		
		if (thread->getSocketDescriptor() == message->sender) {
			qDebug() << "Skip";
			continue;
		}

		qDebug() << "Sending message";
		thread->sendMessage(message, name);
	}
}