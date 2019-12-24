#include"Board.h"
#include <vector>
#include<iostream>
using namespace std;

int Board::hole::holes_beans() const
{
	//returns the # of beans
	return number_beans;
}

void Board::hole::set_holes_beans(int num)
{
	//sets the # of beans
	number_beans = num;
}

int Board::hole::enum_getter() const
{
	//returns the correct side
	return definer;
}

Board::hole::hole(int number, Board::type whichOne)
	:number_beans(number), definer(whichOne)
{
	//constructor that sets the private members accordingly
}

Board::hole::hole()
{
	// default constructor for the hole class
}

Board::hole::hole(const hole& src)
{
	number_beans = src.number_beans;
	definer = src.definer;
}

Board::Board(int nHoles, int nInitialBeansPerHole)
{
	//board's constructor that just pushes back a new hole to the according hole number and side
	for (int i = 0; i < nHoles; i++)
	{
		vec.push_back(new hole(nInitialBeansPerHole, SOUTHHOLE));
	}
	vec.push_back(new hole(0, SOUTHPOT));
	for (int i = 0; i < nHoles; i++)
	{
		vec.push_back(new hole(nInitialBeansPerHole, NORTHHOLE));
	}
	vec.push_back(new hole(0, NORTHPOT));
}

Board::Board(const Board& src)
{
	// this is just a simple copy constructor
	for (int i = 0;i < src.vec.size(); i++)
	{
		hole* n = src.vec[i];
		vec.push_back(new hole(*n));
	}
}

Board& Board::operator=(const Board& src)
{
	// this is just an assignment operator
	for (int i = 0; i < src.vec.size(); i++)
	{
		hole* n = src.vec[i];
		vec.push_back(new hole(*n));
	}
	return *this;
}

int Board::holes() const
{
	return (vec.size() - 2)/2;
	// we subtract two because of the two pots
}

int Board::beans(Side s, int hole) const
{
	if (hole < 0 || hole > holes())
	{
		return -1;
	}
	if (s == SOUTH)
	{
		if (hole == 0)
		{
			// if the hole is the south pot, then return accordingly
			for (int i = 0; i < vec.size(); i++)
			{
				if (vec[i]->enum_getter() == 2)
				{
					return vec[i]->holes_beans();
				}
			}
		}
		return vec[hole - 1]->holes_beans();
		// if it isn't the pot, then it returns the right hole
	}
	if (s == NORTH)
	{
		if (hole == 0)
		{
			// if the hole is the south pot, then return accordingly

			for (int i = 0; i < vec.size(); i++)
			{
				if (vec[i]->enum_getter() == 3)
				{
					return vec[i]->holes_beans();
				}
			}
		}
		return vec[vec.size() - 1 - hole]->holes_beans();
		// if it isn't the pot, then it returns the right hole
	}
}

int Board::beansInPlay(Side s) const
{
	int counter = 0;
	if (s == SOUTH)
	{
		for (int i = 0; i < holes(); i++)
		{
			counter = counter + vec[i]->holes_beans();
		}
	}
	if (s == NORTH)
	{
		for (int i = (holes() + 1); i < (vec.size()-1); i++)
		{
			counter = counter + vec[i]->holes_beans();
		}
	}
	// in order to return the amount of the beans on the respected side, a counter is kept
	return counter;
}

