#pragma once
#pragma comment (lib, "ws2_32.lib")
#include <WS2tcpip.h>
#include <string>
#include <iostream>
#include <thread>
#include "GameMap.h"
#include "TankRenderer.h"
#include "BulletRenderer.h"
#include "TankRenderer.h"
#include "sstream"

#define KEY_ENTER 13
#define KEY_ESCAPE 27
#define KEY_SPACE 32


class Client
{
public:
	Client(std::string name);
	int initializeClientServer();
	static int sendData(SOCKET clientSOCK, int clientIndex);
	static int receiveData(SOCKET clientSOCK);
	static void renderTanks(int clientIndex);
	static void acceptData(std::string dataPacket);

private:
	std::string port = "80";
<<<<<<< Updated upstream
	std::string hostIP = "192.168.1.129";
=======
	std::string hostIP = "192.168.1.116";
>>>>>>> Stashed changes
	std::string playerName;
	int clientIndex;
};

