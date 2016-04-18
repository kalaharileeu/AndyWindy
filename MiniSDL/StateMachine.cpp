#include "StateMachine.h"
#include <iostream>

void StateMachine::clean()
{
	if (!gamestate.empty())
	{
		gamestate.back()->onExit();

		delete gamestate.back();

		gamestate.clear();
	}
}

void StateMachine::update()
{
	if (!gamestate.empty())
	{
		gamestate.back()->update();
	}
}

void StateMachine::draw()
{
	if (!gamestate.empty())
	{
		gamestate.back()->draw();
	}
}

/*pushState: When a new state is pushed, OnEnter needs to be called to
to initialise the state. Loading content etc.*/
void StateMachine::pushState(GameState *state)
{
	gamestate.push_back(state);
	gamestate.back()->onEnter();
}

/*popState: when popState called the onExit needs 
to be called to shut down the state, prpearing for the next state*/
void StateMachine::popState()
{
	if (!gamestate.empty())
	{
		gamestate.back()->onExit();
		gamestate.pop_back();
	}

	gamestate.back()->resume();
}

void StateMachine::changeState(GameState *state)
{
	if (!gamestate.empty())
	{
		//vector::back returns ref to the last element in vector
		//
		if (gamestate.back()->getStateID() == state->getStateID())
		{
			return; // do nothing
		}

		gamestate.back()->onExit();
		gamestate.pop_back();
	}
	// initialise it
	state->onEnter();

	// push back our new state
	gamestate.push_back(state);
}