int Board::totalBeans() const
{
	int counter = 0;
	for (int i = 0; i < holes(); i++)
	{
		counter = counter + vec[i]->holes_beans();
	}
	for (int i = (holes() + 1); i < (vec.size() - 1); i++)
	{
		counter = counter + vec[i]->holes_beans();
	}
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i]->enum_getter() == 2)
		{
			counter = counter + vec[i]->holes_beans();
		}
	}
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i]->enum_getter() == 3)
		{
			counter = counter + vec[i]->holes_beans();
		}
	}
	return counter;
}
/*If the hole indicated by (s,hole) is empty or invalid or a pot, this function returns false without changing anything. 
Otherwise, it will return true after sowing the beans: the beans are removed from hole (s,hole) and sown counterclockwise, 
including s's pot if encountered, but skipping s's opponent's pot. 
The parameters endSide and endHole are set to the side and hole where the last bean was placed. 
(This function does not make captures or multiple turns; 
different Kalah variants have different rules about these issues, 
so dealing with them should not be the responsibility of the Board class.)*/
bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{
	// sowing was very hard because we had to figure out how to deal with the end of the vector
	if (hole <= 0 || hole > holes())
	{
		return false;
	}
	if (beans(s, hole) == 0)
	{
		return false;
	}
	int amount = beans(s, hole);
	int counter = 0;
	int separate = 0;
	if (s == SOUTH)
	{
		counter = hole - 1;
		vec[counter]->set_holes_beans(0); 
			for (int i = hole; amount != 0; i++, amount--)
			{
				if (amount == 1)
				{
					if (vec[i]->enum_getter() == 0)
					{
						endSide = SOUTH;
						endHole = i + 1;
					}
					if (vec[i]->enum_getter() == 2)
					{
						endSide = SOUTH;
						endHole = 0;
					}
					if (vec[i]->enum_getter() == 1)
					{
						endSide = NORTH;
						endHole = vec.size() - 1 - i;
					}
				}
				if (vec[i]->enum_getter() != 3)
				{
					int separate = vec[i]->holes_beans();
					vec[i]->set_holes_beans(separate + 1);
				}
				else
				{
					amount++;
					i = -1;
				}
			}
	}
	if (s == NORTH)
	{
		counter = vec.size() - 1 - hole;
		vec[counter]->set_holes_beans(0);
		for (int i = counter + 1; amount != 0; i++, amount--)
		{
			if (amount == 1)
			{
				if (vec[i]->enum_getter() == 0)
				{
					endSide = SOUTH;
					endHole = i + 1;
				}
				if (vec[i]->enum_getter() == 1)
				{
					endSide = NORTH;
					endHole = vec.size() - 1 - i;
				}
				if (vec[i]->enum_getter() == 3)
				{
					endSide = NORTH;
					endHole = 0;
				}
			}
			if (vec[i]->enum_getter() != 3 && vec[i]->enum_getter() != 2)
			{
				int separate = vec[i]->holes_beans();
				vec[i]->set_holes_beans(separate + 1);
			}
			else if (vec[i]->enum_getter() == 3)
			{
				int separate = vec[i]->holes_beans();
				vec[i]->set_holes_beans(separate + 1);
				i = -1;
			}
			else
			{
				amount++;
			}
		}
	}
	return true;
}

bool Board::moveToPot(Side s, int hole, Side potOwner)
{
	if (hole <= 0 || hole > holes())
	{
		return false;
	}
	int counter = 0;
	int amount = 0;
	counter = beans(s, hole);
	if (potOwner == SOUTH)
	{
		amount = vec[holes()]->holes_beans();
		vec[holes()]->set_holes_beans(amount + counter);
		if (s == SOUTH)
		{
			vec[hole - 1]->set_holes_beans(0);
		}
		else
		{
			vec[vec.size() - 1 - hole]->set_holes_beans(0);
		}
	}
	else
	{
		amount = vec[vec.size() - 1]->holes_beans();
		vec[vec.size() - 1]->set_holes_beans(amount + counter);
		if (s == SOUTH)
		{
			vec[hole - 1]->set_holes_beans(0);
		}
		else
		{
			vec[vec.size() - 1 - hole]->set_holes_beans(0);
		}
	}
	return true;
}

bool Board::setBeans(Side s, int hole, int beans)
{
	if (hole < 0 || hole > holes() || beans < 0)
	{
		return false;
	}
	if (s == SOUTH)
	{
		if (hole == 0)
		{
			vec[holes()]->set_holes_beans(beans);
		}
		vec[hole - 1]->set_holes_beans(beans);
	}
	if (s == NORTH)
	{
		if (hole == 0)
		{
			vec[vec.size() - 1]->set_holes_beans(beans);
		}
		vec[vec.size() - 1 - hole]->set_holes_beans(beans);
	}
	return true;
}

Board::~Board()
{
	for (int i = 0; i < vec.size(); i++)
	{
		delete vec[i];
	}
}
