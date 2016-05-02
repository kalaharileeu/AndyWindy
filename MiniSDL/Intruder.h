//#pragma once
//#include <iostream>
//#include "MovingObject.h"
//#include "GeneralParameters.h"
//
//class Intruder : public MovingObject
//{
//public:
//	/*movespeed, position, width, height, textureid, numframes;*/
//	Intruder(int ms, Vector2D pos, int w, int h, std::string id, int nf)
//		: MovingObject(ms, pos, w, h, id, nf)
//	{
//		//the parameter in the constructor can be more elegantly 
//		//replaced with dependency injection
//		velocity.setX(-movespeed);
//		velocity.setY(movespeed * m);
//	}
//
//	~Intruder() { std::cout << "Intruder detroyed"; }
//
//	void update()
//	{
//		MovingObject::update();
//		handleinput();
//	}
//
//	void draw()
//	{
//		MovingObject::draw();
//	}
//
//	std::string type()
//	{
//		return "Intruder";
//	}
//	//return the position of the object.(Some object feedback)
//	Vector2D Getposition()
//	{
//		return MovingObject::Getposition();
//	}
//
//	void bounce(Vector2D v)
//	{
//		if (v.getY() != 0)
//		{
//			velocity.setY(v.getY());
//		}
//
//		if (v.getX() != 0)
//		{
//			velocity.setX(v.getX());
//		}
//	}
//
//private:
//
//	void handleinput()
//	{
//		if (InputHandler::Instance()->Gettouchstate())
//		{
//			//SDL_Log("Touched !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
//			float x = (position.getX() + InputHandler::Instance()->Gettouchposition()->getX()) / 2;
//			float y = (position.getY() + InputHandler::Instance()->Gettouchposition()->getY()) / 2;
//
//			position.setX(x);
//			position.setY(y);
//		}
//
//		if (InputHandler::Instance()->getMouseButtonState(0))
//		{
//			//std::cout << "mouse clicked" << std::endl;
//			float x = (position.getX() + InputHandler::Instance()->getMousePosition()->getX()) / 2;
//			float y = (position.getY() + InputHandler::Instance()->getMousePosition()->getY()) / 2;
//
//			position.setX(x);
//			position.setY(y);
//		}
//	}
//};
//
