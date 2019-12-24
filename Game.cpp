#include <iostream>
#include <string>
#include "Game.h"
#include "Board.h"
#include "Player.h"
#include "Side.h"
using namespace std;

Game::Game(const Board& b, Player* south, Player* north)
	:copy(b), s(south), n(north), whoseTurn(SOUTH)
{
}
// constructor that sets all the data members to whatever is in the parameters
// since south side always starts, whoseTurn is set to SOUTH always, until it is changed later

void Game::changeTurn(Side figure)
{
	if (figure == SOUTH)
	{
		whoseTurn = NORTH;
	}
	else
	{
		whoseTurn = SOUTH;
	}
	// private function that takes a side value and reverses the turn so that
	// at the end of each move, we can switch turns
}

void Game::display() const
{
	cout << '\t' << n->name() << endl;
	// prints out a tab and the player name as well
	for (int i = 1; i < (copy.holes() + 1); i++)
	{
		cout << "  " << copy.beans(NORTH, i);
	}
	cout << endl;
	cout << copy.beans(NORTH, 0);
	for (int i = 0; i < copy.holes(); i++)
	{
		cout << "   ";
	}
	cout << copy.beans(SOUTH, 0);
	// then prints out each pot's value
	// the north pot is printed on the left while the south is printed on the right
	cout << endl;
	for (int i = 1; i < (copy.holes() + 1); i++)
	{
		cout << "  " << copy.beans(SOUTH, i);
	}
	cout << endl;
	cout << '\t' << s->name() << endl;
	//then prints the south players name
}

void Game::status(bool& over, bool& hasWinner, Side& winner) const
{
	if (copy.beansInPlay(NORTH) == 0 || copy.beansInPlay(SOUTH) == 0)
	{
		//the if statement sees if there are zero beans in every hole on any side
		over = true;
		// if the if statement is true then the game is over
		int counterNorth = 0;
		int counterSouth = 0;
		counterNorth = copy.beansInPlay(NORTH) + copy.beans(NORTH, 0);
		counterSouth = copy.beansInPlay(SOUTH) + copy.beans(SOUTH, 0);
		// this then adds the remaining beans on the other side to their respected pot
		if (counterNorth > counterSouth || counterSouth > counterNorth)
		{
			// this if statement makes sure it's not a tie and there actually is a winner
			hasWinner = true;
			if (counterNorth > counterSouth)
			{
				winner = NORTH;
			}
			else
			{
				winner = SOUTH;
			}
		}
	}
	else
	{
		over = false;
	}
}

bool Game::move()
{
	bool test;
	bool useless;
	Side noth;
	int tester;
	status(test, useless, noth);
	if (test == true)
	{
		for (int i = 0; i < copy.holes() + 1; i++)
		{
			copy.moveToPot(NORTH, i, NORTH);
			copy.moveToPot(SOUTH, i, SOUTH);
		}
		return false;
		// from the beginning we check the status of the game before advancing forward
	}
	if (whoseTurn == SOUTH)
	{
		// if it's south's turn then we have to sow the sourth side based on how
		// the south player chooses the hole
		copy.sow(whoseTurn, s->chooseMove(copy, whoseTurn), noth, tester);
		while (tester == 0)
		{
			//essentially this gives another turn if you land in your own pot
			status(test, useless, noth);
			if (test == true)
			{
				for (int i = 0; i < copy.holes() + 1; i++)
				{
					copy.moveToPot(NORTH, i, NORTH);
					copy.moveToPot(SOUTH, i, SOUTH);
				}
				break;
				// if the game ever ends, this gives a way to break out of the while loop
			}
			display();
			copy.sow(whoseTurn, s->chooseMove(copy, whoseTurn), noth, tester);
		}
		if (noth == whoseTurn && copy.beans(whoseTurn, tester) == 1 && copy.beans(NORTH, tester) != 0)
		{
			// this if statement is used to deal with captures
			// basically, if you land in an empty hole on your side and the hole across does not have zero beans in it
			// then you capture their beans in the hole across alongside your own bean
			copy.moveToPot(SOUTH, tester, whoseTurn);
			copy.moveToPot(NORTH, tester, whoseTurn);
		}
	}
	else
	{
		copy.sow(whoseTurn, n->chooseMove(copy, whoseTurn), noth, tester);
		while (tester == 0)
		{
			status(test, useless, noth);
			if (test == true)
			{
				for (int i = 0; i < copy.holes() + 1; i++)
				{
					copy.moveToPot(NORTH, i, NORTH);
					copy.moveToPot(SOUTH, i, SOUTH);
				}
				break;
				// if the game ever ends, this gives a way to break out of the while loop

			}
			display();
			copy.sow(whoseTurn, n->chooseMove(copy, whoseTurn), noth, tester);
		}
		if (noth == whoseTurn && copy.beans(whoseTurn, tester) == 1 && copy.beans(SOUTH, tester) != 0)
		{
			// this if statement is used to deal with captures
			// basically, if you land in an empty hole on your side and the hole across does not have zero beans in it
			// then you capture their beans in the hole across alongside your own bean
			copy.moveToPot(SOUTH, tester, whoseTurn);
			copy.moveToPot(NORTH, tester, whoseTurn);
		}
	}
	changeTurn(whoseTurn);
	if (copy.beansInPlay(NORTH) == 0 || copy.beansInPlay(SOUTH) == 0)
	{
		for (int i = 0; i < copy.holes() + 1; i++)
		{
			copy.moveToPot(NORTH, i, NORTH);
			copy.moveToPot(SOUTH, i, SOUTH);
		}
	}
	return true;
}

void Game::play()
{
	bool test;
	bool useless = false;
	Side noth;
	display();
	status(test, useless, noth);
	if (s->isInteractive() == false && n->isInteractive() == false)
	{
		while (test == false)
		{
			move();
			display();
			cout << "Press ENTER to continue" << endl;
			cin.get();
			status(test, useless, noth);
		}
		// if both players are computers, this gives us a way to slow down how fast the moves are done
	}
	else 
	{
		while (test != true)
		{
			move();
			display();
			status(test, useless, noth);
			// these three functions are constantly running until status tells us that the game is over
		}
	}
	if (useless == true)
	{
		if (noth == SOUTH)
		{
			cout << s->name() << " has won the game" << endl;
		}
		else
		{
			cout << n->name()<<" has won the game" << endl;
		}
	}
	else
	{
		cout << "The game ended as a tie" << endl;
	}
}

int Game::beans(Side s, int hole) const
{
	if (hole < 0 || hole > copy.holes())
	{
		return -1;
	}
	else
	{
		return(copy.beans(s, hole));
	}
}