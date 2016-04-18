///The Playstate will be the center point to call all the control operations
//BulletHandler, InputManager, playstate also draw the lives in used
#pragma once
#include "GameState.h"
#include "CollisionManager.h"

class GameObject;
class SDLGameObject;
class Level;
//public inheritance with GameState: important
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
private:
	//only one copy of this maintained for all objects
	//do not have to refer to object to refer to static member
	//const: has to initialised outside of the class, done it in .cpp file 
	static const std::string playid;
	std::vector<GameObject*> playobjects;
	CollisionManager CM;
};

