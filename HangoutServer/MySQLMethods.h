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
	int SavePictureUrl(string username, string url, string name);
	int Message(string sender_username, string receiver_username, string message, string status);
	int Event(string event_name, string sender_username, string receiver_username, string status, string event_date, string event_time);
	MessageQueue messageQueue;
private:
	string query;
	const char * q;
	int qstate;
	MYSQL_ROW row;
	MYSQL_RES * res;
	MySQLConnection mySQLConnection;
	Constants constants;



};

#endif
