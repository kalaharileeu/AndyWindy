#pragma once
#include "GameObject.h"
#include <SDL.h>
#include "Game.h"
#include <string>

class MovingObject : public GameObject 
{
public:

	virtual ~MovingObject();
	virtual void draw();
	virtual void update();
	virtual std::string type() { return textureid; }
	virtual Vector2D Getposition(){ return Vector2D(position.getX(), position.getY()); };
	virtual void collision();

protected:
	/*constructor is protected so that it can be accessed
	from derived class*/
	MovingObject(int ms, Vector2D pos, int w, int h, std::string id, int nf);
	int movespeed;
	int m; //movement gradient, for liear angled movement
};

