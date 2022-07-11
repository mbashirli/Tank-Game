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

			FD_SET(ClientSocket, &master);
			std::string tankIndex = std::to_string(totalPlayersOnServer);
			send(master.fd_array[totalPlayersOnServer], tankIndex.c_str(), strlen(tankIndex.c_str()), 0);

			std::thread recvDataHandle(recvData, ClientSocket, std::stoi(tankIndex));
			recvDataHandle.detach();
			totalPlayersOnServer++;

		}
	}

	return 1;
}


int Server::recvData(SOCKET listenSOCK, int playerIndex)
{
	std::string sendableDataBuffer, xCoord, yCoord, tankDirection;
	int i = 0;
	char clientName[50];
	int result;
	recv(listenSOCK, clientName, 50, 0);
	std::cout << clientName << " has joined the server" << std::endl;
	std::cout << "Total players on server: " << master.fd_count << std::endl;
	char dataBuffer[20];

	while (true) {
		result = recv(listenSOCK, dataBuffer, 20, 0);
		if (result > 0)
		{
			playerInformation data = acceptData(dataBuffer);
			Positions::getInstance()->updateTankPosition(data.xCoord, data.yCoord, data.tankDirection, data.index);
			for (int i = 0; i < master.fd_count; i = i + 1)
			{
				xCoord = std::to_string(Positions::getInstance()->getTankPosition(i)->x);
				yCoord = std::to_string(Positions::getInstance()->getTankPosition(i)->y);
				tankDirection = std::to_string(Positions::getInstance()->getTankPosition(i)->direction);

				sendableDataBuffer = xCoord + " " + yCoord + " " + tankDirection + " " + std::to_string(i);
				send(master.fd_array[i], sendableDataBuffer.c_str(), sendableDataBuffer.length(), 0);
			}
		}
		else if (result <= 0)
		{
			FD_CLR(listenSOCK, &master);
			std::cout << "A player has disconnected" << std::endl;
			std::cout << "Total players on server: " << master.fd_count << std::endl;
			return 1;
		}
		else
		{

		}
	}
	return 1;
}


playerInformation Server::acceptData(std::string dataPacket)
{
	int x, y, tankDir, indx, n; playerInformation data;
	std::istringstream is(dataPacket);
	is >> x >> y >> tankDir >> indx;

	data.xCoord = x;
	data.yCoord = y;
	data.tankDirection = tankDir;
	data.index = indx;

	return data;
}