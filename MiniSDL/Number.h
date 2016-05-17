#pragma once
#include "StaticObject.h"
#include "Vector2D.h"


class Number :	public StaticObject
{
public:
	/*movespeed, position, width, height, textureid, numframes;*/
	Number(int ms, Vector2D pos, int w, int h, std::string id, int nf)
		: StaticObject(ms, pos, w, h, id, nf)
	{
		touched = false;
		touchX = -1;
		touchY = -1;
	}

	~Number() { }

	virtual void update()
	{
#if defined( ANDROID )
		//StaticObject::update(); Does nothing empty
		int tempX = InputHandler::Instance()->Gettouchposition()->getX();
		int tempY = InputHandler::Instance()->Gettouchposition()->getY();
		//if there is a change then check for touch collision
		if ((touchX != tempX) || (touchY != tempY))
		{
			touchX = tempX;
			touchY = tempY;

			if ((touchX > position.getX() && touchX < position.getX() + width) &&
				(touchY > position.getY() && touchY < position.getY() + height))
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

	virtual std::string type() { return "Number"; }
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

	void Settextureid(std::string value) { textureid = value; }

	void Getposition(int &xpos, int &ypos) const
	{
		xpos = touchX;
		ypos = touchY;
	}

private:
	void handlemouseinput()
	{
		//when toudhed just set the touched bool
		//if it is a moving object, can cahnge the position for ex.
		int tempX = InputHandler::Instance()->getMousePosition()->getX();
		int tempY = InputHandler::Instance()->getMousePosition()->getY();
		std::cout << "Here" << std::endl;
		//if there is a change then check for touch collision
		if ((touchX != tempX) || (touchY != tempY))
		{
			//if the values are different then change
			touchX = tempX;
			touchY = tempY;

			if ((tempX > position.getX() && tempX < position.getX() + width) &&
				(tempY > position.getY() && tempY < position.getY() + height))
			{
				std::cout << "Here2" << std::endl;
				touched = true;
			}
		}
	}

	bool touched;
	int touchX;
	int touchY;
};

