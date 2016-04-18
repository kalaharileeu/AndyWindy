#pragma once
#include "collision.h"
#include "GameObject.h"
#include <SDL.h>
#include <vector>

class CollisionManager
{
public:
	void checkWrapperWrappedCollision(const std::vector<GameObject*> &objects);
	void checkgeneralcollision(const std::vector<GameObject*> &objects);
};

