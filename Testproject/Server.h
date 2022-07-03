#pragma once
#pragma comment (lib, "ws2_32.lib")
#include <WS2tcpip.h>
#include <string>
#include <iostream>
#include <thread>

static fd_set master;

class Server
{
public:
	Server();
	void generateServer();
	static int acceptPlayer(SOCKET listenSOCK);
	static int recvAndSendData(SOCKET listenSOCK);
private:
	std::string port = "80";
	std::string hostIP = "192.168.1.120";
	static int totalPlayersOnServer;
	enum directionPoints {UP, DOWN, RIGHT, LEFT};
};

