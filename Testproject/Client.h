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

#define KEY_ENTER 13
#define KEY_ESCAPE 27
#define KEY_SPACE 32

class Client
{
public:
	Client(std::string name);
	int initializeClientServer();
	static int sendData(SOCKET clientSOCK);
	static int receiveData(SOCKET clientSOCK);
	static int setTankInformation(SOCKET clientSOCK);
private:
	std::string port = "80";
	std::string hostIP = "192.168.1.129";
	std::string playerName;
	int clientIndex;
};

