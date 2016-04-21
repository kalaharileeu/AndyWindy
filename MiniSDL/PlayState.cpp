/*
inherit from GameState, public
*/
#include "PlayState.h"
#include "Game.h"
#include "TextureManager.h"
#include "Intruder.h"
#include "Shield.h"
#include "Vector2D.h"
#include <stdlib.h>
#include <iostream>

const std::string PlayState::playid = "PLAY";

PlayState::~PlayState()
{
	if (playobjects.empty() == false)
	{
		for (int i = 0; i < playobjects.size(); i++)
		{
			//playobjects[i]->clean();
			delete playobjects[i];
		}
		playobjects.clear();
	}
	CM = CollisionManager();
}//delete the level pointer
/*
Bullet handler should be updated here, check for escape key,
check if player lives are enough to continue
update level
*/
void PlayState::update()
{
	if (boolloadingcomplete && !boolexiting)
	{
		CM.checkWrapperWrappedCollision(playobjects);
		for (int i = 0; i < playobjects.size(); i++)
		{
			//Check for any collisions
			//CM.checkWrapperWrappedCollision(playobjects);
			if (playobjects[i] != NULL)
			{
				if (playobjects[i]->type() == "Intruder")
				{
					//If a intruder collided with a shield, collision will be true
					if (playobjects[i]->Getcollision())
					{
						//Set the intruder pointer to NULL, becasue it now wrapped
						//by a shield
						playobjects[i] = NULL;
						playobjects.erase(playobjects.begin() + i);
					}
				}
				playobjects[i]->update();
			}
		}
		CM.checkgeneralcollision(playobjects);
	}
}

void PlayState::draw()
{
	if (boolloadingcomplete)
	{
		//TheTextureManager::Instance()->draw("intruder", 60, 0, 38, 36, TheGame::Instance()->getdrawer(), SDL_FLIP_NONE);//test draw
		//TheTextureManager::Instance()->drawFrame("intruder", 200, 100, 38, 36, 0, 0, TheGame::Instance()->getdrawer(), 0.0, 255);//test draw
		//BulletHandler::Instance()->drawBullets();
		for (int i = 0; i < playobjects.size(); i++)
		{
			playobjects[i]->draw();
		}
	}
}
//On enter prepare some variables for the level
//player lives, load content get the level filesetc.
bool PlayState::onEnter()
{
	//Manualy load some content here like level etc.
	//Register the image with the TextureManager
	TextureManager::Instance()->load("Content/enemy2.png","intruder", TheGame::Instance()->getdrawer());//load intruder
	TextureManager::Instance()->load("Content/shield.png", "shield", TheGame::Instance()->getdrawer());//load shield
	//load some play objects manually into PlayState
	//playobjects.push_back(new Intruder(1, Vector2D(150, 150), 60, 60, "intruder", 1));
	//playobjects.push_back(new Shield(1, Vector2D(200, 200), 60, 60, "shield", 1));
	//add 10 intruders to the gameobject list
	for (int i = 0; i < 2; i++)
	{
		playobjects.push_back(new Intruder(1, Vector2D((80 * i) + 10, (80 * i) + 10), 60, 60, "intruder", 1));
	}

	//add 10 shields to the gameobject list
	for (int i = 0; i < 10; i++)
	{
		playobjects.push_back(new Shield(1, Vector2D(80, 900), 60, 60, "shield", 1));
	}
	boolloadingcomplete = true;
	return true;
}
//Clear bullets here from BulletHandler and reset Inputhandler
bool PlayState::onExit()
{
	// clean the game objects
	if (!playobjects.empty())
	{
		//delete all the game objects
		for (std::vector<GameObject*>::iterator it = playobjects.begin(); it != playobjects.end(); ++it)
		{
			delete (*it);
		}
		playobjects.clear();
	}
	boolexiting = true;
	std::cout << "exiting PlayState\n";
	return true;
}