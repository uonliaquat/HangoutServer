#include <iostream>
#include "Message.h"
using namespace std;

#ifndef MessageQueue_H
#define MessageQueue_H


class MessageQueue {

public:
	void Add_Message(string sender_name, string sender_username, string sender_pic_url, string receiver_username, string message, string status, string event_date, string event_time, string place, string latlng, string event_id);
	string Get_Message(string username);
private:
	Message * root = nullptr;

};

#endif
