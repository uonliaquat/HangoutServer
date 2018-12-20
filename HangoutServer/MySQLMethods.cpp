#include "pch.h"
#include "MySQLMethods.h"


int MySQLMethods::RegisterUser(string name, string userName, string password) {
	query = "SELECT * FROM Users WHERE username = '"+ userName + "'";
	q = query.c_str();
	qstate = mysql_query(mySQLConnection.getConnection(), q);
	if (!qstate) {
		res = mysql_store_result(mySQLConnection.getConnection());
		int rows = mysql_num_rows(res);
		if (rows == 0) {
			query = "INSERT INTO Users VALUES(0 , '" + name + "','" + userName + "','" + password + "', 'null')";
			q = query.c_str();
			qstate = mysql_query(mySQLConnection.getConnection(), q);
			if (!qstate) {
				return 0;
			}
			else {
				return -1;
			}
		}
		else {
			return -2;
		}
	}
	else {
		return -2;
	}
}

int MySQLMethods::LoginUser(string userName, string password) {
	query = "SELECT * FROM Users WHERE username = '" + userName + "' AND password = '" + password + "'";
	q = query.c_str();
	qstate = mysql_query(mySQLConnection.getConnection(), q);
	if (!qstate) {
		res = mysql_store_result(mySQLConnection.getConnection());
		int rows = mysql_num_rows(res);
		if (rows == 1) {
			return 0;
		}
		else {
			return -2;
		}
	}
	else {
		return -1;
	}
}

string MySQLMethods::GetAllUsers(string username) {
	
	string result;
	query = "SELECT * FROM Users";
	q = query.c_str();
	qstate = mysql_query(mySQLConnection.getConnection(), q);
	if (!qstate) {
		res = mysql_store_result(mySQLConnection.getConnection());
		while (row = mysql_fetch_row(res)) {
			//if (row[2] != username) {
				result = result + +"///";
				result = result + row[1] + "::" + row[2] + "::" + row[4];
			//}
		}
		result = result + "******";
		return result;
	}
	else {
		return " ";
	}
}

int MySQLMethods::Message(string sender_username, string receiver_username, string message, string status) {
	string id;
	string sender_pic_url;
	string sender_name;
	query = "SELECT user_id FROM Users WHERE username = '" + sender_username + "'";
	q = query.c_str();
	qstate = mysql_query(mySQLConnection.getConnection(), q);
	if (!qstate) {
		res = mysql_store_result(mySQLConnection.getConnection());
		row = mysql_fetch_row(res);
		id = row[0];
		if (status == constants.FRIEND_REQUEST_ACCEPTED) {
			query = "UPDATE Friends SET status = 'Friends' WHERE sender = " + id;
			q = query.c_str();
			qstate = mysql_query(mySQLConnection.getConnection(), q);
		}
		else if (status == constants.FRIEND_REQUEST) {
			query = "INSERT INTO Friends VALUES(0, '" + sender_username + "','" + receiver_username + "','" + constants.PENDING + "'," + id + ")";
			q = query.c_str();
			qstate = mysql_query(mySQLConnection.getConnection(), q);
		}

		if (!qstate) {
			query = "SELECT name, image_url  FROM Users WHERE username = '" + sender_username + "'";
			q = query.c_str();
			qstate = mysql_query(mySQLConnection.getConnection(), q);
			if (!qstate) {
				res = mysql_store_result(mySQLConnection.getConnection());
				row = mysql_fetch_row(res);
				sender_name = row[0];
				sender_pic_url = row[1];
				messageQueue.Add_Message(sender_name, sender_username, sender_pic_url, receiver_username, message, status, "", "");
				return 0;
			}
			else {
				return -1;
			}

			return -1;
		}
		else {
			return -1;
		}
	}
	else {
		return -1;
	}
}

int MySQLMethods::Event(string event_name, string sender_username, string receiver_username, string status, string event_date, string event_time) {
	string id;
	string sender_pic_url;
	string sender_name;
	query = "SELECT user_id FROM Users WHERE username = '" + sender_username + "'";
	q = query.c_str();
	qstate = mysql_query(mySQLConnection.getConnection(), q);
	if (!qstate) {
		res = mysql_store_result(mySQLConnection.getConnection());
		row = mysql_fetch_row(res);
		id = row[0];
		query = "INSERT INTO Events VALUES(0, '" + event_name + "','" + sender_username + "','" + receiver_username + "','" + constants.PENDING + "'," + id + ",'" + event_date + "','" + event_time + "')";
		q = query.c_str();
		int qstate = mysql_query(mySQLConnection.getConnection(), q);
		if (!qstate) {
			query = "SELECT name, image_url  FROM Users WHERE username = '" + sender_username + "'";
			q = query.c_str();
			qstate = mysql_query(mySQLConnection.getConnection(), q);
			if (!qstate) {
				res = mysql_store_result(mySQLConnection.getConnection());
				row = mysql_fetch_row(res);
				sender_name = row[0];
				sender_pic_url = row[1];
				messageQueue.Add_Message(sender_name, sender_username, sender_pic_url, receiver_username, event_name, status, event_date, event_time);
				return 0;

			}
			else {
				return -1;
			}
		}
		else {
			return -1;
		}
	}
	else {
		return -1;
	}
}


int MySQLMethods::SavePictureUrl(string username, string url, string name) {
	string id;
	query = "UPDATE Users SET image_url = '"+ url +"' WHERE username = '"+ username +"'";
	q = query.c_str();
	qstate = mysql_query(mySQLConnection.getConnection(), q);
	if (!qstate) {
		query = "UPDATE Users SET name = '" + name + "' WHERE username = '" + username + "'";
		q = query.c_str();
		qstate = mysql_query(mySQLConnection.getConnection(), q);
		if (!qstate) {
			return 1;
		}
		else {
			return -2;
		}
		return 0;
	}
	else {
		return -1;
	}

}




