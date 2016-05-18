#pragma once
#include "Number.h"

class Goback : public Number
{
public:
	/*movespeed, position, width, height, textureid, numframes;*/
	Goback(int ms, Vector2D pos, int w, int h, std::string id, int nf) 
		: Number(ms, pos, w, h, id, nf)
	{
	}
};

class Next : public Number
{
public:
	/*movespeed, position, width, height, textureid, numframes;*/
	Next(int ms, Vector2D pos, int w, int h, std::string id, int nf)
		: Number(ms, pos, w, h, id, nf)
	{
	}
};