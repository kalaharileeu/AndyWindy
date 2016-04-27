/*
inherit from GameState, public
*/
#include "PlayState.h"
#include "Game.h"
#include "TextureManager.h"
#include "Number.h"
#include "Vector2D.h"
#include "MainMenuState.h"
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
	//CM = CollisionManager();
}
/*
Bullet handler should be updated here, check for escape key,
check if player lives are enough to continue
update level
*/
void PlayState::update()
{
	if (boolloadingcomplete && !boolexiting)
	{
		//check if a number was touched
		//begin() returns an iterator that can be used to iterate through the collection,
		//while front() return a reference
		if (playobjects.empty() == false)
		{
			//call update on the first object in the list
			//to set of check for touch or click
			playobjects.front()->update();
			if (dynamic_cast<Number*>(playobjects.front())->Getiftouchedbool())
			{
				//Set the number pointer to NULL, //an wrap it here, the set to Nullptr
				playobjects.front() = nullptr;
				playobjects.erase(playobjects.begin());
				//Update a redraw here
				TheGame::Instance()->Setredrawbool(true);
			}
		}
		else
		{
			//if the playobject are empty, return to menu state
			TheGame::Instance()->Setredrawbool(true);
			TheGame::Instance()->getstatemachine()->changeState(new MainMenuState());
		}
	}
}

void PlayState::draw()
{
	//textdonebool is true once the draw is complete, do not have to continuously draw
	//nothing is moving at this stage
	if (boolloadingcomplete)
	{
		//TheTextureManager::Instance()->draw("intruder", 60, 0, 38, 36, TheGame::Instance()->getdrawer(), SDL_FLIP_NONE);//test draw
		//TheTextureManager::Instance()->drawFrame("intruder", 200, 100, 38, 36, 0, 0, TheGame::Instance()->getdrawer(), 0.0, 255);//test draw
		//BulletHandler::Instance()->drawBullets();
		if (playobjects.empty() == false)
		{
			for (int i = 0; i < playobjects.size(); i++)
			{
				playobjects[i]->draw();
			}
		}
		//Write some text with texter
		if (!textdonebool)
		{
			//This should only called once
			texterwriter = Texter(TheGame::Instance()->getdrawer());
			textdonebool = true;
		}

	}
}
//On enter prepare some variables for the level
//player lives, load content get the level filesetc.
//This is called by Statemaschine
bool PlayState::onEnter()
{
	//Get the text ready, TTF_Font
	//texterwriter = Texter(TheGame::Instance()->getdrawer());
	std::vector<int> positions;
	std::string strArr[] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten" };
	std::vector<std::string> counttextures = { strArr, strArr + 10 };//intialize the vector with the array values
	//Manualy load some content here like level etc.
	//Register the image with the TextureManager
	TextureManager::Instance()->load("Content/one.png","one", TheGame::Instance()->getdrawer());//load intruder
	TextureManager::Instance()->load("Content/two.png", "two", TheGame::Instance()->getdrawer());//load intruder
	TextureManager::Instance()->load("Content/three.png", "three", TheGame::Instance()->getdrawer());//load intruder
	TextureManager::Instance()->load("Content/four.png", "four", TheGame::Instance()->getdrawer());//load intruder
	TextureManager::Instance()->load("Content/five.png", "five", TheGame::Instance()->getdrawer());//load intruder
	TextureManager::Instance()->load("Content/six.png", "six", TheGame::Instance()->getdrawer());//load intruder
	TextureManager::Instance()->load("Content/seven.png", "seven", TheGame::Instance()->getdrawer());//load intruder
	TextureManager::Instance()->load("Content/eight.png", "eight", TheGame::Instance()->getdrawer());//load intruder
	TextureManager::Instance()->load("Content/nine.png", "nine", TheGame::Instance()->getdrawer());//load intruder
	TextureManager::Instance()->load("Content/ten.png", "ten", TheGame::Instance()->getdrawer());//load shield
	//load some play objects manually into PlayState
	int imagewidth = TextureManager::Instance()->GetTextureDimensions("one").getX();
	int imageheight = TextureManager::Instance()->GetTextureDimensions("one").getY();
	int numberofitems = 10;
	int centerwidth = TheGame::Instance()->getGameWidth() / 2;
	int centerheight = TheGame::Instance()->getGameHeight() / 2;
	int spacing = 10;
	//The start point of items placement
	int startpoint = centerwidth - ((numberofitems / 2) * (imagewidth + spacing));
	//add 10 intruders to the gameobject list
	for (int i = 0; i < 10; i++)
	{
		playobjects.push_back(new Number(1, Vector2D(startpoint + 
			((imagewidth + 10) * i), centerheight), imagewidth, imagewidth, counttextures[i], 1));
	}
	textdonebool = false;
	boolloadingcomplete = true;
	return true;
}
//Clear bullets here from BulletHandler and reset Inputhandler
bool PlayState::onExit()
{
	//Below is the  class handling the text
	texterwriter.clear();
	textdonebool = false;//This si clearing say please write text
	boolloadingcomplete = false;
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