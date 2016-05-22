/* inherit from GameState, public*/
#include "PlayState.h"
#include "Game.h"
#include "TextureManager.h"
#include "Number.h"
#include "Goback.h"
#include "GeneralNumber.h"
#include "Vector2D.h"
#include "MainMenuState.h"
#include "DoneState.h"
#include <stdlib.h>
#include <iostream>
#include "Texter.h"

const std::string PlayState::playid = "PLAY";

PlayState::~PlayState()
{
	if (playobjects.empty() == false)
	{
		for (int i = 0; i < playobjects.size(); i++)
		{
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
		//update go back to check if user want to go back to main menu
		goback->update();
		if (dynamic_cast<Goback*>(goback)->Getiftouchedbool())
		{
			TheGame::Instance()->getstatemachine()->changeState(new MainMenuState());
			return;//This return very importent, gave me lots of headaches without
		}
		//check if a number was touched
		//begin() returns an iterator that can be used to iterate through the collection,
		//while front() return a reference
		if (donesearching == false)
		{
			for (int i = 0; i < playobjects.size(); i++)
			{
				//if it is a blue square then continue
				if (dynamic_cast<StaticObject*>(playobjects[i])->Gettextureid() == "bluesquare")
				{
					//call update to check for user interaction
					(playobjects[i])->update();
					if (dynamic_cast<Number*>(playobjects[i])->Getiftouchedbool())
					{
						//if blue square touched make it green
						dynamic_cast<Number*>(playobjects[i])->Settextureid("greensquare");
						counter++;//counter used in number display
						TheGame::Instance()->Setredrawbool(true);
					}
					break;
				}
				//if no more blue squares then done
				if (i == playobjects.size() - 1) { donesearching = true; }

			}
		}
		else
		{
			//if the playobject are empty, return to menu state
			//TheGame::Instance()->Setredrawbool(true);
			if (counter == 10)
			{
				TheGame::Instance()->getstatemachine()->changeState(new DoneState("ten"));
				return;
			}
			else if (counter == 5)
			{
				TheGame::Instance()->getstatemachine()->changeState(new DoneState("five"));
				return;
			}
			else if (counter == 3)
			{
				TheGame::Instance()->getstatemachine()->changeState(new DoneState("three"));
				return;
			}
			else if (counter == 6)
			{
				TheGame::Instance()->getstatemachine()->changeState(new DoneState("six"));
				return;
			}
		}
	}
}

void PlayState::draw()
{
	//textdonebool is true once the draw is complete, do not have to continuously draw
	//nothing is moving at this stage
	if (boolloadingcomplete)
	{
		//draw the go back to main menu button
		goback->draw();
		if (playobjects.empty() == false)
		{
			for (int i = 0; i < playobjects.size(); i++)
			{
				playobjects[i]->draw();
			}
		}
		//subtract the number of playobjects left to the numbe of numbers
		//int i = numberobjects.size() - playobjects.size();
		if (counter == 0)
		{
			int xposition = ((TheGame::Instance()->getGameWidth() - Texter::Instance()->GetTextureDimensions("count10").getX()) / 2);
			Texter::Instance()->draw("count10", xposition, 0, TheGame::Instance()->getdrawer());
			xposition = ((TheGame::Instance()->getGameWidth() - Texter::Instance()->GetTextureDimensions("bluecircles").getX()) / 2);
			Texter::Instance()->draw("bluecircles", xposition, 60, TheGame::Instance()->getdrawer());
		}
		else if (counter == 1)
		{ 
			one->draw();
			int x = ((TheGame::Instance()->getGameWidth() - Texter::Instance()->GetTextureDimensions("one").getX()) / 2);
			Texter::Instance()->draw("one", x, 0, TheGame::Instance()->getdrawer());
		}
		else if (counter == 2) 
		{ 
			two->draw(); 
			int x = ((TheGame::Instance()->getGameWidth() - Texter::Instance()->GetTextureDimensions("two").getX()) / 2);
			Texter::Instance()->draw("two", x, 0, TheGame::Instance()->getdrawer());
		}
		else if (counter == 3) 
		{ 
			three->draw(); 
			int x = ((TheGame::Instance()->getGameWidth() - Texter::Instance()->GetTextureDimensions("three").getX()) / 2);
			Texter::Instance()->draw("three", x, 0, TheGame::Instance()->getdrawer());
		}
		else if (counter == 4)
		{ 
			four->draw();
			int x = ((TheGame::Instance()->getGameWidth() - Texter::Instance()->GetTextureDimensions("four").getX()) / 2);
			Texter::Instance()->draw("four", x, 0, TheGame::Instance()->getdrawer());
		}
		else if (counter == 5)
		{ 
			five->draw();
			int x = ((TheGame::Instance()->getGameWidth() - Texter::Instance()->GetTextureDimensions("five").getX()) / 2);
			Texter::Instance()->draw("five", x, 0, TheGame::Instance()->getdrawer());
		}
		else if (counter == 6)
		{ 
			six->draw();
			int x = ((TheGame::Instance()->getGameWidth() - Texter::Instance()->GetTextureDimensions("six").getX()) / 2);
			Texter::Instance()->draw("six", x, 0, TheGame::Instance()->getdrawer());
		}
		else if (counter == 7)
		{ 
			seven->draw();
			int x = ((TheGame::Instance()->getGameWidth() - Texter::Instance()->GetTextureDimensions("seven").getX()) / 2);
			Texter::Instance()->draw("seven", x, 0, TheGame::Instance()->getdrawer());
		}
		else if (counter == 8)
		{ 
			eight->draw();
			int x = ((TheGame::Instance()->getGameWidth() - Texter::Instance()->GetTextureDimensions("eight").getX()) / 2);
			Texter::Instance()->draw("eight", x, 0, TheGame::Instance()->getdrawer());
		}
		else if (counter == 9)
		{ 
			nine->draw();
			int x = ((TheGame::Instance()->getGameWidth() - Texter::Instance()->GetTextureDimensions("nine").getX()) / 2);
			Texter::Instance()->draw("nine", x, 0, TheGame::Instance()->getdrawer());
		}

	}
}
//On enter prepare some variables for the level
//player lives, load content get the level filesetc.
//This is called by Statemaschine
bool PlayState::onEnter()
{
	setup();
	//Load text here
	int imagewidth = TextureManager::Instance()->GetTextureDimensions("bluesquare").getX();
	int imageheight = TextureManager::Instance()->GetTextureDimensions("bluesquare").getY();
	//number of squares
	int numberofitems = 10;
	int gamewidth = TheGame::Instance()->getGameWidth();
	//****Horizontal spacing*****
	int centerheight = TheGame::Instance()->getGameHeight() / 2;
	//****Horizontal spacing*****
	int spacing = (gamewidth - (numberofitems * imagewidth)) / (numberofitems + 1);
	int centerwidth = gamewidth / 2;
	//*****vertical spaces end***
	int startpoint = centerwidth - ((numberofitems / 2) * (imagewidth + spacing));
	int verticalposition = centerheight + (imageheight * 2);
	//add 10 intruders to the gameobject list
	for (int i = 0; i < 10; i++)
	{
		playobjects.push_back(new Number(1, Vector2D(startpoint + ((imagewidth + spacing) * i),
			verticalposition), imagewidth, imageheight, "bluesquare", 1));
	}
	//EXIT:insert the exit byutton, same width and height as bluesquare
	goback = new Goback(1, Vector2D(0, 0), imagewidth, imageheight, "exit", 1);
	////Request a redraw to draw the new state
	//TheGame::Instance()->Setredrawbool(true);
	boolloadingcomplete = true;
	return true;
}
//Clear and reset everything
bool PlayState::onExit()
{
	std::cout << "playstateaOnExit";
	if (goback != nullptr)
	{
		delete goback;
		goback = nullptr;
	}
	////Below is the  class handling the text
	//textmanager.clear();
	//donesearching = false;
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
	TheInputHandler::Instance()->reset();
	//TextureManager::Instance()->clearTextureMap();
	//Below is the  class handling the text

	donesearching = false;
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
	textdonebool = false;//TODO://seems like I do not hneed this
	boolloadingcomplete = false;
	boolexiting = true;
	return true;
}
//setup on enter
void PlayState::setup()
{
	//no more blue squares to look for
	donesearching = false;
	//Get the text ready, TTF_Font

	counter = 0;
	//textmanager.load("Count the blue squares.", "count10", TheGame::Instance()->getdrawer());
	//textmanager.load("From left to right!", "bluecircles", TheGame::Instance()->getdrawer());
	//TODO: fix this: bit not correct way. Get the dimensions from the texture
	//*************************This is all to do with spacing the squares**********************
	//Get texture heights
	int imagewidth = TextureManager::Instance()->GetTextureDimensions("bluesquare").getX();
	int imageheight = TextureManager::Instance()->GetTextureDimensions("bluesquare").getY();
	//EXIT:insert the exit byutton, same width and height as bluesquare
	goback = new Goback(1, Vector2D(0, 0), imagewidth, imageheight, "exit", 1);
	int numberimagewidth = TheTextureManager::Instance()->GetTextureDimensions("One").getX();
	int numberimageheight = TheTextureManager::Instance()->GetTextureDimensions("One").getY();
	//number of squares
//	int numberofitems = 10;
	int gamewidth = TheGame::Instance()->getGameWidth();
	//****Horizontal spacing*****
	int centerwidth = gamewidth / 2;
//	int spacing = (gamewidth - (numberofitems * imagewidth)) / (numberofitems + 1);
	//******Horizontal spacing end****** 
	//*****vertical spacing****
	int centerheight = TheGame::Instance()->getGameHeight() / 2;
	int verticalposition = centerheight + (imageheight * 2);
	int numberverticalposition = verticalposition - numberimageheight - 150;
	//*****vertical spaces end***
	one = new Number(1, Vector2D(centerwidth - (numberimagewidth / 2), numberverticalposition), numberimagewidth, numberimageheight, "One", 1);
	two = new Number(1, Vector2D(centerwidth - (numberimagewidth / 2), numberverticalposition), numberimagewidth, numberimageheight, "Two", 1);
	three = new Number(1, Vector2D(centerwidth - (numberimagewidth / 2), numberverticalposition), numberimagewidth, numberimageheight, "Three", 1);
	four = new Number(1, Vector2D(centerwidth - (numberimagewidth / 2), numberverticalposition), numberimagewidth, numberimageheight, "Four", 1);
	five = new Number(1, Vector2D(centerwidth - (numberimagewidth / 2), numberverticalposition), numberimagewidth, numberimageheight, "Five", 1);
	six = new Number(1, Vector2D(centerwidth - (numberimagewidth / 2), numberverticalposition), numberimagewidth, numberimageheight, "Six", 1);
	seven = new Number(1, Vector2D(centerwidth - (numberimagewidth / 2), numberverticalposition), numberimagewidth, numberimageheight, "Seven", 1);
	eight = new Number(1, Vector2D(centerwidth - (numberimagewidth / 2), numberverticalposition), numberimagewidth, numberimageheight, "Eight", 1);
	nine = new Number(1, Vector2D(centerwidth - (numberimagewidth / 2), numberverticalposition), numberimagewidth, numberimageheight, "Nine", 1);
	//This is clearing say please write text
	textdonebool = false;
	//Request a redraw to draw the new state
	TheGame::Instance()->Setredrawbool(true);
}