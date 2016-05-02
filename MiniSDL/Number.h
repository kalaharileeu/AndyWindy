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

	~Number() { }

	void update()
	{
#if defined( ANDROID )
		//StaticObject::update(); Does nothing empty
		if (InputHandler::Instance()->Gettouchstate())
		{ 
			//when touched just set the touched bool
			//if it is a moving object, can cahnge the position for ex.
			int touchX = InputHandler::Instance()->Gettouchposition()->getX();
			int touchy = InputHandler::Instance()->Gettouchposition()->getY();

			if ((touchX > position.getX() && touchX < position.getX() + width) &&
				(touchy > position.getY() && touchy < position.getY() + height))
			{
				touched = true;
			}
		}
#endif
#if !defined( ANDROID )
		if (InputHandler::Instance()->getMouseButtonState(0))
		{
			handlemouseinput();
		}
#endif
	}

	void draw()
	{ 
		StaticObject::draw();	
	}

	std::string type() {	return "Number"; }
	//return the position of the object.(Some object feedback)
	Vector2D Getposition() {	return StaticObject::Getposition();	}
	bool Getiftouchedbool() 
	{
		if (touched == true)
		{
			touched = false;
			return true;
		}
		else
			return false;
	}

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

	bool touched;
};

