#pragma once
#pragma once
#include "StaticObject.h"
//Draws a general shape in dedicated position
class GeneralNumber : public StaticObject
{
public:
	/*movespeed, position, width, height, textureid, numframes;*/
	GeneralNumber(int ms, Vector2D pos, int w, int h, std::string id, int nf)
		: StaticObject(ms, pos, w, h, id, nf)
	{}

	~GeneralNumber() { }

	void update(){}

	void draw()
	{
		StaticObject::draw();
	}

	std::string type() { return "GeneralShape"; }
	//return the position of the object.(Some object feedback)
	Vector2D Getposition() { return StaticObject::Getposition(); }
};

