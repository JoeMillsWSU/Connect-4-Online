#pragma once

#include "Player.h"

class Client : public Player
{
public:
	Client();
	~Client();
	SOCKET GetServer();
	void Connect();
	void Connect(std::string target_ip_address);
private:
	SOCKADDR_IN addr;
};

