#pragma once
#include "GameObject.h"
#include "GameState.h"

class SumState : public GameState
{
public:
	SumState();
	~SumState();
	virtual void update();
	virtual void draw();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return stateid; }
protected:
	void setup();
	//this write the screen text
	int a, b, sum;
	GameObject* goback;
	GameObject* goforward;
	int counter;
	int counterb;
	std::vector<GameObject*> playobjects;
	GameObject* firstarg;
	GameObject* secarg;
	GameObject* thesum;
	GameObject* firstargdot;//dots
	GameObject* secargdot;//dots
	GameObject* thesumdot;//dots
	GameObject* tick;//dots
	std::vector<GameObject*> frameobjects;
	std::vector<std::string> numbertostring;
	GameObject* plus;
	GameObject* equal;
	//only one copy of this maintained for all objects
	//do not have to refer to object to refer to static member
	//const: has to initialised outside of the class, done it in .cpp file 
	static const std::string stateid;
};
