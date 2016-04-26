#pragma once
#include "StaticObject.h"

class Number :	public StaticObject
{
public:
	/*movespeed, position, width, height, textureid, numframes;*/
	Number(int ms, Vector2D pos, int w, int h, std::string id, int nf)
		: StaticObject(ms, pos, w, h, id, nf)
	{
		touched = false;
	}

	~Number() { std::cout << "Number detroyed"; }

	void update()
	{
		StaticObject::update();
		if (InputHandler::Instance()->Gettouchstate())
		{ 
			handletouchinput();
		}
		if (InputHandler::Instance()->getMouseButtonState(0))
		{
			handlemouseinput();
		}

	}
	void draw()	{ StaticObject::draw();	}

	std::string type() {	return "Number"; }
	//return the position of the object.(Some object feedback)
	Vector2D Getposition() {	return StaticObject::Getposition();	}
	bool Getiftouchedbool() { return touched; }

private:

	void handlemouseinput()
	{
		//when toudhed just set the touched bool
		//if it is a moving object, can cahnge the position for ex.
		int touchX = InputHandler::Instance()->getMousePosition()->getX();
		int touchy = InputHandler::Instance()->getMousePosition()->getY();

		if ((touchX > position.getX() && touchX < position.getX() + width) &&
			(touchy > position.getY() && touchy < position.getY() + height))
		{
			touched = true;
		}
	}

	void handletouchinput()
	{
		//when toudhed just set the touched bool
		//if it is a moving object, can cahnge the position for ex.
		int touchX = InputHandler::Instance()->Gettouchposition()->getX();
		int touchy = InputHandler::Instance()->Gettouchposition()->getY();

		if ((touchX > position.getX() && touchX < position.getX() + width) &&
			(touchy > position.getY() && touchy < position.getY() + height))
		{
			touched = true;
		}
	}


	bool touched;
};

