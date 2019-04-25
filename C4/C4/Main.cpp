#include <SFML\Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include "Board.h"
#include "Client.h"
#include "Server.h"

Client client;
Server server;
Board board = Board();

bool is_server;

int GetUserInput(int lower, int upper);
void Start();
void PrintStartMenu();
void ClientGameLoop();
void ServerGameLoop();
void CloseSockets();
void Exit();

void RenderingThread(sf::RenderWindow * window);

int main(void)
{
	Start();

	// create the window (remember: it's safer to create it in the main thread due to OS limitations)
	sf::RenderWindow window(sf::VideoMode(700, 650), "Connect 4");

	// deactivate its OpenGL context
	window.setActive(false);

	// launch the rendering thread
	sf::Thread thread(&RenderingThread, &window);
	thread.launch();

	is_server ? ServerGameLoop() : ClientGameLoop();

	CloseSockets();
	Exit();
	return 0;
}
int GetUserInput(int lower, int upper)
{
	std::string user_input;
	bool is_input_valid = false;
	do
	{
		is_input_valid = true;
		std::cout << "\t ";
		std::cin >> user_input;
		int length = user_input.length();
		for (int i = 0; i < length; i++) // is each char in the user input a digit?
		{
			if (!isdigit(user_input[i]))
			{
				is_input_valid = false;
				system("CLS");
				PrintStartMenu();
				break;
			}
		}
		if (is_input_valid) // is user input within bounds?
		{
			int numerical_input = std::stoi(user_input);
			if (numerical_input < lower || numerical_input > upper)
			{
				is_input_valid = false;
				system("CLS");
				PrintStartMenu();
			}
		}
	} while (!is_input_valid);
	return std::stoi(user_input);
}
void Start()
{
	PrintStartMenu();
	int user_menu_selection = GetUserInput(1, 3);
	std::string str;
	std::string ip;
	switch (user_menu_selection)
	{
	case(1):
		server = Server();
		server.Connect();
		str = ("Connect 4 - Server");
		SetConsoleTitle(str.c_str());
		is_server = true;
		break;
	case(2):
		client = Client();
		client.Connect();
		str = ("Connect 4 - Client");
		SetConsoleTitle(str.c_str());
		is_server = false;
		break;
	case(3):
		client = Client();
		std::cout << std::endl << "\tEnter IP: ";
		std::cin >> ip;
		client.Connect(ip);
		str = ("Connect 4 - Client");
		SetConsoleTitle(str.c_str());
		is_server = false;
		break;
	default:
		break;
	}
}
void PrintStartMenu()
{
	system("CLS");
	std::cout << std::endl;
	std::cout << "\t" << "[1]" << "\t" << "Start game" << std::endl;
	std::cout << "\t" << "[2]" << "\t" << "Join game" << std::endl;
	std::cout << "\t" << "[3]" << "\t" << "Direct IP" << std::endl << std::endl;
}
void ClientGameLoop()
{
	bool is_game_over = false;
	//Board board = Board();
	char buffer[512];

	// update board
	system("CLS");
	board.PrintBoard();
	
	while (!is_game_over)
	{
		// listen
		recv(client.GetServer(), buffer, sizeof(buffer), 0);
		int server_column_selection = buffer[0] - '0';
		memset(buffer, 0, sizeof(buffer));

		Token server_token = Token(State(1));
		int server_token_row_position = board.PlaceToken(server_column_selection, server_token);
		is_game_over = board.DidTokenPlacementWinGame(server_column_selection, server_token_row_position);
		// did server move end game? 
		if (is_game_over)
		{
			std::cout << std::endl << "\tYou lose. " << std::endl;
			break;
		}

		// update board
		system("CLS");
		board.PrintBoard();
		
		// make move
		int client_column_selection = GetUserInput(1, 7) - 1;
		Token client_token = Token(State(2));
		buffer[0] = client_column_selection + '0';
		send(client.GetServer(), buffer, sizeof(buffer), 0);
		memset(buffer, 0, sizeof(buffer));
		int client_token_row_position = board.PlaceToken(client_column_selection, client_token);
		is_game_over = board.DidTokenPlacementWinGame(server_column_selection, server_token_row_position);
		// did client move end game? 
		if (is_game_over)
		{
			std::cout << std::endl << "\tYou win. " << std::endl;
			break;
		}

		// update board
		system("CLS");
		board.PrintBoard();
	}

	// update board one last time
	system("CLS");
	board.PrintBoard();

}
void ServerGameLoop()
{
	bool is_game_over = false;
	//Board board = Board();
	// update board
	system("CLS");
	board.PrintBoard();
	char buffer[512];
	do
	{
		// make move
		int server_column_selection = GetUserInput(1, 7) - 1;
		Token server_token = Token(State(1));
		buffer[0] = server_column_selection + '0';
		send(server.GetClient(), buffer, sizeof(buffer), 0);
		memset(buffer, 0, sizeof(buffer));

		int server_token_row_position = board.PlaceToken(server_column_selection, server_token);
		is_game_over = board.DidTokenPlacementWinGame(server_column_selection, server_token_row_position);
		
		// update board
		system("CLS");
		board.PrintBoard();

		// did server move end game? 
		if (is_game_over)
		{
			std::cout << std::endl << "\tYou win. " << std::endl;
			break;
		}

		// listen
		recv(server.GetClient(), buffer, sizeof(buffer), 0);
		int client_column_selection = buffer[0] - '0';
		memset(buffer, 0, sizeof(buffer));
		Token client_token = Token(State(2));
		int client_token_row_position = board.PlaceToken(client_column_selection, client_token);
		is_game_over = board.DidTokenPlacementWinGame(client_column_selection, client_token_row_position);
		
		// update board
		system("CLS");
		board.PrintBoard();

		// did client move end game? 
		if (is_game_over)
		{
			std::cout << std::endl << "\tYou lose. " << std::endl;
			break;
		}

	} while (!is_game_over);

	// update board one last time
	system("CLS");
	board.PrintBoard();
}
void CloseSockets()
{
	if (is_server)
	{
		server.CloseSocket();
	}
	else
	{
		client.CloseSocket();
	}
}
void Exit()
{
	std::cout << std::endl << "\tPress [Enter] to exit. ";
	std::string a = "";
	std::cin >> a;
}

