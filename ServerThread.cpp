#include "ServerThread.h"
#include "ChattingServer.h"
#include "Message.h"


ServerThread::ServerThread(qintptr ID, QObject* parent) : QThread(parent) {
	this->socketDescriptor = ID;
	this->parent = parent;
	this->socket = new QTcpSocket();
}

void ServerThread::run() {
	// Construct the necessary components for this thread
	qDebug() << "Starting thread for " << socketDescriptor;
	
	if (!socket->setSocketDescriptor(this->socketDescriptor)) {
		emit error(socket->error());
		return;
	}

	qDebug() << "Sending init response";
	socket->write("200");
	socket->waitForBytesWritten();
	qDebug() << "Init response sent";
	qDebug() << "Waiting 3000 ms for name";
	
	if (!socket->waitForReadyRead()) {
		qDebug() << "Never got name, closing thread";
		exit(0);
	} else {
		qDebug() << "Recieving name";
		QByteArray data = socket->readAll();
		this->name = data;
		qDebug() << "Thread " << socketDescriptor << "'s name is now: " << this->name;
		qDebug() << "Confirming";
		socket->write("200;Server connection establisehd");
		socket->waitForBytesWritten();
	}

	(void)connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::DirectConnection);
	(void)connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
	
	qDebug() << "Thread for client:  " << socketDescriptor << " is done setting up";

	// Loop the thread for as long as client is connected
	exec();
}

void ServerThread::readyRead() {
	QByteArray data = socket->readAll();
	Message* message = new Message(this->socketDescriptor, data);

	qDebug() << socketDescriptor << " sent data: " << data;
	this->messages.append(message);
	
	//socket->write("200");
	ChattingServer* pChatServer = dynamic_cast<ChattingServer*>(parent);
	pChatServer->spreadMessage(message, this->name);
}

void ServerThread::disconnected() {
	qDebug() << socketDescriptor << " disconnected";
	socket->deleteLater();

	// Quit the thread, not the application
	exit(0);
}

qintptr ServerThread::getSocketDescriptor() {
	return this->socketDescriptor;
}

void ServerThread::sendMessage(Message* message, QString name) {
	qDebug() << "Send message from thread";
	
	QString data = name + ";" + message->content;
	QByteArray dataToSend = data.toUtf8();


	qDebug() << "Sending " << dataToSend;

	this->socket->write(dataToSend);
	this->socket->waitForBytesWritten();
	
	qDebug() << "Message sent";
	return;
}