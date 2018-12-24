#include <iostream>
#include <mysql.h>
#include <string>
#include "Constants.h"
#include "MessageQueue.h"
#include <fstream>
#include <sstream>


#include "MySQLConnection.h"

using namespace std;


#ifndef MySQLMethods_H
#define MySQLMethods_H


class MySQLMethods {

public:
	int RegisterUser(string name, string userName, string password);
	int LoginUser(string userName, string password);
	string GetAllUsers(string username);
	string GetFriends(string username);
	string GetEventRequests(string username);
	string GetPendingEvents(string username);
	int SavePictureUrl(string username, string url, string name);
	int SaveMemory(string username, string pic_url);
	string GetMemory(string username);
	string GetPictureUrl(string username);
	int Message(string sender_username, string receiver_username, string message, string status);
	int Event(string event_name, string sender_username, string receiver_username, string status, string event_date, string event_time, string place, string latlng, int count);
	MessageQueue messageQueue;
private:
	string query;
	const char * q;
	int qstate;
	MYSQL_ROW row;
	MYSQL_RES * res;
	MySQLConnection mySQLConnection;
	Constants constants;
	int event_id;



};

#endif