void RenderingThread(sf::RenderWindow * window)
{
	float cell_thiccness = 2.0f;
	float token_width = 45.f;
	float cell_width = 50.f;
	float token_offset = (cell_thiccness/2) + ((cell_width - token_width) / 1);

	sf::RectangleShape grid[7][6];
	sf::CircleShape token_graphic_objects[BOARD_ROWS][BOARD_COLUMNS];

	// activate the window's context
	window->setActive(true);

	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}

	// the rendering loop
	while (window->isOpen())
	{
		// draw grid
		window->clear();
		sf::Vector2f cellSize(100.0f, 100.0f);

		for (int i = 0; i < BOARD_COLUMNS; i++) 
		{
			for (int j = 0; j < BOARD_ROWS; j++) 
			{
				grid[i][j].setSize(cellSize);
				grid[i][j].setOutlineColor(sf::Color::White);
				grid[i][j].setFillColor(sf::Color::Transparent);
				grid[i][j].setOutlineThickness(cell_thiccness);
				grid[i][j].setPosition(i*cellSize.x + (cell_thiccness /2), j*cellSize.y + (cell_thiccness /2));

				window->draw(grid[i][j]);
			}
		}
		
		// drawing tokens
		for (int row = 0; row < BOARD_ROWS; row++)
		{
			for (int col = 0; col < BOARD_COLUMNS; col++)
			{
				token_graphic_objects[row][col] = sf::CircleShape(token_width);
				if (board.board[row][col].token_state == 1)
				{
					token_graphic_objects[row][col].setFillColor(sf::Color::Red);
				}
				else if (board.board[row][col].token_state == 2)
				{
					token_graphic_objects[row][col].setFillColor(sf::Color::Blue);
				}
				else
				{
					token_graphic_objects[row][col].setFillColor(sf::Color::Transparent);
				}
				int x = col * 100;
				int y = row * 100;
				token_graphic_objects[row][col].setPosition(x + token_offset, y + token_offset);
				window->draw(token_graphic_objects[row][col]);
			}
		}

		// end the current frame
		window->display();
	}
}
