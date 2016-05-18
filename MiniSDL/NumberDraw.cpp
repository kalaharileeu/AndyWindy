#include "NumberDraw.h"
#include "Goback.h"
#include "MainMenuState.h"
#include "InputHandler.h"

const std::string NumberDraw::stateid = "DRAWNUMBER";

NumberDraw::~NumberDraw()
{
	if (playobjects.empty() == false)
	{
		for (int i = 0; i < playobjects.size(); i++)
		{
			delete playobjects[i];
		}
		playobjects.clear();
	}
	if (goback != nullptr)
	{
		delete goback;
		goback = nullptr;
	}
}

void NumberDraw::update()
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
		//update goforward to check if user want to go back to main menu

		goforward->update();
		//this changes the texture id if the goforward arrow is touched
		if (dynamic_cast<Next*>(goforward)->Getiftouchedbool())
		{
			//change the number clear clear all decorating values
			//just one object in playobjects
			//count +1 moves to the next text in the vector, numbertostring change change the 
			//texture id
			dynamic_cast<Number*>(playobjects[0])->Settextureid(numbertostring[counter++]);
			if (counter > (numbertostring.size() - 1)) { counter = 0; }//check not over size limit
			drawcoord.clear();
			TheGame::Instance()->Setredrawbool(true);
		}
		//check if the playobject was touched was touched
		for (int i = 0; i < playobjects.size(); i++)
		{
			#if !defined( ANDROID )
			(playobjects[0])->update();
			#endif
			#if defined( ANDROID )
			//Doing a dffient update for touch and drag...mmm..
			//because te response is deffent to touch and lift
			dynamic_cast<Number*>(playobjects[0])->updatefingermotion();
			#endif
			if (dynamic_cast<Number*>(playobjects[0])->Getiftouchedbool())
			{
				int x, y;
				//return value by reference
				dynamic_cast<Number*>(playobjects[0])->Getposition(x, y);
				//limit the size to draw to 100
				if (drawcoord.size() < 100)
				{
					drawcoord.push_back(Vector2D(x, y));
					TheGame::Instance()->Setredrawbool(true);
				}
			}
		}
	}
}

void NumberDraw::draw()
{
	if (boolloadingcomplete)
	{
		//draw the go back to main menu button
		goback->draw();
		goforward->draw();
		if (playobjects.empty() == false)
		{
			for (int i = 0; i < playobjects.size(); i++)
			{
				//draw a playobject zoomed
				dynamic_cast<Number*>(playobjects[i])->drawzoom(3.0);
				for (int i = 0; i < drawcoord.size(); i++)
				{
					//Draw some images when number is traced with finger
					TheTextureManager::Instance()->draw("star", drawcoord[i].getX(), drawcoord[i].getY(),
						60, 60, TheGame::Instance()->getdrawer(), SDL_FLIP_NONE);
				}
			}
		}
	}
}

bool NumberDraw::onEnter()
{
	counter = 1;
	//finger touch start
	xstart, ystart = -1;
	//Do general setup
	setup();
	boolloadingcomplete = true;
	boolexiting = false;
	//Doing all these push backs to keep the compiler happy
	//will get a better way
	numbertostring.push_back("Zero");
	numbertostring.push_back("One");
	numbertostring.push_back("Two");
	numbertostring.push_back("Three");
	numbertostring.push_back("Four");
	numbertostring.push_back("Five");
	numbertostring.push_back("Six");
	numbertostring.push_back("Seven");
	numbertostring.push_back("Eight");
	numbertostring.push_back("Nine");
	TheGame::Instance()->Setredrawbool(true);
	return true;
}
//Clear/reset verything
bool NumberDraw::onExit()
{
	boolloadingcomplete = false;
	boolexiting = true;
	if (goback != nullptr)
	{
		delete goback;
		goback = nullptr;
	}
	if (goforward != nullptr)
	{
		delete goforward;
		goforward = nullptr;
	}
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
	TheGame::Instance()->Setredrawbool(true);
	return true;
}

void NumberDraw::setup()
{
	//Load text to be written here
	//textmanager.load("Draw the number.", "drawnumber", TheGame::Instance()->getdrawer());
	//image height width, the number image loaded by game.cpp
	int w1 = TextureManager::Instance()->GetTextureDimensions("One").getX();
	int h1 = TextureManager::Instance()->GetTextureDimensions("One").getY();
	//game height width
	int gamew = TheGame::Instance()->getGameWidth();
	int gameh = TheGame::Instance()->getGameHeight();
	//****Horizontal spacing*****
	int centerwidth = gamew / 2;
	//******Horizontal spacing end****** 
	//*****vertical spacing****
	int centerheight = gameh / 2;
	//Load a player object here. Texture "One" registered by game.cpp
	playobjects.push_back(new Number(1, Vector2D(centerwidth , centerheight), w1, h1, "Zero", 1));
	//this is the go back to main menu symbol
	int w = TextureManager::Instance()->GetTextureDimensions("exit").getX();
	int h = TextureManager::Instance()->GetTextureDimensions("exit").getY();
	goback = new Goback(1, Vector2D(0, 0), w, h, "exit", 1);
	//this is the to move to next number
	goforward = new Next(1, Vector2D(gamew - w, gameh - h), w, h, "next", 1);
}