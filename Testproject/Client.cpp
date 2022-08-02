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

	char tankIndex[1];
	recv(sock, tankIndex, 1, 0);
	clientIndex = std::stoi(tankIndex);
	Positions::getInstance()->setClientIndex(clientIndex);

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
	TankRenderer clientTank;
	clientTank.setTankPosition(0, 0, 0);
	BulletRenderer newBullet(&newTank);
	BulletRenderer clientBullet(&clientTank);
	tankPosition tankInformation;

	int inactiveTank;
	std::string xCoord, yCoord, tankDirection, index, dataBuffer, pressedKey;

	newTank.renderTank();

	std::thread animateDeath(&TankRenderer::deathAnimation, newTank);
	std::thread animateBullets(&BulletRenderer::renderBullets, &newBullet);
	std::thread animateOtherBullets(&BulletRenderer::renderBullets, &clientBullet);

	animateBullets.detach();
	animateDeath.detach();
	animateOtherBullets.detach();

	while (true) {

		if (Positions::getInstance()->getBulletStatus() == true)
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			
			clientTank.setTankPosition(Positions::getInstance()->getBulletCoordinates().x,
				Positions::getInstance()->getBulletCoordinates().y,
				Positions::getInstance()->getBulletCoordinates().direction);
			clientBullet.addBullet();	
			Positions::getInstance()->setSendBulletFalse();
		}


		bool isKeyPressed = _kbhit();
		int keyPressed;
		if (isKeyPressed)
		{
			keyPressed = _getch();
			if (keyPressed == 224)
				keyPressed = _getch();

			if (keyPressed == KEY_SPACE)
			{
				newBullet.addBullet();
				xCoord = std::to_string(newTank.getCurrentTankPosition().x);
				yCoord = std::to_string(newTank.getCurrentTankPosition().y);
				tankDirection = std::to_string(newTank.getTankDirection());
				index = std::to_string(clientIndex);
				pressedKey = std::to_string(keyPressed);
				dataBuffer = xCoord + " " + yCoord + " " + tankDirection + " " + index + " " + pressedKey + "1 1";

				send(clientSOCK, dataBuffer.c_str(), dataBuffer.length() + 1, 0);
			}
			else if (keyPressed == KEY_ESCAPE)
			{
				newTank.clearTank();
				dataBuffer = "0 0 0 " + index + "0 0 0";
				send(clientSOCK, dataBuffer.c_str(), dataBuffer.length() + 1, 0);
				closesocket(clientSOCK);
				WSACleanup();
			}
			else
			{
				xCoord = std::to_string(newTank.getCurrentTankPosition().x);
				yCoord = std::to_string(newTank.getCurrentTankPosition().y);
				tankDirection = std::to_string(newTank.getTankDirection());
				index = std::to_string(clientIndex);
				pressedKey = std::to_string(keyPressed);
				dataBuffer = xCoord + " " + yCoord + " " + tankDirection + " " + index + " " + pressedKey + " 0 1";
				Positions::getInstance()->updateTankPosition(std::stoi(xCoord), std::stoi(yCoord), std::stoi(tankDirection), std::stoi(index));
				send(clientSOCK, dataBuffer.c_str(), dataBuffer.length() + 1, 0);
				newTank.moveTank(keyPressed);
			}
		}

		if (Positions::getInstance()->getTankStatus(clientIndex) == false && newTank.isTankDisabled())
		{
			newTank.disableTank();

		}
	}
	return 1;
}


int Client::receiveData(SOCKET clientSOCK)
{
	char dataBuffer[20];
	int result;
	while (true) {
		result = recv(clientSOCK, dataBuffer, 20, 0);
		acceptData(dataBuffer);
	}
	return 1;
}

void Client::acceptData(std::string dataPacket)
{
	std::istringstream is(dataPacket);
	int xCoord, yCoord, tankDirection, index, n, totalTankAmount, pressedKey, status, addBullet, totalPlayerCount;
	is >> xCoord >> yCoord >> tankDirection >> index >> pressedKey >> addBullet>> status >> totalPlayerCount;
	Positions::getInstance()->updateTankPosition(xCoord, yCoord, tankDirection, index);
	//std::cout << "Index: " << index << std::endl;

	if (index == Positions::getInstance()->getClientIndex())
		return;
	if (status == 0)
	{
		return;
	}


	if (addBullet == 1)
	{
		Positions::getInstance()->setSendBulletTrue();
		Positions::getInstance()->setBulletCoordinates(xCoord, yCoord, tankDirection);
	}
	TankRenderer customTankRenderer(xCoord, yCoord, tankDirection, index, totalPlayerCount);
	customTankRenderer.moveTank(pressedKey);
	return;
}
