#include "Client.h"

Client::Client(std::string name)
{
	this->playerName = name;
}

int Client::initializeClientServer()
{
	int result;
	WSADATA wsaData;
	result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0) {
		std::cout << "Initialize Winsock Fail: " << result << std::endl;
		return 1;
	}
	addrinfo hints, * res;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	result = getaddrinfo(hostIP.c_str(), port.c_str(), &hints, &res);
	if (result != 0) {
		std::cout << "getaddrinfo failed: " << result << std::endl;
		return 1;
	}

	SOCKET sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (sock == INVALID_SOCKET) {
		std::cout << "Create connect sock failed: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return 1;
	}

	result = connect(sock, res->ai_addr, (int)res->ai_addrlen);

	if (result != 0) {
		std::cout << "connect failed: " << WSAGetLastError() << std::endl;
		closesocket(sock);
		WSACleanup();
		return 1;
	}
	GameMap::getInstance()->renderMap();

	send(sock, playerName.c_str(), strlen(playerName.c_str()) + 1, 0);
	
	char tankIndex[2];
	recv(sock, tankIndex, 2, 0);

	clientIndex = std::stoi(tankIndex);
	std::thread sendDataThread(sendData, sock, clientIndex);
	sendDataThread.detach();

	std::thread receiveDataThread(receiveData, sock);
	receiveDataThread.join();

	closesocket(sock);
	WSACleanup();
}





int Client::sendData(SOCKET clientSOCK, int clientIndex)
{
	TankRenderer newTank(clientIndex);
	BulletRenderer newBullet(&newTank);
	tankPosition tankInformation;

	int inactiveTank;
	std::string xCoord, yCoord, tankDirection, index, dataBuffer;

	newTank.renderTank();

	std::thread animateDeath(&TankRenderer::deathAnimation, newTank);
	std::thread animateBullets(&BulletRenderer::renderBullets, &newBullet);
	animateBullets.detach();
	animateDeath.detach();

	while (true) {
		bool isKeyPressed = _kbhit();
		if (isKeyPressed)
		{
			int keyPressed = _getch();
			if (keyPressed == KEY_SPACE)
			{
				newBullet.addBullet();
			}
			else if (keyPressed == KEY_ESCAPE)
			{
				closesocket(clientSOCK);
				WSACleanup();
			}
			else
			{
				newTank.moveTank();
			}
		}
		xCoord = std::to_string(newTank.getCurrentTankPosition().x);
		yCoord = std::to_string(newTank.getCurrentTankPosition().y);
		tankDirection = std::to_string(newTank.getTankDirection());
		index = std::to_string(clientIndex);
		
		dataBuffer = xCoord + " " + yCoord + " " + tankDirection + " " + index;
		send(clientSOCK, dataBuffer.c_str(), dataBuffer.length() + 1, 0);

		std::cout << Positions::getInstance()->getTankPosition(0)->x << std::endl;
		std::cout << Positions::getInstance()->getTankPosition(0)->y << std::endl;
	}
	return 1;
}


int Client::receiveData(SOCKET clientSOCK)
{
	char dataBuffer[20];
	int result;
	while (true) {
		result = recv(clientSOCK, dataBuffer, 20, 0);
		if (result > 0)
		{
			acceptData(dataBuffer);
		}
		else
		{
			std::cout << "ERROR" << std::endl;
			return 1;
		}
	}
	return 1;
}

void Client::acceptData(std::string dataPacket)
{
	std::istringstream is(dataPacket);
	int xCoord, yCoord, tankDirection, index, n;
	is >> xCoord >> yCoord >> tankDirection >> index;
	Positions::getInstance()->updateTankPosition(index, xCoord, yCoord, tankDirection);
}