#include "Message.h"

Message::Message(qintptr sender, QByteArray content) {
	this->sender = sender;
	this->content = content;
}

Message::Message(qintptr sender, QByteArray content, QDateTime date) {
	this->sender = sender;
	this->content = content;
	this->date = date;
}
