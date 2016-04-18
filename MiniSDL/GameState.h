#pragma once
#include <string>
#include <vector>
/*
There are a few possible states for the game/program for instance playstate, pause state, menustate etc.
FSM(Finite State Machine), machine can exist in a finite number of states, can exist in only one state
at a time (current state), and can change from one state to another (transition).
Abstract class:
Like GameObject class: abstract base class;
no functionality into it, derived classes to follow this contract.
*/
class GameState
{
public:
	virtual ~GameState() {}//destructor
	virtual void update() = 0;//function like the functions in the Game class
	virtual void draw() = 0;//function like the functions in the Game class
	virtual bool onEnter() = 0;//load
	virtual bool onExit() = 0;//clean
	virtual void resume() {}
	//const function can not change data members
	virtual std::string getStateID() const = 0;//ID is used to ensure that states don't get repeated
protected:
	//initialise some default values
	GameState() : boolloadingcomplete(false), boolexiting(false)
	{}
	bool boolloadingcomplete;
	bool boolexiting;
	//list of texture IDs to each state so that we can clear all of the textures that were loaded for that state
	std::vector<std::string> textureidlist;
};

