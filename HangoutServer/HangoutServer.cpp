#include "pch.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment (lib, "ws2_32.lib")
//#pragma comment (lib, "mysqlcppconn.lib")
#include <iostream>
#include <string>
#include <WinSock2.h>
#include "MySQLConnection.h"
#include "MySQLMethods.h"
#include "JSONParser.h"
#include "Constants.h"
#include "FileHandling.h"

using namespace std;

int main() {

	static const char SERVER_IP[] = "10.211.55.3";
	static const int SERVER_PORT = 54000;
	static const int SERVER_PING_PORT = 64000;
	SOCKET listening_socket, ping_listening_socket, client_socket;
	JSONParser json_parser;
	Constants constants;
	MySQLMethods mySQLMethods;
	FileHandling fileHandling;


	//Establish MySQL Conenction
	MySQLConnection mysql_connection;

	//WinSock Startup
	WSAData wsaData;
	WORD Dllversion = MAKEWORD(2, 1);
	if (WSAStartup(Dllversion, &wsaData) != 0) {
		MessageBoxA(NULL, "WinSock Startup failed!", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	//Create Socket
	ping_listening_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (ping_listening_socket == -1) {
		cerr << "Can't Create Ping Socket";
		return -1;
	}
	listening_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (listening_socket == -1) {
		cerr << "Can't Create Socket";
		return -1;
	}

	//Bind the socket with ip address and port number
	sockaddr_in server, client;
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);
	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	memset(server.sin_zero, 8, 0);


	//Bind the socket with ip address and port number: PING
	sockaddr_in server_ping, client_ping;
	server_ping.sin_family = AF_INET;
	server_ping.sin_port = htons(SERVER_PING_PORT);
	server_ping.sin_addr.s_addr = inet_addr(SERVER_IP);
	memset(server.sin_zero, 8, 0);


	int len = sizeof(sockaddr_in);
	if ((bind(listening_socket, (sockaddr*)&server, len)) == -1) {
		cerr << "Can't bind!" << endl;
		return -1;
	}


	int len_ping = sizeof(sockaddr_in);
	if ((bind(ping_listening_socket, (sockaddr*)&server_ping, len_ping)) == -1) {
		cerr << "Can't bind Ping!" << endl;
		return -1;
	}

	//Start Listening
	if (listen(listening_socket, SOMAXCONN) == -1) {
		cerr << "Can't bind!" << endl;
	}

	if (listen(ping_listening_socket, SOMAXCONN) == -1) {
		cerr << "Can't bind!" << endl;
	}

	cout << "Server Started!" << endl;
	char rec_buf[4096];
	char send_buf[4096];
	string msg;
	while (true)
	{
		//Wait for connection
		if ((client_socket = accept(listening_socket, (sockaddr*)&client, &len)) == -1) {
			cerr << "Can't accept" << endl;
		}
		memset(rec_buf, 4096, 0);
		memset(send_buf, 4096, 0);
		int bytesReceived = recv(client_socket, rec_buf, 4096, 0);
		if (bytesReceived > 0) {
			//Check Client Request Method
			if (json_parser.getMethod(rec_buf) == constants.PING) {
				string username = json_parser.getUsername(rec_buf);
				string result = mySQLMethods.messageQueue.Get_Message(username);
				msg = constants.PING + " " + result;
				if (result != "") {
					strcpy_s(send_buf, msg.c_str());
					if ((send(client_socket, send_buf, strlen(send_buf), 0)) != -1) {
						//cout << send_buf << endl;
					}
				}
			}
			else if (json_parser.getMethod(rec_buf) == constants.REGISTER_USER) {
				string name = json_parser.getName(rec_buf);
				string username = json_parser.getUsername(rec_buf);
				string password = json_parser.getPassword(rec_buf);
				int status = mySQLMethods.RegisterUser(name, username, password);
				if (status == 0) {
					msg = constants.REGISTER_USER + " Registered successfully!";
				}
				else if(status == -2){
					msg = constants.REGISTER_USER + " Username already exists!";
				}
				else {
					msg = constants.REGISTER_USER + " Couldn't Register!";
				}
				strcpy_s(send_buf, msg.c_str());
				if ((send(client_socket, send_buf, strlen(send_buf), 0)) != -1) {
					cout << send_buf << endl;
				}
			}
			else if (json_parser.getMethod(rec_buf) == constants.LOGIN_USER) {
				string username = json_parser.getUsername(rec_buf);
				string password = json_parser.getPassword(rec_buf);
				int status = mySQLMethods.LoginUser(username, password);
				if (status == 0) {
					msg = constants.LOGIN_USER + " Logged In successfully!";
				}
				else if (status == -2) {
					msg = constants.LOGIN_USER + " Username doesn't exist!";
				}
				else{
					msg = constants.LOGIN_USER + " Couldn't Login!";
				}
				strcpy_s(send_buf, msg.c_str());
				if ((send(client_socket, send_buf, strlen(send_buf), 0)) != -1) {
					cout << send_buf << endl;
				}
			}
			else if (json_parser.getMethod(rec_buf) == constants.GET_ALL_USERS) {
				string username = json_parser.getUsername(rec_buf);
				string result = mySQLMethods.GetAllUsers(username);
				if (result != " ") {
					msg = constants.GET_ALL_USERS + " " + result;
				}
				else {
					msg = constants.GET_ALL_USERS + " Couldn't fetch all users!";
				}
				strcpy_s(send_buf, msg.c_str());
				if ((send(client_socket, send_buf, strlen(send_buf), 0)) != -1) {
					//cout << send_buf << endl;
				}
			}
			else if (json_parser.getMethod(rec_buf) == constants.SEND_FRIEND_REQUEST) {
				string sender_username = json_parser.getUsername(rec_buf);
				string receiver_username = json_parser.getReceiverUsername(rec_buf);

				int status = mySQLMethods.Message(sender_username, receiver_username, "", constants.FRIEND_REQUEST);
				if (status == 0) {
					msg = constants.SEND_FRIEND_REQUEST + " Friend Request Sent!";
				}
				else if (status == -1) {
					msg = constants.SEND_FRIEND_REQUEST + " Couldn't Send Friend Request!";
				}
				strcpy_s(send_buf, msg.c_str());
				if ((send(client_socket, send_buf, strlen(send_buf), 0)) != -1) {
					cout << send_buf << endl;
				}
			}
			else if (json_parser.getMethod(rec_buf) == constants.SAVE_PROFILE_PIC) {
				string username = json_parser.getUsername(rec_buf);
				string name = json_parser.getName(rec_buf);
				string image_url = json_parser.getProfilePictureUrl(rec_buf);
				int status = mySQLMethods.SavePictureUrl(username, image_url, name);
				if (status == 0) {
					msg = constants.SAVE_PROFILE_PIC + " Picture Uplaoded Successfuly!";
				}
				else if (status == -1) {
					msg = constants.SAVE_PROFILE_PIC + " Couldn't Upload Profile Picture!";
				}
				else if (status == 1) {
					msg = constants.SAVE_PROFILE_PIC + " Data Saved Successfully!";
				}
				else if (status == 1) {
					msg = constants.SAVE_PROFILE_PIC + " Couldn't Update your Name!";
				}
				strcpy_s(send_buf, msg.c_str());
				if ((send(client_socket, send_buf, strlen(send_buf), 0)) != -1) {
					cout << send_buf << endl;
				}
			}
			else if (json_parser.getMethod(rec_buf) == constants.FRIEND_REQUEST_ACCEPTED) {
				string sender_username = json_parser.getUsername(rec_buf);
				string receiver_username = json_parser.getReceiverUsername(rec_buf);
				int status = mySQLMethods.Message(sender_username, receiver_username, "", constants.FRIEND_REQUEST_ACCEPTED);
				if (status == 0) {
					msg = constants.SEND_FRIEND_REQUEST + " Friend Request Accepted!";
				}
				else if (status == -1) {
					msg = constants.SEND_FRIEND_REQUEST + " Couldn't Accept Friend Request!";
				}
				strcpy_s(send_buf, msg.c_str());
				if ((send(client_socket, send_buf, strlen(send_buf), 0)) != -1) {
					cout << send_buf << endl;
				}
			}
			else if (json_parser.getMethod(rec_buf) == constants.MESSAGE) {
				string sender_username = json_parser.getUsername(rec_buf);
				string receiver_username = json_parser.getReceiverUsername(rec_buf);
				string message = json_parser.getMessage(rec_buf);
				int status = mySQLMethods.Message(sender_username, receiver_username, message, constants.MESSAGE);
				if (status == 0) {
					msg = constants.MESSAGE + " Message Received!";
					cout << msg << endl;
				}
				else if (status == -1) {
					msg = constants.MESSAGE + " Couldn't receive message!";
					cout << msg << endl;
				}
//				strcpy_s(send_buf, msg.c_str());
//				if ((send(client_socket, send_buf, strlen(send_buf), 0)) != -1) {
//					cout << send_buf << endl;
//				}
			}
			else if (json_parser.getMethod(rec_buf) == constants.EVENT_REQUEST) {
				struct Node_event {
					Node_event * next = nullptr;
					string username = "";
				};
				string username_receiver = json_parser.getReceiverUsername(rec_buf);
				string username = json_parser.getUsername(rec_buf);
				string event_name = json_parser.getMessage(rec_buf);
				string event_date = json_parser.getDate(rec_buf);
				string event_time = json_parser.getTime(rec_buf);
				
				Node_event * root = nullptr;

			
				string _username_receiver = "";
				for (int i = 0; i < username_receiver.length(); i++) {
					if (username_receiver[i] == '.' && username_receiver[i + 1] == '.' && username_receiver[i + 2] == '.') {
						i = i + 2;
						Node_event * new_node = new Node_event;
						new_node->username = _username_receiver;
						_username_receiver = "";
						if (root == nullptr) {
							root = new_node;
						}
						else {
							Node_event * temp = root;
							while (temp->next != nullptr) {
								temp = temp->next;
							}
							temp->next = new_node;
						}
					}
					else {
						_username_receiver = _username_receiver + username_receiver[i];
					}
				}


				Node_event * temp = root;
				int status;
				while (temp != nullptr) {
					status = mySQLMethods.Event(event_name, username, temp->username, constants.EVENT_REQUEST, event_date, event_time);
					temp = temp->next;
				}
				if (status == 0) {
					msg = constants.EVENT_REQUEST + " Event Request Sent!";
			
				}
				else if(status == -1){
					msg = constants.EVENT_REQUEST + " Couldn't send Event Request!";
				}
				strcpy_s(send_buf, msg.c_str());
				if ((send(client_socket, send_buf, strlen(send_buf), 0)) != -1) {
					cout << send_buf << endl;
				}
				
			}

		}
		closesocket(client_socket);
	}






	closesocket(listening_socket);
	WSACleanup();
	system("pause");
}
