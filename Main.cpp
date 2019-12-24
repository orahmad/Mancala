#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "Side.h"
#include <iostream>
#include <cassert>
using namespace std;

//void doGameTests()
//{
//	BadPlayer bp1("Bart");
//	BadPlayer bp2("Homer");
//	Board b(3, 0);
//	b.setBeans(SOUTH, 1, 2);
//	b.setBeans(NORTH, 2, 1);
//	b.setBeans(NORTH, 3, 2);
//	Game g(b, &bp1, &bp2);
//	bool over;
//	bool hasWinner;
//	Side winner;
//	//    Homer
//	//   0  1  2
//	// 0         0
//	//   2  0  0
//	//    Bart
//	g.status(over, hasWinner, winner);
//	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 0 &&
//		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
//		g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
//
//	g.move();
//	//   0  1  0
//	// 0         3
//	//   0  1  0
//	g.status(over, hasWinner, winner);
//	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
//		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 0 &&
//		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);
//
//	g.move();
//	//   1  0  0
//	// 0         3
//	//   0  1  0
//	g.status(over, hasWinner, winner);
//	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
//		g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
//		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);
//
//	g.move();
//	//   1  0  0
//	// 0         3
//	//   0  0  1
//	g.status(over, hasWinner, winner);
//	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
//		g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
//		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 1);
//
//	g.move();
//	//   0  0  0
//	// 1         4
//	//   0  0  0
//	g.status(over, hasWinner, winner);
//	assert(over && g.beans(NORTH, POT) == 1 && g.beans(SOUTH, POT) == 4 &&
//		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
//		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
//	assert(hasWinner && winner == SOUTH);
//}
//
//int main()
//{
//	doGameTests();
//	cout << "Passed all tests" << endl;
//}

//#include "Board.h"
//#include "Side.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//void doBoardTests()
//{
	/*Board b(3, 2);
	assert(b.holes() == 3 && b.totalBeans() == 12 &&
		b.beans(SOUTH, POT) == 0 && b.beansInPlay(SOUTH) == 6);
	b.setBeans(SOUTH, 1, 1);
	b.moveToPot(SOUTH, 2, SOUTH);
	assert(b.totalBeans() == 11 && b.beans(SOUTH, 1) == 1 &&
		b.beans(SOUTH, 2) == 0 && b.beans(SOUTH, POT) == 2 &&
		b.beansInPlay(SOUTH) == 3);
	Side es;
	int eh;
	b.sow(SOUTH, 3, es, eh);
	assert(es == NORTH && eh == 3 && b.beans(SOUTH, 3) == 0 &&
		b.beans(NORTH, 3) == 3 && b.beans(SOUTH, POT) == 3 &&
		b.beansInPlay(SOUTH) == 1 && b.beansInPlay(NORTH) == 7);
	b.setBeans(NORTH, 3, 4);
	b.sow(NORTH, 3, es, eh);
	assert(es == SOUTH && eh == 1 && b.beans(SOUTH, 3) == 0 &&
		b.beans(NORTH, 3) == 0 && b.beans(NORTH, POT) == 1 &&
		b.beansInPlay(SOUTH) == 2 && b.beansInPlay(NORTH) == 6 && b.beans(NORTH, 1) == 3);*/
//}
//
//int main()
//{
//	doBoardTests();
//	cout << "Passed all tests" << endl;
//}


int main()
{
	HumanPlayer hp("Marge");
	SmartPlayer sp("Homer");
	Board b(3, 2);
	Game g(b, &hp, &sp);
	g.play();
}