#include <iostream>
#include <fstream>
#include <string>
#include <fstream>

using namespace std;

#ifndef FileHandling_H
#define FileHandling_H


class FileHandling {

public:
	int SavePicture(string username, string picture);
	string GetPicture(string username);

private:


};

#endif
