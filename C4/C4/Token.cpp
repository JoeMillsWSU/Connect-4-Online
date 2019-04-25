#include "Token.h"

Token::Token() { }

Token::Token(State s)
{
	this->token_state = s;
}

Token::~Token() { }
