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
	zoom = 1.0;
}

StaticObject::~StaticObject()
{
}

void StaticObject::draw()
{
	TextureManager::Instance()->drawFrame(textureid, (Uint32)position.getX(), (Uint32)position.getY(),
		width, height, currentrow, currentframe, TheGame::Instance()->getdrawer(), angle, alpha);
}
//draw zoom
void StaticObject::drawzoom(float newzoom)
{
	if (newzoom > 0)
	{
		if (zoom != newzoom)
		{
			zoom = newzoom;
			width = width * zoom;
			height = height * zoom;
			//center the image with its new size
			position.setX(position.getX() - ((width) / 2));
			position.setY(position.getY() - ((height) / 2));
		}
	}
	//below are the zoomed values
	TextureManager::Instance()->draw("One", (Uint32)position.getX(), (Uint32)position.getY(),
		width, height, TheGame::Instance()->getdrawer(), SDL_FLIP_NONE);
}
// apply velocity to current position
void StaticObject::update()
{
	//GP is the gameparameters
	//Static/Stationary object no movement to update
}

void StaticObject::collision()
{
}
//Setter: sets collsion to false
void StaticObject::Setcollisiontrue()
{
	//Static/stationary object cannot collide
	boolcollision = true;
}
