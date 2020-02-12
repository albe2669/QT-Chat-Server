#pragma once

#include <QTcpServer>
#include "ServerThread.h"

class ChattingServer : public QTcpServer
{
public:
	ChattingServer(QObject *parent = Q_NULLPTR);
	void startServer();
	void spreadMessage(Message*, QString);

	QVector<ServerThread*> threads;
	
signals:

public slots:

private:

protected:
	void incomingConnection(qintptr handle) Q_DECL_OVERRIDE;
};
