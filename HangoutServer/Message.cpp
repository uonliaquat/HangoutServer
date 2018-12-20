#include "pch.h"
#include "Message.h"

Message::Message() {
	next = nullptr;
	message = "";
	sender = "";
	receiver = "";
	status = "";
	sender_picture_url = "";
	sender_username = "";
	date = "";
	time = "";
}