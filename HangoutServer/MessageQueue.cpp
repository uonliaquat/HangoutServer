#include "pch.h"
#include "MessageQueue.h"


void MessageQueue::Add_Message(string sender_name, string sender_username, string sender_pic_url,  string receiver_username, string message, string status, string event_date, string event_time)
{
	Message *newMessage = new Message;
	newMessage->sender = sender_name;
	newMessage->receiver = receiver_username;
	newMessage->message = message;
	newMessage->status = status;
	newMessage->sender_username = sender_username;
	newMessage->sender_picture_url = sender_pic_url;
	newMessage->date = event_date;
	newMessage->time = event_time;

	Message * temp = root;
	if (temp == nullptr) {
		root = newMessage;
		return;
	}
	while (temp->next != nullptr) {
		temp = temp->next;
	}
	temp->next = newMessage;
}

string MessageQueue::Get_Message(string username) {
	Message * temp = root;
	Message * temp1 = temp;
	int i = 0;
	while (temp != nullptr)
	{
		if (i == 1) {
			temp1 = temp1->next;
		}
		i = 1;
		if (temp->receiver == username) {
			string msg = temp->sender + "///" + temp->sender_username + "///" + temp->sender_picture_url + "///" + temp->status + "///" + temp->message + "///" + temp->date + "///" + temp->time;
			Message * temp2 = temp;
			temp1->next = temp2->next;
			delete temp2;
			return msg;

		}
		temp = temp->next;
	}
	return "";
}

