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
	GameObject* goback;
	GameObject* goforward;
	std::vector<GameObject*> playobjects;
	//only one copy of this maintained for all objects
	//do not have to refer to object to refer to static member
	//const: has to initialised outside of the class, done it in .cpp file 
	static const std::string stateid;
};

