#include <iostream>
#include <mysql.h>

using namespace std;

#ifndef MySQLConnection_H
#define MySQLConnection_H

class MySQLConnection {

public:
	MySQLConnection();
	MYSQL * getConnection();

private:
	MYSQL * conn;
	const char * HOST = "hangout-database.cnwj4bpkbtyl.us-east-1.rds.amazonaws.com";
	const char * USERNAME = "falcons16";
	const char * PASSWORD = "falcons16";
	const char * DATABASE = "Hangout";
	int PORT = 3306;
};

#endif
