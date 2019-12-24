#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include "Side.h"
using namespace std;


class Board
{
public:
	Board(int nHoles, int nInitialBeansPerHole);
	Board(const Board& src);
	Board &operator=(const Board& src);
	int holes() const;
	int beans(Side s, int hole) const;
	int beansInPlay(Side s) const;
	int totalBeans() const;
	bool sow(Side s, int hole, Side& endSide, int& endHole);
	bool moveToPot(Side s, int hole, Side potOwner);
	bool setBeans(Side s, int hole, int beans);
	~Board();
private:
	enum type { SOUTHHOLE, NORTHHOLE, SOUTHPOT, NORTHPOT };
	class hole
	{
	public:
		hole();
		hole(const hole& src);
		hole(int number, type whichOne);
		int holes_beans() const;
		void set_holes_beans(int num);
		int enum_getter() const;
	private:
		int number_beans;
		type definer;
	};
	vector<hole*> vec;
};

#endif