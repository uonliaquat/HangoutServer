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
			query = "INSERT INTO Users VALUES('" + name + "','" + userName + "','" + password + "', 'null')";
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
			if (row[2] != username) {
				result = result + +"///";
				result = result + row[0] + "::" + row[1] + "::" + row[3];
			}
		}
		result = result + "******";
		return result;
	}
	else {
		return " ";
	}
}

string MySQLMethods::GetFriends(string username) {

	string result;
	query = "SELECT Users.name, Users.username, Users.image_url FROM Users INNER JOIN Friends ON Friends.sender = Users.username WHERE Friends.status = 'Friends' AND Friends.receiver = '"+ username +"'" ;
	q = query.c_str();
	qstate = mysql_query(mySQLConnection.getConnection(), q);
	if (!qstate) {
		res = mysql_store_result(mySQLConnection.getConnection());
		while (row = mysql_fetch_row(res)) {
			result = result + +"///";
			result = result + row[0] + "::" + row[1] + "::" + row[2];
		}
		result = result + "******";
		return result;
	}
	else {
		return " ";
	}
}

string MySQLMethods::GetEventRequests(string username) {

	string result;
	query = "SELECT Events_Detail.event_creator, Events_Detail.event_name, Events_Detail.date, Events_Detail.time, Events_Detail.location, Events_Detail.latLng, Events_Detail.event_id FROM Events INNER JOIN Events_Detail ON Events_Detail.event_id = Events.event_id WHERE Events.receiver = +'" + username + "' AND status = '" + constants.PENDING + "'";
	q = query.c_str();
	qstate = mysql_query(mySQLConnection.getConnection(), q);
	if (!qstate) {
		res = mysql_store_result(mySQLConnection.getConnection());
		while (row = mysql_fetch_row(res)) {
				result = result + +"///";
				result = result + row[0] + "::" + row[1] + "::" + row[2] + "::" + row[3] + "::" + row[4] + "::" + row[5] + "::" + row[6] + "::" + row[7];
		}
		result = result + "******";
		return result;
	}
	else {
		return " ";
	}
}

