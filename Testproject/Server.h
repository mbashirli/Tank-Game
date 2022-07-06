#pragma once
#pragma comment (lib, "ws2_32.lib")
#include <WS2tcpip.h>
#include <string>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include "Client.h"

static fd_set master;


class Server
{
public:
	Server();
	void generateServer();
	static int acceptPlayer(SOCKET listenSOCK);
	static int recvData(SOCKET listenSOCK);
	static int sendData(SOCKET listenSOCK);
	static void updateTankPositions(std::string newData);
	static std::vector<int> explode(const char* charStr, const char& ch);
	static void tester();
private:
	std::string port = "80";
	std::string hostIP = "192.168.1.120";
	enum directionPoints {UP, DOWN, RIGHT, LEFT};
};

