
/*
• Removing one state and adding another: We will use this way to completely
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
	~StateMachine() {}

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