string MySQLMethods::GetPendingEvents(string username) {

	string result;
	query = "SELECT Events_Detail.event_creator, Events_Detail.event_name, Events_Detail.date, Events_Detail.time, Events_Detail.location, Events_Detail.latLng, Events_Detail.event_id FROM Events INNER JOIN Events_Detail ON Events_Detail.event_id = Events.event_id WHERE Events.receiver = +'" + username + "' AND status = '" + constants.ACCEPTED + "'";
	q = query.c_str();
	qstate = mysql_query(mySQLConnection.getConnection(), q);
	if (!qstate) {
		res = mysql_store_result(mySQLConnection.getConnection());
		while (row = mysql_fetch_row(res)) {
			result = result + +"///";
			result = result + row[0] + "::" + row[1] + "::" + row[2] + "::" + row[3] + "::" + row[4] + "::" + row[5] + "::" + row[6] + "::" + row[7];
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
	string event_creator;
	string event_name;
	string date;
	string time;
	string location;
	string latlng;
	if (status == constants.FRIEND_REQUEST_ACCEPTED) {
		query = "UPDATE Friends SET status = 'Friends' WHERE sender = '" + receiver_username + "'";
	}
	else if (status == constants.FRIEND_REQUEST) {
		query = "INSERT INTO Friends VALUES(0, '" + sender_username + "','" + receiver_username + "','" + constants.PENDING + "')";
	}
	else if (status == constants.EVENT_REQUEST_ACCEPTED) {
		query = "Update Events SET status = '" + constants.ACCEPTED + "' WHERE event_id = " + message + " AND receiver = '" + sender_username + "'";
	}
	q = query.c_str();
	qstate = mysql_query(mySQLConnection.getConnection(), q);
	if (!qstate) {
		if (status == constants.EVENT_REQUEST_ACCEPTED) {
			query = "SELECT Events_Detail.event_creator, Events_Detail.event_name, Events_Detail.date, Events_Detail.time, Events_Detail.location, Events_Detail.latLng, Users.name FROM Users INNER JOIN Events_Detail WHERE Events_Detail.event_id = " + message + " AND Users.username = '" + sender_username + "'";
			q = query.c_str();
			qstate = mysql_query(mySQLConnection.getConnection(), q);
			if (!qstate) {
				res = mysql_store_result(mySQLConnection.getConnection());
				row = mysql_fetch_row(res);
				event_creator = row[0];
				event_name = row[1];
				date = row[2];
				time = row[3];
				location = row[4];
				latlng = row[5];
				sender_name = row[6];

				messageQueue.Add_Message(sender_name, sender_username, "", event_creator, event_name, status, date, time, location,latlng, message);
				return 0;
			}
			else {
				return -1;
			}
		}
		else {
			query = "SELECT name, image_url  FROM Users WHERE username = '" + sender_username + "'";
			q = query.c_str();
			qstate = mysql_query(mySQLConnection.getConnection(), q);
			if (!qstate) {
				res = mysql_store_result(mySQLConnection.getConnection());
				row = mysql_fetch_row(res);
				sender_name = row[0];
				sender_pic_url = row[1];
				messageQueue.Add_Message(sender_name, sender_username, sender_pic_url, receiver_username, message, status, "", "", "", "", "");
				return 0;
			}
			else {
				return -1;
			}
		}
	}
	else {
		return -1;
	}
}

int MySQLMethods::Event(string event_name, string sender_username, string receiver_username, string status, string event_date, string event_time, string place, string latlng, int count) {
	string id;
	string sender_pic_url;
	string sender_name;
	qstate = 0;
	if (count == 0) {
		query = "INSERT INTO Events_Detail VALUES(0, '" + sender_username + "','" + event_name + "','" + event_date + "','" + event_time + "','" + place + "','" + latlng + "')";
		q = query.c_str();
		qstate = mysql_query(mySQLConnection.getConnection(), q);
		if (!qstate) {
			query = "SELECT LAST_INSERT_ID()";
			q = query.c_str();
			qstate = mysql_query(mySQLConnection.getConnection(), q);
			if (!qstate) {
				res = mysql_store_result(mySQLConnection.getConnection());
				row = mysql_fetch_row(res);
				event_id = atoi(row[0]);
			}
			else {
				return -1;
			}
		}
		else {
			return -1;
		}

	}
	if (!qstate) {
		string id = to_string(event_id);
		query = "INSERT INTO Events VALUES (0, '" + receiver_username + "','" + id + "','" + constants.PENDING + "');";
		q = query.c_str();
		qstate = mysql_query(mySQLConnection.getConnection(), q);
		if (!qstate) {
			query = "SELECT name, image_url  FROM Users WHERE username = '" + sender_username + "'";
			q = query.c_str();
			qstate = mysql_query(mySQLConnection.getConnection(), q);
			if (!qstate) {
				res = mysql_store_result(mySQLConnection.getConnection());
				row = mysql_fetch_row(res);
				sender_name = row[0];
				sender_pic_url = row[1];
				messageQueue.Add_Message(sender_name, sender_username, sender_pic_url, receiver_username, event_name, status, event_date, event_time, place, latlng, to_string(event_id));
				return 0;

			}
			else {
				return -1;
			}
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

string MySQLMethods::GetPictureUrl(string username) {
	string pic_url;
	query = "SELECT image_url FROM Users WHERE username = '" + username + "'";
	q = query.c_str();
	qstate = mysql_query(mySQLConnection.getConnection(), q);
	if (!qstate) {
		res = mysql_store_result(mySQLConnection.getConnection());
		row = mysql_fetch_row(res);
		pic_url = row[0];
		return pic_url;
	}
	else {
		return "";
	}
}

int MySQLMethods::SaveMemory(string username, string pic_url) {
	query = "INSERT into Memories VALUES(0, '" + username + "','" + pic_url + "')";
	q = query.c_str();
	qstate = mysql_query(mySQLConnection.getConnection(), q);
	if (!qstate) {
		return 0;
	}
	else {
		return -1;
	}
}


string MySQLMethods::GetMemory(string username) {
	string result;
	query = "SELECT Users.name, Users.username, Users.image_url, Memories.memory_url FROM Users INNER JOIN Memories ON Users.username = Memories.username";
	q = query.c_str();
	qstate = mysql_query(mySQLConnection.getConnection(), q);
	if (!qstate) {
		res = mysql_store_result(mySQLConnection.getConnection());
		while (row = mysql_fetch_row(res)) {
			result = result + +"///";
			result = result + row[0] + "::" + row[1] + "::" + row[2] + "::" + row[3];
		}
		result = result + "******";
		return result;
	}
	else {
		return " ";
	}
}




