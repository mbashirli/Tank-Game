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
	send(sock, playerName.c_str(), strlen(playerName.c_str()) + 1, 0);

	std::thread sendDataThread(sendData, sock);
	sendDataThread.detach();

	std::thread receiveDataThread(receiveData, sock);
	receiveDataThread.join();

	closesocket(sock);
	WSACleanup();
}

int Client::sendData(SOCKET clientSOCK)
{
	while (true)
	{

	}
	return 1;
}

int Client::receiveData(SOCKET clientSOCK)
{
	GameMap::getInstance()->renderMap();
	while (true)
	{

	}

	return 1;
}