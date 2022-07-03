#pragma once
#pragma comment (lib, "ws2_32.lib")
#include <WS2tcpip.h>
#include <string>
#include <iostream>
#include <thread>

class Client
{
public:
	Client(std::string name);
	int initializeClientServer();
	static int sendData(SOCKET clientSOCK);
private:
	std::string hostIP = "127.0.0.1";
	std::string port = "13337";
	std::string playerName;
};

