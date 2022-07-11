#include "Server.h"


Server::Server()
{
}


void Server::generateServer()
{

	WSADATA wsadata;
	int result = WSAStartup(MAKEWORD(2, 2), &wsadata);
	if (result != 0) {
		std::cout << "WSAStartup error: " << result << std::endl;
		return;
	}
	else
	{
		std::cout << "WSAStartup OK" << std::endl;
	}

	SOCKET listenSOCK = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenSOCK == INVALID_SOCKET) {
		std::cout << "listenSOCK error: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return;
	}
	else
	{
		std::cout << "listenSOCK OK" << std::endl;
	}

	struct addrinfo* res = NULL;
	struct addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
	result = getaddrinfo(NULL, port.c_str(), &hints, &res);

	if (result != 0) {
		std::cout << "getaddrinfo error: " << WSAGetLastError() << std::endl;
		closesocket(listenSOCK);
		WSACleanup();
		return;
	}
	else
	{
		std::cout << "getaddrinfo OK" << std::endl;
	}

	result = ::bind(listenSOCK, res->ai_addr, (int)res->ai_addrlen);
	if (result == SOCKET_ERROR) {
		std::cout << "bind error: " << WSAGetLastError() << std::endl;
		closesocket(listenSOCK);
		WSACleanup();
		return;
	}
	else
	{
		std::cout << "bind OK" << std::endl;
	}
	freeaddrinfo(res);

	result = listen(listenSOCK, SOMAXCONN);
	if (result == SOCKET_ERROR) {
		std::cout << "listen error: " << WSAGetLastError() << std::endl;
		closesocket(listenSOCK);
		WSACleanup();
		return;
	}
	else
	{
		std::cout << "listen OK" << std::endl;
	}
	std::thread acceptPlayers(acceptPlayer, listenSOCK);
	acceptPlayers.join();

	WSACleanup();
	return;
}

int Server::acceptPlayer(SOCKET listenSOCK)
{
	std::cout << "Server: Waiting for players to join..." << std::endl;
	int totalPlayersOnServer = 0;
	while (true) {
		SOCKET ClientSocket = accept(listenSOCK, NULL, NULL);
		if (ClientSocket == INVALID_SOCKET)
		{
			std::cout << "accept error: " << WSAGetLastError() << std::endl;
			closesocket(ClientSocket);
		}
		else
		{
			std::thread recvDataHandle(recvData, ClientSocket);
			recvDataHandle.detach();
			std::thread sendDataHandle(sendData, ClientSocket);
			sendDataHandle.detach();
			FD_SET(ClientSocket, &master);
			std::string tankIndex = std::to_string(totalPlayersOnServer);
			send(master.fd_array[totalPlayersOnServer], tankIndex.c_str(), strlen(tankIndex.c_str()), 0);
			Positions::getInstance()->increaseTankAmount();
			totalPlayersOnServer++;
		}
	}
	return 1;
}


int Server::sendData(SOCKET listenSOCK)
{
	std::string dataBuffer, xCoord, yCoord, tankDirection;
	int i = 0;
	while (true)
	{
		for (i = 0; i < Positions::getInstance()->getTotalTanks(); i = i + 1)
		{
			/*xCoord = std::to_string(Positions::getInstance()->getTankPosition(i)->x);
			yCoord = std::to_string(Positions::getInstance()->getTankPosition(i)->y);
			tankDirection = std::to_string(Positions::getInstance()->getTankPosition(i)->direction);
			dataBuffer = xCoord + " " + yCoord + " " + tankDirection + " " + std::to_string(i);*/
			//	send(listenSOCK, dataBuffer.c_str(), dataBuffer.length(), 0)
		}
		dataBuffer = "631 69 2 2 ";
		send(listenSOCK, dataBuffer.c_str(), dataBuffer.length(), 0);
	}
	return 1;
}


int Server::recvData(SOCKET listenSOCK)
{
	char clientName[50];
	int result;
	recv(listenSOCK, clientName, 50, 0);
	std::cout << clientName << " has joined the server" << std::endl;
	std::cout << "Total players on server: " << Positions::getInstance()->getTotalTanks() << std::endl;

	char dataBuffer[20];


	while (true) {
		result = recv(listenSOCK, dataBuffer, 20, 0);
		if (result > 0)
		{
			Application::getInstance()->lockCout();
			playerInformation data = acceptData(dataBuffer);
			//Positions::getInstance()->updateTankPosition(data.index, data.xCoord, data.yCoord, data.tankDirection);
			Application::getInstance()->unlockCout();
		}
		else if (result <= 0)
		{
			FD_CLR(listenSOCK, &master);
			std::cout << "A player has disconnected" << std::endl;
			Positions::getInstance()->decreaseTankAmount();
			std::cout << "Total players on server: " << Positions::getInstance()->getTotalTanks() << std::endl;
			return 1;
		}
	}
	return 1;
}


playerInformation Server::acceptData(std::string dataPacket)
{
	std::istringstream is(dataPacket);
	int xCoord, yCoord, tankDirection, index, n;
	is >> xCoord >> yCoord >> tankDirection >> index;
	playerInformation data = { xCoord, yCoord, tankDirection, index };
	return data;
}