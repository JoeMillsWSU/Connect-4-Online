#include "Client.h"

Client::Client()
{
}

Client::~Client()
{
}

SOCKET Client::GetServer()
{
	return server;
}

void Client::Connect()
{
	WSAStartup(MAKEWORD(2, 0), &WSAData);
	server = socket(AF_INET, SOCK_STREAM, 0);

	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // replace the ip with your future server ip address. If server AND client are running on the same computer, you can use the local ip 127.0.0.1
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5555);

	connect(server, (SOCKADDR *)&addr, sizeof(addr));
	std::cout << "\tconnected to server!" << std::endl;
}
