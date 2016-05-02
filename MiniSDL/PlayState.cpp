/*
inherit from GameState, public
*/
#include "PlayState.h"
#include "Game.h"
#include "TextureManager.h"
#include "Number.h"
#include "GeneralNumber.h"
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

	if (numberobjects.empty() == false)
	{
		for (int i = 0; i < numberobjects.size(); i++)
		{
			//numberobjects[i]->clean();
			delete numberobjects[i];
		}
		numberobjects.clear();
	}
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
			dynamic_cast<Number*>(playobjects.front())->update();
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
			//TheGame::Instance()->Setredrawbool(true);
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
		//subtract the number of playobjects left to the numbe of numbers
		int i = (numberobjects.size() - 1) - playobjects.size();
		if ((i < numberobjects.size()) && (i > -1))
		{
			dynamic_cast<GeneralNumber*>(numberobjects[i])->draw();
		}
		textmanager.draw("count10", 0, 0, TheGame::Instance()->getdrawer());
		textmanager.draw("bluecircles", 0, 60, TheGame::Instance()->getdrawer());
	}
}
//On enter prepare some variables for the level
//player lives, load content get the level filesetc.
//This is called by Statemaschine
bool PlayState::onEnter()
{
	//Get the text ready, TTF_Font
	//texterwriter = Texter(TheGame::Instance()->getdrawer());
	textmanager = Texter();
	std::vector<int> positions;
	std::string strArr[] = { "bigone", "bigtwo", "bigthree", "bigfour",
		"bigfive", "bigsix", "bigseven", "bigeight", "bignine", "bigzero" };
	std::vector<std::string> counttextures = { strArr, strArr + 10 };//intialize the vector with the array values
	//Manualy load some content here like level etc.
	//Register the image with the TextureManager
	//load some play objects manually into PlayState
	TextureManager::Instance()->load("Content/bluesquare.png","bluesquare", TheGame::Instance()->getdrawer());//load intruder
	//Just letters
	TextureManager::Instance()->load("Content/bigone.png", "bigone", TheGame::Instance()->getdrawer());//load intruder
	TextureManager::Instance()->load("Content/bigtwo.png", "bigtwo", TheGame::Instance()->getdrawer());//load intruder
	TextureManager::Instance()->load("Content/bigthree.png", "bigthree", TheGame::Instance()->getdrawer());//load intruder
	TextureManager::Instance()->load("Content/bigfour.png", "bigfour", TheGame::Instance()->getdrawer());//load intruder
	TextureManager::Instance()->load("Content/bigfive.png", "bigfive", TheGame::Instance()->getdrawer());//load intruder
	TextureManager::Instance()->load("Content/bigsix.png", "bigsix", TheGame::Instance()->getdrawer());//load intruder
	TextureManager::Instance()->load("Content/bigseven.png", "bigseven", TheGame::Instance()->getdrawer());//load intruder
	TextureManager::Instance()->load("Content/bigeight.png", "bigeight", TheGame::Instance()->getdrawer());//load intruder
	TextureManager::Instance()->load("Content/bignine.png", "bignine", TheGame::Instance()->getdrawer());//load intruder
	TextureManager::Instance()->load("Content/bigzero.png", "bigtzero", TheGame::Instance()->getdrawer());//load shield
	//load some play test manually  PlayState
	textmanager.load("Count the blue squares.", "count10", TheGame::Instance()->getdrawer());
	textmanager.load("From left to right.", "bluecircles", TheGame::Instance()->getdrawer());
	//TODO: fix this: bit not correct way. Get the dimensions from the texture
	//Get texture heights
	int imagewidth = TextureManager::Instance()->GetTextureDimensions("bluesquare").getX();
	int imageheight = TextureManager::Instance()->GetTextureDimensions("bluesquare").getY();
	int numberimagewidth = TheTextureManager::Instance()->GetTextureDimensions("bigone").getX();
	int numberimageheight = TheTextureManager::Instance()->GetTextureDimensions("bigone").getY();
	//number of squares
	int numberofitems = 10;
	//****Horizontal spacing*****
	int centerwidth = TheGame::Instance()->getGameWidth() / 2;
	int spacing = 20;
	//******Horizontal spacing end****** 
	//*****vertical spacing****
	int centerheight = TheGame::Instance()->getGameHeight() / 2;
	int verticalposition = centerheight + (imageheight * 2);
	int numberverticalposition = verticalposition - numberimageheight - 30;
	//*****vertical spaces end***
	//The start point of items placement
	int startpoint = centerwidth - ((numberofitems / 2) * (imagewidth + spacing));
	//add 10 intruders to the gameobject list
	for (int i = 0; i < 10; i++)
	{
		playobjects.push_back(new Number(1, Vector2D(startpoint + 
			((imagewidth + 10) * i), verticalposition), imagewidth, imageheight, "bluesquare", 1));
	}
	for (int i = 0; i < 10; i++)
	{
		numberobjects.push_back(new GeneralNumber(1, Vector2D(startpoint - (numberimagewidth / 2)
			, numberverticalposition), numberimagewidth, numberimageheight, counttextures[i], 1));
	}
	//This is clearing say please write text
	textdonebool = false;
	boolloadingcomplete = true;
	//Request a redraw to draw the new state
	TheGame::Instance()->Setredrawbool(true);
	return true;
}
//Clear bullets here from BulletHandler and reset Inputhandler
bool PlayState::onExit()
{
	// reset the input handler
	TheInputHandler::Instance()->reset();
	TextureManager::Instance()->clearTextureMap();
	//Below is the  class handling the text
	textmanager.clear();
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
	if (!numberobjects.empty())
	{
		//delete all the game objects
		for (std::vector<GameObject*>::iterator it = numberobjects.begin(); it != numberobjects.end(); ++it)
		{
			delete (*it);
		}
		numberobjects.clear();
	}
	//This is clearing say please write text
	textdonebool = false;
	boolloadingcomplete = false;
	boolexiting = true;
	std::cout << "exiting PlayState\n";
	return true;
}