#include "SumState.h"
#include "Game.h"
#include "Goback.h"

const std::string SumState::stateid = "sumstate";

SumState::SumState()
{
	goback = nullptr;
	goforward = nullptr;
	boolloadingcomplete = false;
	boolexiting = false;
}

SumState::~SumState()
{
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

	if (!playobjects.empty())
	{
		for (int i = 0; i < playobjects.size(); i++)
		{
			delete playobjects[i];
			playobjects[i] = nullptr;
		}
		playobjects.clear();
	}
}

void SumState::update()
{
	if (boolloadingcomplete && !boolexiting)
	{

	}
}

void SumState::draw()
{
	if (boolloadingcomplete)
	{
		//draw the go back to main menu button
		goback->draw();
		goforward->draw();
		if (playobjects.empty() == false)
		{

		}

	}
}

bool SumState::onEnter()
{
	setup();
	TheGame::Instance()->Setredrawbool(true);
	return true;
}

bool SumState::onExit()
{
	if (boolloadingcomplete)
	{
		boolexiting = true;


		return true;
	}
}

void SumState::setup()
{
	//**********************************THIS CAN TEMPLATE*************************
	//game height width
	int gamew = TheGame::Instance()->getGameWidth();
	int gameh = TheGame::Instance()->getGameHeight();
	//this is the go back to main menu symbol
	int w = TextureManager::Instance()->GetTextureDimensions("exit").getX();
	int h = TextureManager::Instance()->GetTextureDimensions("exit").getY();
	goback = new Goback(1, Vector2D(0, 0), w, h, "exit", 1);
	//this is the to move to next number
	goforward = new Next(1, Vector2D(gamew - w, gameh - h), w, h, "next", 1);
	//***********************************END TEMPLATE*************************
}
