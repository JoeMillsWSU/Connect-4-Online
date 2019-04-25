#pragma once

#include "Token.h"
#include <algorithm>    // std::max
#include <iostream>

#define BOARD_COLUMNS 7
#define BOARD_ROWS 6
#define TOKENS_IN_A_ROW_NEEDED 4

class Board
{
public:
	Board();
	~Board();
	int PlaceToken(int column, Token t);
	bool DidTokenPlacementWinGame(int col, int row);
	void PrintBoard();

	Token board[6][7];

};

