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
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_RIGHT 77
#define KEY_LEFT 75

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
	std::string hostIP = "192.168.100.12";
	std::string playerName;
	int clientIndex;
};

