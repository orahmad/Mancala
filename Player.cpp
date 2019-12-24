#include "Player.h"
#include "Board.h"
#include <iostream>
#include <string>
using namespace std;

//==========================================================================
// AlarmClock ac(numMilliseconds);  // Set an alarm clock that will time out
//                                  // after the indicated number of ms
// if (ac.timedOut())  // Will be false until the alarm clock times out; after
//                     // that, always returns true.
//==========================================================================

#include <chrono>
#include <future>
#include <atomic>

class AlarmClock
{
public:
	AlarmClock(int ms)
	{
		m_timedOut = false;
		m_isRunning = true;
		m_alarmClockFuture = std::async([=]() {
			for (int k = 0; k < ms && m_isRunning; k++)
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			if (m_isRunning)
				m_timedOut = true;
		});
	}

	~AlarmClock()
	{
		m_isRunning = false;
		m_alarmClockFuture.get();
	}

	bool timedOut() const
	{
		return m_timedOut;
	}

	AlarmClock(const AlarmClock&) = delete;
	AlarmClock& operator=(const AlarmClock&) = delete;
private:
	std::atomic<bool> m_isRunning;
	std::atomic<bool> m_timedOut;
	std::future<void> m_alarmClockFuture;
};
void bestMove(Side s, GameTree* test, int& bestHole, int& value, AlarmClock& timeOut);


Player::Player(std::string name)
	:m_name(name)
{
}

BadPlayer::BadPlayer(std::string name)
	:Player::Player(name)
{
}

HumanPlayer::HumanPlayer(std::string name)
	: Player::Player(name)
{
}

SmartPlayer::SmartPlayer(std::string name)
	: Player::Player(name)
{
	m_privr = new GameTree;
}

std::string Player::name() const
{
	return m_name;
}

bool Player::isInteractive() const
{
	return false;
}

int BadPlayer::chooseMove(const Board& b, Side s) const
{
	// this functions just picks the hole that is closest to the North Pot
	int counter = b.holes() + 1;
	for (int i = 1; i < counter; i++)
	{
		if (b.beans(s, i) != 0)
		{
			// you have to make sure that it doesn't pick a hole with zero beans in it
			return i;
		}
	}
	return -1;
}

bool HumanPlayer::isInteractive() const
{
	return true;
}

int HumanPlayer::chooseMove(const Board& b, Side s) const
{
	if (b.beansInPlay(s) == 0)
	{
		return -1;
	}
	// the human player is prompted on what hole to pick
	int n;
	cout << "Select a hole, " << name() << ": ";
	cin >> n;
	cin.ignore();
	while (n < 1 || n > b.holes() || b.beans(s, n) == 0)
	{
		// if the hole isn't valid, then it prompts you to repick a hole
		cout << "Pick a valid hole" << endl;
		cout << "Select a hole, " << name() << ": ";
		cin >> n;
		cin.ignore();
	}
	return n;
}

int SmartPlayer::chooseMove(const Board& b, Side s) const
{
	if (b.beansInPlay(s) == 0)
		return -1;

	// make a copy of the current board in play
	m_privr->m_copy = new Board(b);

	int bH, val;
	switch (s) {
	case SOUTH:
		val = -1000;    // so that when no good moves are available, they will still choose -999
		break;          // worst case scenario, just in case
	case NORTH:
		val = 1000;
		break;
	}

	AlarmClock timeOut(4900);

	bestMove(s, m_privr, bH, val, timeOut);

	return bH;
}

Player::~Player()
{}

BadPlayer::~BadPlayer()
{}

HumanPlayer::~HumanPlayer()
{}

SmartPlayer::~SmartPlayer()
{}

void bestMove(Side s, GameTree* test, int& bestHole, int& value, AlarmClock& timeOut)
{
	Board* now = test->m_copy;  // The board we are currently evaluating
	Side opp = opponent(s);
	int holes = now->holes();

	if (now->beansInPlay(s) == 0 || now->beansInPlay(opp) == 0) {

		for (int i = 1; i <= holes; i++) {
			now->moveToPot(s, i, s);
			now->moveToPot(opp, i, opp);    //if game is over, clean up whatever might be left
		}

		if (now->beans(s, 0) > now->beans(opp, 0))  //when game is won
			switch (s) {
			case SOUTH:
				value = 999;    // big for SOUTH, small for NORTH
				break;
			case NORTH:
				value = -999;
				break;
			}
		else if (now->beans(s, 0) < now->beans(opp, 0)) // if game is lost
			switch (s) {
			case SOUTH:
				value = -999;   // small for SOUTH, big for NORTH
				break;
			case NORTH:
				value = 999;
			}
		else
			value = 0;  // tied

		bestHole = -1;
		return;
	}

	if ((timeOut.timedOut())) { // within 4.9 seconds
		bestHole = -1;
		value = (now->beans(SOUTH, 0) - now->beans(NORTH, 0));
		return;
	}

	for (int i = 1; i <= holes; i++) {

		int num;
		if (s == SOUTH)
			num = holes + 1 - i;    // numbering system for south holes
		else
			num = i;

		if (now->beans(s, num) > 0) {   // enter if not an empty hole

			GameTree* branch = new GameTree;

			Board* branch_board = branch->m_copy = new Board(*now); // copy of the board on the branch

			Side endSide; int endHole;

			int bh2, val2;

			branch_board->sow(s, num, endSide, endHole);    //sow the branch copy

			if (endHole == 0)
			{
				bestMove(s, branch, bh2, val2, timeOut);
			}

			else if (endSide == s && endHole != 0 && branch_board->beans(s, endHole) == 1
				&& branch_board->beans(opp, endHole) > 0)
			{
				branch_board->moveToPot(s, endHole, s); // capture
				branch_board->moveToPot(opp, endHole, s);
			}

			bestMove(opp, branch, bh2, val2, timeOut);  // check the lower levels

			if ((val2 > value && s == SOUTH)
				|| (val2 < value && s == NORTH)) { // bigger number for south, lower for north

				value = val2;

				bestHole = num;
			}

			delete branch_board; delete branch; // delete the dynamically allocated copies
		}
	}

	return;
}
