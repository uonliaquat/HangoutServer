#include "pch.h"
#include "FileHandling.h"

int FileHandling::SavePicture(string username, string picture) {
	ofstream myfile("C:/Users/uonliaquatarain/Desktop/HangoutData/PrrofilePictures/ProfilePicture_" + username + ".txt");
	if (myfile.is_open())
	{
		myfile << picture;
		myfile.close();
		return 0;
	}
	else {
		return -1;
	}
}

string FileHandling::GetPicture(string username) {
	string line;
	string result = "";
	ifstream myfile("C:/Users/uonliaquatarain/Desktop/HangoutData/PrrofilePictures/ProfilePicture_" + username + ".txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			result = result + line;
		}
		myfile.close();
		return result;
	}
	else {
		return "";
	}
}