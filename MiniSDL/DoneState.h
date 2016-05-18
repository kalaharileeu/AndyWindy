#pragma once
#include "GameState.h"

//class Texter;
class GameObject;
//public inheritance with GameState: important
class DoneState : public GameState
{
public:
	DoneState(std::string drawvalue);
	//virtual member is a member function that can be redefined in a derived class
	virtual ~DoneState();
	virtual void update();
	virtual void draw();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return doneid; }
private:
	//only one copy of this maintained for all objects
	//do not have to refer to object to refer to static member
	//const: has to initialised outside of the class, done it in .cpp file 
	static const std::string doneid;
	std::vector<GameObject*> numberobjects;
	//CollisionManager CM;
	//Texter* textmanagerdone;
	bool textdonebool;
	//This is the number to draw
	std::string numbertodraw;
};

