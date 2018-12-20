#include "pch.h"
#include "MySQLConnection.h"

MySQLConnection::MySQLConnection() {
	//BUILDING MYSQL CONNECTION
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, HOST, USERNAME, PASSWORD, DATABASE, PORT, NULL, 0);
	if (conn) {
		cout << "Succelfully Connected to Database!" << endl;
	}
	else {
		cout << "Couldn't connect to database" << endl;
	}

}

MYSQL* MySQLConnection::getConnection() {
	return conn;
}
