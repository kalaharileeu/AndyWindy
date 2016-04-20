#include "StaticObject.h"

StaticObject::StaticObject(int ms, Vector2D pos, int w, int h, std::string id, int nf) : GameObject()
{    // get position
	movespeed = 0;//can not move so do not use ms
	position = Vector2D(pos.getX(), pos.getY());
	// get image variables
	width = w;
	height = h;
	textureid = id;
	numframes = nf;
	m = 0;
}

StaticObject::~StaticObject()
{
}

void StaticObject::draw()
{
	TextureManager::Instance()->drawFrame(textureid, (Uint32)position.getX(), (Uint32)position.getY(),
		width, height, currentrow, currentframe, TheGame::Instance()->getdrawer(), angle, alpha);
}
// apply velocity to current position
void StaticObject::update()
{
	//GP is the gameparameters
	//Static/Stationary object no movement to update
}
//Setter: sets collsion to false
void StaticObject::collision()
{
	//Static/stationary object cannot collide
	boolcollision = false;
}
