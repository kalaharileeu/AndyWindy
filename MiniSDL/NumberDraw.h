//number draw is a gamestate loaded when draw button is presses
//draw letters with finger when touch or mouse click
#pragma once
#include "GameState.h"
//#include "Texter.h"

//class Texter;
class GameObject;

class NumberDraw : public GameState
{
public:
	virtual ~NumberDraw();
	virtual void update();
	virtual void draw();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return stateid; }
protected:
	void setup();
	//this write the screen text
	//Texter numberdrawtester;
	GameObject* goback;
	std::vector<GameObject*> playobjects;
	//only one copy of this maintained for all objects
	//do not have to refer to object to refer to static member
	//const: has to initialised outside of the class, done it in .cpp file 
	static const std::string stateid;

};

