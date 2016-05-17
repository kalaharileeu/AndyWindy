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
		}
		//check if the playobject was touched was touched
		for (int i = 0; i < playobjects.size(); i++)
		{
			#if !defined( ANDROID )
			(playobjects[0])->update();
			#endif
			#if defined( ANDROID )
			dynamic_cast<Number*>(playobjects[0])->updatefingermotion();
			#endif
			if (dynamic_cast<Number*>(playobjects[0])->Getiftouchedbool())
			{
				int x, y;
				//return value by reference
				dynamic_cast<Number*>(playobjects[0])->Getposition(x, y);
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
		if (playobjects.empty() == false)
		{
			for (int i = 0; i < playobjects.size(); i++)
			{
				dynamic_cast<Number*>(playobjects[i])->drawzoom(3.0);
				for (int i = 0; i < drawcoord.size(); i++)
				{
					TheTextureManager::Instance()->draw("star", drawcoord[i].getX(), drawcoord[i].getY(), 40, 40, TheGame::Instance()->getdrawer(),
						SDL_FLIP_NONE);
				}
			}
		}
	}
}

bool NumberDraw::onEnter()
{
	//finger touch start
	xstart, ystart = -1;
	//Do general setup
	setup();
	boolloadingcomplete = true;
	boolexiting = false;
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
	playobjects.push_back(new Number(1, Vector2D(centerwidth, centerheight), w1, h1, "One", 1));
	//this is the go back to main menu symbol
	int w = TextureManager::Instance()->GetTextureDimensions("exit").getX();
	int h = TextureManager::Instance()->GetTextureDimensions("exit").getY();
	goback = new Goback(1, Vector2D(0, 0), w, h, "exit", 1);
}