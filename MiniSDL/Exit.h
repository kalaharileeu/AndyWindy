#pragma once
#include "Number.h"
class Exit : public Number
{
public:
	Exit(int ms, Vector2D pos, int w, int h, std::string id, int nf)
		: Number(ms, pos, w, h, id, nf)
	{

	}

	//void update() {};
	//void draw() {};

	~Exit() {}
};

