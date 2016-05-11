#include "YelloBlue.h"
#include "Game.h"
#include "Number.h"

const std::string YelloBlue::yellowblueplayid = "YELLOWBLUEPLAY";

YelloBlue::~YelloBlue()
{
	//Do not do this: Playstate destructor will be called
	//PlayState::~PlayState();
}

bool YelloBlue::onEnter()
{
	PlayState::setup();
	//Load text here
	textmanager.load("Count the blue squares.", "count10", TheGame::Instance()->getdrawer());
	textmanager.load("From left to right!", "bluecircles", TheGame::Instance()->getdrawer());

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
	//load 5 blue and 5 yellow
	for (int i = 0; i < 10; i++)
	{
		if (i % 2 == 0)
		{
			playobjects.push_back(new Number(1, Vector2D(startpoint + ((imagewidth + spacing) * i),
				verticalposition), imagewidth, imageheight, "bluesquare", 1));
		}
		else
		{
			playobjects.push_back(new Number(1, Vector2D(startpoint + ((imagewidth + spacing) * i),
				verticalposition), imagewidth, imageheight, "yellowsquare", 1));
		}
	}
	////Request a redraw to draw the new state
	//TheGame::Instance()->Setredrawbool(true);
	boolloadingcomplete = true;
	return true;
}