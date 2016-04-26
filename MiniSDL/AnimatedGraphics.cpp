#include "AnimatedGraphics.h"

AnimatedGraphics::AnimatedGraphics(int ms, Vector2D pos, int w, int h, std::string id, int nf) : StaticObject(ms, pos, w, h, id, nf)
{

}

void AnimatedGraphics::draw()
{
	StaticObject::draw();
}

void AnimatedGraphics::update()
{
	currentframe = int(((SDL_GetTicks() / (1000 / m_animSpeed)) % numframes));
}