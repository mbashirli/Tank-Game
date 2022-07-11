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
	static int recvData(SOCKET listenSOCK);
	static int sendData(SOCKET listenSOCK);
	static playerInformation acceptData(std::string dataPacket);
private:
	std::string port = "80";
<<<<<<< Updated upstream
	std::string hostIP = "192.168.1.129";
=======
	std::string hostIP = "192.168.1.116";
>>>>>>> Stashed changes
	static std::vector <playerInformation> playersData;
	enum directionPoints {UP, DOWN, RIGHT, LEFT};
};

