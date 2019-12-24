#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <vector>
#include "Board.h"
#include "Side.h"

class Player
{
public:
	Player(std::string name);
	std::string name() const;
	virtual bool isInteractive() const;
	virtual int chooseMove(const Board& b, Side s) const = 0;
	virtual ~Player();
private:
	string m_name;
};

class BadPlayer : public Player
{
public:
	BadPlayer(std::string name);
	virtual int chooseMove(const Board& b, Side s) const;
	virtual ~BadPlayer();
};

class HumanPlayer : public Player
{
public:
	HumanPlayer(std::string name);
	virtual bool isInteractive() const;
	virtual int chooseMove(const Board& b, Side s) const;
	virtual ~HumanPlayer();
};

class SmartPlayer : public Player
{
public:
	SmartPlayer(std::string name);
	virtual int chooseMove(const Board& b, Side s) const;
	virtual ~SmartPlayer();
private:
	GameTree* m_privr;
};


#endif
