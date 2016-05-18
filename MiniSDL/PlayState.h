///The Playstate will be the center point to call all the control operations
//BulletHandler, InputManager, playstate also draw the lives in used
//But more simplistic in this application
#pragma once
#include "GameState.h"

class GameObject;

class PlayState : public GameState
{
public:
	//virtual member is a member function that can be redefined in a derived class
	virtual ~PlayState();
	virtual void update();
	virtual void draw();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return playid; }
protected:
	void setup();
	std::vector<GameObject*> playobjects;
	//std::vector<GameObject*> numberobjects;
	int counter;
	//bool to check any more blue squares
	bool donesearching;
	GameObject* one;
	GameObject* two;
	GameObject* three;
	GameObject* four;
	GameObject* five;
	GameObject* six;
	GameObject* seven;
	GameObject* eight;
	GameObject* nine;
	//used to move back to main menu
	GameObject* goback;
	//this write the screen text
	//Texter textmanager;
	bool textdonebool;

private:
	//only one copy of this maintained for all objects
	//do not have to refer to object to refer to static member
	//const: has to initialised outside of the class, done it in .cpp file 
	static const std::string playid;


};

