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

}

int Server::acceptPlayer(SOCKET listenSOCK)
{
	std::cout << "Server: Waiting for players to join...";
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
			std::thread sendDataHandle(sendData, ClientSocket);
			sendDataHandle.detach();
			std::thread recvDataHandle(recvData, ClientSocket);
			recvDataHandle.detach();
			FD_SET(ClientSocket, &master);
			auto tankIndex = std::to_string(totalPlayersOnServer);
			send(master.fd_array[totalPlayersOnServer], tankIndex.c_str(), strlen(tankIndex.c_str()), 0);
			totalPlayersOnServer++;
		}
	}
	return 1;
}


int Server::sendData(SOCKET listenSOCK)
{
	return 1;
}


int Server::recvData(SOCKET listenSOCK)
{
	char dataBuffer[100];
	const char* buffer;
	int xCoord, yCoord, tankDirection, index;
	while (true) {
		recv(listenSOCK, dataBuffer, 100, 0);
		buffer = dataBuffer;
		explode(buffer, '_');
	}
	return 1;
}


std::vector<int> Server::explode(const char* charStr, const char& ch) {

	std::string str = charStr, next;
	std::vector<int> result;
	int arr[4], i = 0;
	for (std::string::const_iterator it = str.begin(); it != str.end(); it++) {
		if (*it == ch) {
			if (!next.empty()) {
				arr[i] = stoi(next);
				i = i + 1;
				next.clear();
			}
		}
		else {
			next += *it;
		}
	}

	std::cout << arr[0]<<" ";

	Sleep(1000);
	return result;
}
