#pragma once
#include "GameObject.h"
//#include <SDL.h>
#include "Game.h"
//#include <string>

class StaticObject : public GameObject
{
public:
	~StaticObject();
	virtual void draw();
	virtual void update();
	virtual void collision();
	virtual std::string type() { return textureid; }
	virtual Vector2D Getposition() { return Vector2D(position.getX(), position.getY()); };
	//Setter
	virtual void Setcollisiontrue();
	//Get
	std::string Gettextureid() { return textureid; }
protected:

	/*constructor is protected so that it can be accessed
	from derived class*/
	StaticObject(int ms, Vector2D pos, int w, int h, std::string id, int nf);
	int movespeed = 0;
	int m = 0; //movement gradient, for liear angled movement
};

