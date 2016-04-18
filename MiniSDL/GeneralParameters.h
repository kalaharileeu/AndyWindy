#pragma once

#include "Game.h"

class GeneralParameters
{
public:
	static GeneralParameters* Instance()
	{
		if (instance == 0)
		{
			instance = new GeneralParameters();
		}

		return instance;
	}
//********Get the boundaries of the game********
	//int Getxaxmax()
	//{
	//	//SDL_GetWindowSize(TheGame::Instance()->getWindow(), &gamewidth, NULL);
	//	return TheGame::Instance()->getGameWidth();
	//}
	//int Getyaxmax()
	//{
	//	//SDL_GetWindowSize(TheGame::Instance()->getWindow(), NULL, &gameheight);
	//	return TheGame::Instance()->getGameHeight();
	//}

	int Getxaxmin()
	{
		return 0;
	}

	int Getyaxmin()
	{
		return 0;
	}
//***********Done getting boundaries**********
private:
	GeneralParameters() {};
	int gamewidth;
	int gameheight;

	// singleton instance
	static GeneralParameters* instance;
};

typedef GeneralParameters  GP;
//GeneralParameters* instance = 0;



