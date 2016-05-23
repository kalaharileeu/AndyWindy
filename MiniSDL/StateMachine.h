/*
-The game loop and its pipelines: The Clean, update, draw, handleevents
are the four pipelines pumped by the game loop.
-StateMachine has 3 of pipes runnung through it, Clean, update and draw
-Get initialized in Game.cpp.
• Removing one state and adding another: use this way to completely
change states without leaving the option to return
• Adding one state without removing the previous state: This way is useful
for pause menus and so on
• Removing one state without adding another: This way will be used to remove
pause states or any other state that had been pushed on top of another one
*/
#pragma once
#include <vector>
#include "GameState.h"
class StateMachine
{
public:
	StateMachine() {}
	~StateMachine()
	{
		if (!gamestate.empty())
		{
			for (int i = 0; i < gamestate.size(); i++)
			{
				if (gamestate[i] != nullptr)
				{
					gamestate[i]->onExit();
					delete gamestate[i];
					gamestate[i] = nullptr;
				}
			}
		}
	}
	void update();
	void draw();
	void pushState(GameState* state);
	void changeState(GameState* state);
	void popState();

	void clean();

	std::vector<GameState*>& getGameStates() { return gamestate; }

private:
	std::vector<GameState*> gamestate;
};