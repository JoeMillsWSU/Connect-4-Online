#include "Board.h"

Board::Board()
{
	for (int y = 0; y < BOARD_ROWS; y++)
	{
		for (int x = 0; x < BOARD_COLUMNS; x++)
		{
			this->board[y][x].token_state = State(0);
		}
		std::cout << std::endl;
	}
}
Board::~Board() { }
int Board::PlaceToken(int column, Token t)
{
	int final_row = 0;
	if (this->board[0][column].token_state != 0)
	{
		return false;
	}
	bool is_placed = false;
	for (int row = 0; row < BOARD_ROWS - 1; row++)
	{
		if (this->board[row + 1][column].token_state != 0)
		{
			this->board[row][column] = t;
			final_row = row;
			is_placed = true;
			break;
		}
	}
	if (!is_placed)
	{
		this->board[BOARD_ROWS - 1][column] = t;
		final_row = BOARD_ROWS - 1;
	}
	return final_row;
}
bool Board::DidTokenPlacementWinGame(int col, int row)
{
	int new_token_token_state = this->board[row][col].token_state;
	// horizontal
	int horizontal_in_a_row = 1;
	// horizontal - left
	for (int x = col - 1; x >= std::max(0, col - TOKENS_IN_A_ROW_NEEDED + 1); x--)
	{
		if (this->board[row][x].token_state == new_token_token_state)
		{
			horizontal_in_a_row++;
			if (horizontal_in_a_row == TOKENS_IN_A_ROW_NEEDED)
			{
				return true;
			}
		}
		else
		{
			break;
		}
	}
	// horiontal - right
	for (int x = col + 1; x <= std::min(BOARD_COLUMNS - 1, col + TOKENS_IN_A_ROW_NEEDED - 1); x++)
	{
		if (this->board[row][x].token_state == new_token_token_state)
		{
			horizontal_in_a_row++;
			if (horizontal_in_a_row == TOKENS_IN_A_ROW_NEEDED)
			{
				return true;
			}
		}
		else
		{
			break;
		}
	}
	// vertical - only need to check downwards 4-in-a-row
	int vertical_in_a_row = 0;
	for (int y = row; y <= std::min(BOARD_ROWS - 1, row + TOKENS_IN_A_ROW_NEEDED - 1); y++)
	{
		if (this->board[y][col].token_state == new_token_token_state)
		{
			vertical_in_a_row++;
			if (vertical_in_a_row == TOKENS_IN_A_ROW_NEEDED)
			{
				return true;
			}
		}
		else
		{
			break;
		}
	}
	// diagonal - top-left to bottom-right
	int diagonal_top_left_to_bottom_right = 1;
	// diagonal - left-up
	int x = col - 1;
	int y = row - 1;
	for (; x >= std::max(0, col - TOKENS_IN_A_ROW_NEEDED + 1), y >= std::max(0, row - TOKENS_IN_A_ROW_NEEDED + 1); x--, y--)
	{
		if (this->board[y][x].token_state == new_token_token_state)
		{
			diagonal_top_left_to_bottom_right++;
			if (diagonal_top_left_to_bottom_right == TOKENS_IN_A_ROW_NEEDED)
			{
				return true;
			}
		}
		else
		{
			break;
		}
	}
	// diagonal - right-down
	x = col + 1;
	y = row + 1;
	for (; x <= std::min(BOARD_COLUMNS - 1, col + TOKENS_IN_A_ROW_NEEDED - 1), y <= std::min(BOARD_ROWS - 1, row + TOKENS_IN_A_ROW_NEEDED - 1); x++, y++)
	{
		if (this->board[y][x].token_state == new_token_token_state)
		{
			diagonal_top_left_to_bottom_right++;
			if (diagonal_top_left_to_bottom_right == TOKENS_IN_A_ROW_NEEDED)
			{
				return true;
			}
		}
		else
		{
			break;
		}
	}
	// diagonal - bottom-left to top-right
	int diagonal_bottom_left_to_top_right = 1;
	// diagonal - left-down
	x = col - 1;
	y = row + 1;
	for (; x >= std::max(0, col - TOKENS_IN_A_ROW_NEEDED + 1), y <= std::min(BOARD_ROWS - 1, row + TOKENS_IN_A_ROW_NEEDED - 1); x--, y++)
	{
		if (this->board[y][x].token_state == new_token_token_state)
		{
			diagonal_bottom_left_to_top_right++;
			if (diagonal_bottom_left_to_top_right == TOKENS_IN_A_ROW_NEEDED)
			{
				return true;
			}
		}
		else
		{
			break;
		}
	}
	// diagonal - right-up
	x = col + 1;
	y = row - 1;
	for (; x <= std::min(BOARD_COLUMNS - 1, col + TOKENS_IN_A_ROW_NEEDED - 1), y >= std::max(0, row - TOKENS_IN_A_ROW_NEEDED + 1); x++, y--)
	{
		if (this->board[y][x].token_state == new_token_token_state)
		{
			diagonal_bottom_left_to_top_right++;
			if (diagonal_bottom_left_to_top_right == TOKENS_IN_A_ROW_NEEDED)
			{
				return true;
			}
		}
		else
		{
			break;
		}
	}

	return false;
}
void Board::PrintBoard()
{
	std::cout << std::endl;
	for (int y = 0; y < BOARD_ROWS; y++)
	{
		for (int x = 0; x < BOARD_COLUMNS; x++)
		{
			switch (this->board[y][x].token_state)
			{
			case(0):
				std::cout << "  ";
				break;
			case(1):
				std::cout << "X ";
				break;
			case(2):
				std::cout << "O ";
				break;
			default:
				break;
			}
		}
		std::cout << std::endl;
	}
	std::cout << "- - - - - - -" << std::endl;
	std::cout << "1 2 3 4 5 6 7" << std::endl;
}
