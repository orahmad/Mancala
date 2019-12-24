#ifndef GAME_H
#define GAME_H
#include "Board.h"
#include "Side.h"
#include "Player.h"
#include <iostream>
using namespace std;

class Game
{
public:
	Game(const Board& b, Player* south, Player* north);
	void display() const;
	void status(bool& over, bool& hasWinner, Side& winner) const;
	bool move();
	void play();
	int beans(Side s, int hole) const;
private:
	Board copy;
	Player *s;
	Player *n;
	Side whoseTurn;
	void changeTurn(Side figure);
};

#endif
