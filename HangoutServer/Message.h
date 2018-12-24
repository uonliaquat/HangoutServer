#include <iostream>


using namespace std;

#ifndef Message_H
#define Message_H


struct Message {

public:
	Message();
	string sender;
	string receiver;
	string message;
	string status;
	string sender_username;
	string sender_picture_url;
	string date;
	string time;
	string place;
	string latlng;
	Message * next;
	string event_id;


};

#endif
