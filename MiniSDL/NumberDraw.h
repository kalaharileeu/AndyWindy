//number draw is a gamestate loaded when draw button is presses
//draw letters with finger when touch or mouse click
#pragma once
#include "GameState.h"
#include "Vector2D.h"

class GameObject;

class NumberDraw : public GameState
{
public:
	NumberDraw();
	~NumberDraw();
	virtual void update();
	virtual void draw();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return stateid; }
protected:
	void setup();
	//this write the screen text
	GameObject* goback;
	GameObject* goforward;
	std::vector<GameObject*> playobjects;
	//only one copy of this maintained for all objects
	//do not have to refer to object to refer to static member
	//const: has to initialised outside of the class, done it in .cpp file 
private:
	static const std::string stateid;
	int xstart, ystart;
	std::vector<Vector2D> drawcoord;
	std::vector<std::string> numbertostring;
	int counter;
	int tempx;
	int tempy;
};

