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
	static void destroy()
	{
		delete instance;
		instance = nullptr;
	}
//********Get the boundaries of the game********

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



