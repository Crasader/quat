#ifndef __SOLVER_STATE_CONTROLLER_H__
#define __SOLVER_STATE_CONTROLLER_H__

namespace QUAT {
class PuzzleLayer;

class SolverStateController
{
public:
	enum STATE {
		IDLE,
		CHOOSING_LETTER
	};

private:
	PuzzleLayer * puzzleLayer;

	STATE _state;

	void setState(STATE newState);

public:

	// States
	/**
	 * When only the current solution progress is showing.
	 */
	void to_IDLE();

	/**
	 * When the user clicked on one of the letters in the current word and
	 * can choose a new letter for that column.
	 */
	void to_CHOOSING_LETTER(int column);

	/**
	 * Gets the current state.
	 */
	STATE state();

	SolverStateController(QUAT::PuzzleLayer * puzzleLayer);


};

}

#endif // __SOLVER_STATE_CONTROLLER_H__
