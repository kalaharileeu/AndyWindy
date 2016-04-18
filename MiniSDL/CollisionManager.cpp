#include "CollisionManager.h"
#include "Shield.h"
#include <iostream>
#include "Vector2D.h"


void CollisionManager::checkWrapperWrappedCollision(const std::vector<GameObject*> &objects)
{
	//pointer used to point at "intruders"
	GameObject* pointerobjectintruder;
	GameObject* pointerobjectshield;
	//create two collsion rectangles
	SDL_Rect* rectshield = new SDL_Rect();
	SDL_Rect* rectsintruder = new SDL_Rect();
	for (int i = 0; i < objects.size(); i++)
	{
		//pointer used to point at "Shield"
		pointerobjectshield = objects[i];
		//perform search for Shield gameobjects
		if (pointerobjectshield->type() == std::string("Shield"))
		{
			//Populate collision rectangle
			rectshield->x = pointerobjectshield->Getposition().getX();
			rectshield->y = pointerobjectshield->Getposition().getY();
			rectshield->w = pointerobjectshield->Getwidth();
			rectshield->h = pointerobjectshield->Getheight();
			//Search th
			for(int j = 0; j < objects.size(); j++)
			{
				pointerobjectintruder = objects[j];
				//if it  is a intruder and it has not collided yet
				if (pointerobjectintruder->type() == std::string("Intruder"))
				{
					//Populate collision rectangle
					rectsintruder->x = pointerobjectintruder->Getposition().getX();
					rectsintruder->y = pointerobjectintruder->Getposition().getY();
					rectsintruder->w = pointerobjectintruder->Getwidth();
					rectsintruder->h = pointerobjectintruder->Getheight();
					//Check for collision
					if (RectRect(rectsintruder, rectshield))
					{
						//If it already collided then skip it
						if (!pointerobjectintruder->Getcollision() && !pointerobjectshield->Getcollision())
						{
							pointerobjectintruder->collision();
							pointerobjectshield->collision();
							//upcast to shield to use shield specific functions
							dynamic_cast<Shield*>(pointerobjectshield)->loadwrapped(pointerobjectintruder);
							std::cout << "collision" << std::endl;
							//below how to load a brand new gameobject into the wrapper
							//dynamic_cast<Shield*>(playobjects[i])->
							//loadwrapped(new Intruder(1, Vector2D(200, 200), 60, 60, "intruder", 1));
						}
					}
				}
			}
		}
	}
	delete rectshield;
	delete rectsintruder;
}

void CollisionManager::checkgeneralcollision(const std::vector<GameObject*> &objects)
{
	GameObject* pointerobjectshield2;
	GameObject* pointerobjectshield;
	//create two collsion rectangles
	Vector2D bouncevec;
	SDL_Rect* rectshield = new SDL_Rect();
	SDL_Rect* rectshield2 = new SDL_Rect();
	for (int i = 0; i < objects.size(); i++)
	{
		//pointer used to point at "Shield"
		pointerobjectshield = objects[i];
		//perform search for Shield gameobjects
		if (pointerobjectshield->type() == std::string("Intruder"))
		{
			//Populate collision rectangle
			rectshield->x = pointerobjectshield->Getposition().getX();
			rectshield->y = pointerobjectshield->Getposition().getY();
			rectshield->w = pointerobjectshield->Getwidth();
			rectshield->h = pointerobjectshield->Getheight();
			//Search th
			for (int j = i + 1; j < objects.size(); j++)
			{
				pointerobjectshield2 = objects[j];
				//if it  is a intruder and it has not collided yet
				if (pointerobjectshield2->type() == std::string("Intruder"))
				{
					//Populate collision rectangle
					rectshield2->x = pointerobjectshield2->Getposition().getX();
					rectshield2->y = pointerobjectshield2->Getposition().getY();
					rectshield2->w = pointerobjectshield2->Getwidth();
					rectshield2->h = pointerobjectshield2->Getheight();
					//Check for collision
					if(j != i)
					{
						//Check for collision
						if (RectRect(rectshield, rectshield2))
						{
							bouncevec = RectRectbounce(rectshield, rectshield2);
							//upcast to intruder
							dynamic_cast<Intruder*>(pointerobjectshield)->bounce(bouncevec);
							bouncevec = RectRectbounce(rectshield, rectshield2);
							int x = bouncevec.getX() * (-1);
							int y = bouncevec.getY() * (-1);
							bouncevec.setX(x);
							bouncevec.setY(y);
							dynamic_cast<Intruder*>(pointerobjectshield2)->bounce(bouncevec);
						}
					}
				}
			}
		}
	}
	delete rectshield;
	delete rectshield2;
}