#include "Server.h"

Server::Server()
{
}

Server::~Server()
{
}

SOCKET Server::GetClient()
{
	return this->client;
}

void Server::Connect()
{
	WSAStartup(MAKEWORD(2, 0), &WSAData);
	server = socket(AF_INET, SOCK_STREAM, 0);

	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(5555);

	bind(server, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
	listen(server, 0);

	std::cout << "\tlistening for incoming connections..." << std::endl;

	int clientAddrSize = sizeof(clientAddr);
	if ((client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
	{
		std::cout << "\tclient connected!" << std::endl;
	}
}
