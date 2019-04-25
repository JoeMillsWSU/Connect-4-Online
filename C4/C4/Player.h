#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <winsock2.h>
#include "Board.h"
#include <string>

class Player
{
public:
	Player();
	~Player();
	void Connect();
	void CloseSocket();
	int RecieveMove();
	int MakeMove(int column_selection);
protected:
	WSADATA WSAData;
	 SOCKET server;
};

