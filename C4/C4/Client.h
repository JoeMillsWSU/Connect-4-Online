#pragma once

#include "Player.h"

class Client : public Player
{
public:
	Client();
	~Client();
	SOCKET GetServer();
	void Connect();
private:
	SOCKADDR_IN addr;
};

