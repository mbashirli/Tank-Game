#pragma once
#pragma comment (lib, "ws2_32.lib")
#include <WS2tcpip.h>
#include <string>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include "Client.h"
#include <sstream>

static fd_set master;

struct playerInformation {
	int xCoord, yCoord, tankDirection, index;
};

class Server
{
public:
	Server();
	void generateServer();
	static int acceptPlayer(SOCKET listenSOCK);
	static int recvData(SOCKET listenSOCK, int playerIndex);
	static int sendData();
	static playerInformation acceptData(std::string dataPacket);
private:
	std::string port = "80";
	std::string hostIP = "192.168.100.12";
	static std::vector <playerInformation> playersData;
	enum directionPoints {UP, DOWN, LEFT, RIGHT};
};

