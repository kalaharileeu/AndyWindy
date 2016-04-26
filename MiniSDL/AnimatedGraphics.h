#pragma once
#include "StaticObject.h"
///Animated Graphic is a stationary animated effect
class AnimatedGraphics : public StaticObject
{
public:
	AnimatedGraphics(int ms, Vector2D pos, int w, int h, std::string id, int nf);
	virtual ~AnimatedGraphics() {}
	virtual void draw();
	virtual void update();

private:
	int m_animSpeed;
	int m_frameCount;
};

