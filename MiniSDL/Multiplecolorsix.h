#pragma once
#pragma once
#include "Game.h"
#include "Number.h"
#include "PlayState.h"

class Multisix : public PlayState
{
public:

	bool onEnter()
	{
		PlayState::setup();
		//Load text here
		textmanager.load("Count the blue squares.", "count10", TheGame::Instance()->getdrawer());
		textmanager.load("From left to right!", "bluecircles", TheGame::Instance()->getdrawer());

		int imagewidth = TextureManager::Instance()->GetTextureDimensions("bluesquare").getX();
		int imageheight = TextureManager::Instance()->GetTextureDimensions("bluesquare").getY();
		//number of squares horizontally
		int numberofitems = 10;
		int gamewidth = TheGame::Instance()->getGameWidth();
		//****Horizontal spacing*****
		int centerheight = TheGame::Instance()->getGameHeight() / 2;
		//****Horizontal spacing*****
		//only two space here left and write side of the screeen
		int spacing = (gamewidth - (numberofitems * imagewidth)) / 2;
		int centerwidth = gamewidth / 2;
		//*****vertical spaces end***
		//****vertical and horizontal start points******
		int startpoint = centerwidth - ((numberofitems / 2) * (imagewidth));
		int verticalposition = centerheight + (imageheight * 2);
		//add 20 playobject "Number" to the gameobject list
		for (int i = 0; i < 20; i++)
		{
			//There should be 6 blue squares
			if ((i + 1) % 3 == 0)
			{
				playobjects.push_back(new Number(1, Vector2D(startpoint + ((imagewidth) * (i % 10)),
					verticalposition + (imageheight * (i / numberofitems)) ), imagewidth, imageheight, "bluesquare", 1));
			}
			else if ((i + 1) % 2 == 0)
			{
				playobjects.push_back(new Number(1, Vector2D(startpoint + ((imagewidth) * (i % 10)),
					verticalposition + (imageheight * (i / numberofitems))), imagewidth, imageheight, "yellowsquare", 1));
			}
			else
			{
				playobjects.push_back(new Number(1, Vector2D(startpoint + ((imagewidth) * (i % 10)),
					verticalposition + (imageheight * (i / numberofitems))), imagewidth, imageheight, "redsquare", 1));
			}
		}

		boolloadingcomplete = true;
		return true;
	}

	std::string getStateID() const { return redyellowblueplayid; }
private:
	static const std::string redyellowblueplayid;
};
//This goes here not at the top: compiler need it here
const std::string Multisix::redyellowblueplayid = "MULTISIXID";