#include <iostream>
#include<string>
#include "Constants.h"


using namespace std;

#ifndef JSONParser_H
#define JSONParser_H


class JSONParser {

public:
	string getMethod(string str);
	string getName(string str);
	string getUsername(string str);
	string getReceiverUsername(string str);
	string getPassword(string str);
	string getProfilePictureUrl(string str);
	string getMessage(string str);
	string getDate(string str);
	string getTime(string str);

private:
	Constants constants;

};

#endif
