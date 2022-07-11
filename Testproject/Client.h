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
	static void acceptData(std::string dataPacket);

private:
	std::string port = "80";
	std::string hostIP = "192.168.1.120";
	std::string playerName;
	int clientIndex;
};

