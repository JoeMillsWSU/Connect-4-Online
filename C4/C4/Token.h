#pragma once
enum State
{
	empty = 0,
	player_1 = 1,
	player_2 = 2
};
class Token
{
public:
	Token();
	Token(State s);
	~Token();
	State token_state;
};

