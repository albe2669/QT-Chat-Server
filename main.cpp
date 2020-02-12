#include "ChattingServer.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	
	ChattingServer Server;
	Server.startServer();
	
	return a.exec();
}
