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
#include "DoneState.h"
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
}
/*
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
			//dynamic_cast<Number*>(playobjects.front())->update();
			playobjects.front()->update();
			if (dynamic_cast<Number*>(playobjects.front())->Getiftouchedbool())
			{
				//Set the number pointer to NULL, //an wrap it here, the set to Nullptr
				delete playobjects.front();
				playobjects.front() = nullptr;
				playobjects.erase(playobjects.begin());
				//Update a redraw here
				counter++;
				TheGame::Instance()->Setredrawbool(true);
			}
		}
		else
		{
			//if the playobject are empty, return to menu state
			//TheGame::Instance()->Setredrawbool(true);
			TheGame::Instance()->getstatemachine()->changeState(new DoneState());
		}
	}
}

void PlayState::draw()
{
	//textdonebool is true once the draw is complete, do not have to continuously draw
	//nothing is moving at this stage
	if (boolloadingcomplete)
	{
		if (playobjects.empty() == false)
		{
			for (int i = 0; i < playobjects.size(); i++)
			{
				playobjects[i]->draw();
			}
		}
		//subtract the number of playobjects left to the numbe of numbers
		//int i = numberobjects.size() - playobjects.size();
		if (counter == 1){ one->draw();}
		if (counter == 2) { two->draw(); }
		if (counter == 3) { three->draw(); }
		if (counter == 4) { four->draw(); }
		if (counter == 5) { five->draw(); }
		if (counter == 6) { six->draw(); }
		if (counter == 7) { seven->draw(); }
		if (counter == 8) { eight->draw(); }
		if (counter == 9) { nine->draw(); }

		int xposition = ((TheGame::Instance()->getGameWidth() - textmanager.GetTextureDimensions("count10").getX()) / 2);
		textmanager.draw("count10", xposition, 0, TheGame::Instance()->getdrawer());
		xposition = ((TheGame::Instance()->getGameWidth() - textmanager.GetTextureDimensions("bluecircles").getX()) / 2);
		textmanager.draw("bluecircles", xposition, 60, TheGame::Instance()->getdrawer());
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
	counter = 0;
	//Manualy load some content here like level etc.
	//Register the image with the TextureManager
	//load some play objects manually into PlayState
	TextureManager::Instance()->load("Content/bluesquare.png","bluesquare", TheGame::Instance()->getdrawer());//load intruder
	//Just letters
	TextureManager::Instance()->load("Content/bigone.png", "One", TheGame::Instance()->getdrawer());//load intruder
	TextureManager::Instance()->load("Content/bigtwo.png", "Two", TheGame::Instance()->getdrawer());//load intruder
	TextureManager::Instance()->load("Content/bigthree.png", "Three", TheGame::Instance()->getdrawer());//load intruder
	TextureManager::Instance()->load("Content/bigfour.png", "Four", TheGame::Instance()->getdrawer());//load intruder
	TextureManager::Instance()->load("Content/bigfive.png", "Five", TheGame::Instance()->getdrawer());//load intruder
	TextureManager::Instance()->load("Content/bigsix.png", "Six", TheGame::Instance()->getdrawer());//load intruder
	TextureManager::Instance()->load("Content/bigseven.png", "Seven", TheGame::Instance()->getdrawer());//load intruder
	TextureManager::Instance()->load("Content/bigeight.png", "Eight", TheGame::Instance()->getdrawer());//load intruder
	TextureManager::Instance()->load("Content/bignine.png", "Nine", TheGame::Instance()->getdrawer());//load intruder
	//TextureManager::Instance()->load("Content/bigzero.png", "bigtzero", TheGame::Instance()->getdrawer());//load shield
	//load some play test manually  PlayState
	textmanager.load("Count the blue squares.", "count10", TheGame::Instance()->getdrawer());
	textmanager.load("From left to right!", "bluecircles", TheGame::Instance()->getdrawer());
	//TODO: fix this: bit not correct way. Get the dimensions from the texture
	//*************************This is all to do with spacing the squares**********************
	//Get texture heights
	int imagewidth = TextureManager::Instance()->GetTextureDimensions("bluesquare").getX();
	int imageheight = TextureManager::Instance()->GetTextureDimensions("bluesquare").getY();
	int numberimagewidth = TheTextureManager::Instance()->GetTextureDimensions("One").getX();
	int numberimageheight = TheTextureManager::Instance()->GetTextureDimensions("One").getY();
	//number of squares
	int numberofitems = 10;
	int gamewidth = TheGame::Instance()->getGameWidth();
	//****Horizontal spacing*****
	int centerwidth = gamewidth / 2;
	int spacing = (gamewidth - (numberofitems * imagewidth)) / (numberofitems + 1);
	//******Horizontal spacing end****** 
	//*****vertical spacing****
	int centerheight = TheGame::Instance()->getGameHeight() / 2;
	int verticalposition = centerheight + (imageheight * 2);
	int numberverticalposition = verticalposition - numberimageheight - 50;
	//*****vertical spaces end***
	//The start point of items placement
	int startpoint = centerwidth - ((numberofitems / 2) * (imagewidth + spacing));
	//add 10 intruders to the gameobject list
	for (int i = 0; i < 10; i++)
	{
		playobjects.push_back(new Number(1, Vector2D(startpoint + ((imagewidth + spacing) * i), verticalposition), imagewidth, imageheight, "bluesquare", 1));
	}
	one = new Number(1, Vector2D(centerwidth - (numberimagewidth / 2), numberverticalposition), numberimagewidth, numberimageheight, "One", 1);
	two = new Number(1, Vector2D(centerwidth - (numberimagewidth / 2), numberverticalposition), numberimagewidth, numberimageheight, "Two", 1);
	three = new Number(1, Vector2D(centerwidth - (numberimagewidth / 2), numberverticalposition), numberimagewidth, numberimageheight, "Three", 1);
	four = new Number(1, Vector2D(centerwidth - (numberimagewidth / 2), numberverticalposition), numberimagewidth, numberimageheight, "Four", 1);
	five = new Number(1, Vector2D(centerwidth - (numberimagewidth / 2), numberverticalposition), numberimagewidth, numberimageheight, "Five", 1);
	six = new Number(1, Vector2D(centerwidth - (numberimagewidth / 2), numberverticalposition), numberimagewidth, numberimageheight, "Six", 1);
	seven = new Number(1, Vector2D(centerwidth - (numberimagewidth / 2), numberverticalposition), numberimagewidth, numberimageheight, "Seven", 1);
	eight = new Number(1, Vector2D(centerwidth - (numberimagewidth / 2), numberverticalposition), numberimagewidth, numberimageheight, "Eight", 1);
	nine = new Number(1, Vector2D(centerwidth - (numberimagewidth / 2), numberverticalposition), numberimagewidth, numberimageheight, "Nine", 1);
	//numberobjects.push_back(new GeneralNumber(1, Vector2D(centerwidth - (numberimagewidth / 2), numberverticalposition), numberimagewidth, numberimageheight, "One", 1));
	//numberobjects.push_back(new GeneralNumber(1, Vector2D(centerwidth - (numberimagewidth / 2), numberverticalposition), numberimagewidth, numberimageheight, "Two", 1));
	//numberobjects.push_back(new GeneralNumber(1, Vector2D(centerwidth - (numberimagewidth / 2), numberverticalposition), numberimagewidth, numberimageheight, "Three", 1));
	//numberobjects.push_back(new GeneralNumber(1, Vector2D(centerwidth - (numberimagewidth / 2), numberverticalposition), numberimagewidth, numberimageheight, "Four", 1));
	//numberobjects.push_back(new GeneralNumber(1, Vector2D(centerwidth - (numberimagewidth / 2), numberverticalposition), numberimagewidth, numberimageheight, "Five", 1));
	//numberobjects.push_back(new GeneralNumber(1, Vector2D(centerwidth - (numberimagewidth / 2), numberverticalposition), numberimagewidth, numberimageheight, "Six", 1));
	//numberobjects.push_back(new GeneralNumber(1, Vector2D(centerwidth - (numberimagewidth / 2), numberverticalposition), numberimagewidth, numberimageheight, "Seven", 1));
	//numberobjects.push_back(new GeneralNumber(1, Vector2D(centerwidth - (numberimagewidth / 2), numberverticalposition), numberimagewidth, numberimageheight, "Eight", 1));
	//numberobjects.push_back(new GeneralNumber(1, Vector2D(centerwidth - (numberimagewidth / 2), numberverticalposition), numberimagewidth, numberimageheight, "Nine", 1));
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

	delete one;
	one = nullptr;
	delete two;
	two = nullptr;
	delete three;
	three = nullptr;
	delete four;
	four = nullptr;
	delete five;
	five = nullptr;
	delete six;
	six = nullptr;
	delete seven;
	seven = nullptr;
	delete eight;
	eight = nullptr;
	delete nine;
	nine = nullptr;

	if (playobjects.empty() == false)
	{
		for (int i = 0; i < playobjects.size(); i++)
		{
			if (playobjects[i] != nullptr)
			{
				delete playobjects[i];
				playobjects[i] = nullptr;
			}
		}
		playobjects.clear();
	}
	//This is clearing say please write text
	textdonebool = false;
	boolloadingcomplete = false;
	boolexiting = true;
	std::cout << "exiting PlayState\n";
	return true;
}