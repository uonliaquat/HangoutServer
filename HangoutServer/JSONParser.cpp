#include "pch.h"
#include "JSONParser.h"

string JSONParser::getMethod(string str) {
	if (strstr(str.c_str(), constants.REGISTER_USER.c_str())) {
		return constants.REGISTER_USER;
	}
	else if (strstr(str.c_str(), constants.LOGIN_USER.c_str())) {
		return constants.LOGIN_USER;
	}
	else if (strstr(str.c_str(), constants.GET_ALL_USERS.c_str())) {
		return constants.GET_ALL_USERS;
	}
	else if (strstr(str.c_str(), constants.SEND_FRIEND_REQUEST.c_str())) {
		return constants.SEND_FRIEND_REQUEST;
	}
	else if (strstr(str.c_str(), constants.PING.c_str())) {
		return constants.PING;
	}
	else if (strstr(str.c_str(), constants.SAVE_PROFILE_PIC.c_str())) {
		return constants.SAVE_PROFILE_PIC;
	}
	else if (strstr(str.c_str(), constants.GET_PROFILE_PIC.c_str())) {
		return constants.GET_PROFILE_PIC;
	}
	else if (strstr(str.c_str(), constants.FRIEND_REQUEST_ACCEPTED.c_str())) {
		return constants.FRIEND_REQUEST_ACCEPTED;
	}
	else if (strstr(str.c_str(), constants.FRIEND_REQUEST_REJECTED.c_str())) {
		return constants.FRIEND_REQUEST_REJECTED;
	}
	else if (strstr(str.c_str(), constants.MESSAGE.c_str())) {
		return constants.MESSAGE;
	}
	else if (strstr(str.c_str(), constants.EVENT_REQUEST.c_str())) {
		return constants.EVENT_REQUEST;
	}
}

string JSONParser::getName(string str) {
	string name = "";
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == 'n' && str[i + 1] == 'a' && str[i + 2] == 'm' && str[i + 3] == 'e') {
			i = i + 7;
			while (str[i] != '"') {
				name = name + str[i];
				i++;
			}
			break;
		}
	}
	return name;
}

string JSONParser::getUsername(string str) {
	string userName = "";
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == 'u' && str[i + 1] == 's' && str[i + 2] == 'e' && str[i + 3] == 'r' && str[i + 4] == 'n' && str[i + 5] == 'a' && str[i + 6] == 'm' && str[i + 7] == 'e') {
			i = i + 11;
			while (str[i] != '"') {
				userName = userName + str[i];
				i++;
			}
			break;
		}
	}
	return userName;
}

string JSONParser::getReceiverUsername(string str) {
	string userName = "";
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == 'u' && str[i + 1] == 's' && str[i + 2] == 'e' && str[i + 3] == 'r' && str[i + 4] == 'n' && str[i + 5] == 'a' && str[i + 6] == 'm' && str[i + 7] == 'e' &&
			str[i + 8] == '_' && str[i + 9] == 'r' && str[i + 10] == 'e' && str[i + 11] == 'c' && str[i + 12] == 'e' && str[i + 13] == 'i' && str[i + 14] == 'v' && str[i + 15] == 'e' &&
			str[i + 16] == 'r') {
			i = i + 20;
			while (str[i] != '"') {
				userName = userName + str[i];
				i++;
			}
			break;
		}
	}
	return userName;
}

string JSONParser::getPassword(string str) {
	string password = "";
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == 'p' && str[i + 1] == 'a' && str[i + 2] == 's' && str[i + 3] == 's' && str[i + 4] == 'w' && str[i + 5] == 'o' && str[i + 6] == 'r' && str[i + 7] == 'd') {
			i = i + 11;
			while (str[i] != '"') {
				password = password + str[i];
				i++;
			}
			break;
		}
	}
	return password;
}

string JSONParser::getProfilePictureUrl(string str) {
	string picture = "";
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == 'p' && str[i + 1] == 'r' && str[i + 2] == 'o' && str[i + 3] == 'f' && str[i + 4] == 'i' && str[i + 5] == 'l' && str[i + 6] == 'e' && str[i + 7] == '_'
			&& str[i + 8] == 'p' && str[i + 9] == 'i' && str[i + 10] == 'c') {
			i = i + 14;
			while (str[i] != '"') {
				picture = picture + str[i];
				i++;
			}
			break;
		}
	}
	return picture;
}

string JSONParser::getMessage(string str) {
	string message = "";
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == 'm' && str[i + 1] == 'e' && str[i + 2] == 's' && str[i + 3] == 's' && str[i + 4] == 'a' && str[i + 5] == 'g' && str[i + 6] == 'e') {
			i = i + 10;
			while (str[i] != '"') {
				message = message + str[i];
				i++;
			}
			break;
		}
	}
	return message;
}

string JSONParser::getDate(string str) {
	string date = "";
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == 'd' && str[i + 1] == 'a' && str[i + 2] == 't' && str[i + 3] == 'e') {
			i = i + 7;
			while (str[i] != '"') {
				date = date + str[i];
				i++;
			}
			break;
		}
	}
	return date;
}

string JSONParser::getTime(string str) {
	string time = "";
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == 't' && str[i + 1] == 'i' && str[i + 2] == 'm' && str[i + 3] == 'e') {
			i = i + 7;
			while (str[i] != '"') {
				time = time + str[i];
				i++;
			}
			break;
		}
	}
	return time;

}