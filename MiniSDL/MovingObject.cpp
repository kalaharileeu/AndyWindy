#include "MovingObject.h"
/*
Because I'm not using dependence injection here, I have to pass the
parameter in through the constructor when I initaize the class
This moving object is bound to the windows frame dimensions can not move
out of it
Dependency injection can be achived with the LoaderParameter class, or some parameter class 
*/
MovingObject::MovingObject(int ms, Vector2D pos, int w, int h, std::string id, int nf) : GameObject()
{    // get position
	movespeed = ms;
	position = Vector2D(pos.getX(), pos.getY());
	// get image variables
	width = w;
	height = h;
	textureid = id;
	numframes = nf;
	m = 1;
}

MovingObject::~MovingObject()
{}

void MovingObject::draw()
{
	TextureManager::Instance()->drawFrame(textureid, (Uint32)position.getX(), (Uint32)position.getY(),
		width, height, currentrow, currentframe, TheGame::Instance()->getdrawer(), angle, alpha);
}
// apply velocity to current position
void MovingObject::update()
{
	//GP is the gameparameters
	//Check the Y boundaries
	//Bottom side
	if (position.getY() >= TheGame::Instance()->getGameHeight() - height)
	{
		velocity.setY(-movespeed);
	}
	//Top side, use the image height as well
	else if (position.getY() <= GP::Instance()->Getyaxmin())
	{
		velocity.setY(movespeed);
	}
	//Check the X boundaries
	//Right screen side collision, use the image with
	if (position.getX() >= TheGame::Instance()->getGameWidth() - width)
	{
		velocity.setX(-movespeed);
	}
	//Left screen side collision, the left side 
	else if (position.getX() <= GP::Instance()->Getxaxmin())
	{
		velocity.setX(movespeed);
	}

	position += velocity;
	currentframe = int(((SDL_GetTicks() / (1000 / 3)) % numframes));
}
//Setter: When calles Set collision to true
//TODO: function name is not good enough
void MovingObject::collision()
{
	boolcollision = true;
}
