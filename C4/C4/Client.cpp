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

	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // If server AND client are running on the same computer, you can use the local ip 127.0.0.1
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5555);

	connect(server, (SOCKADDR *)&addr, sizeof(addr));
	std::cout << "\tconnected to server!" << std::endl;
}
void Client::Connect(std::string target_ip_address)
{
	WSAStartup(MAKEWORD(2, 0), &WSAData);
	server = socket(AF_INET, SOCK_STREAM, 0);
	const char * ip = target_ip_address.c_str();
	addr.sin_addr.s_addr = inet_addr(ip); 
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5555);

	connect(server, (SOCKADDR *)&addr, sizeof(addr));
	std::cout << "\tconnected to server!" << std::endl;
}
