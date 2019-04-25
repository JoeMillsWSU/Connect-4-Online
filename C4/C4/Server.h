#pragma once

#include "Player.h"

class Server : public Player
{
public:
	Server();
	~Server();
	SOCKET GetClient();
	void Connect();
private:
	SOCKADDR_IN serverAddr, clientAddr;
	SOCKET client;
};

