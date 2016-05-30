#include "DoneState.h"
#include "GeneralNumber.h"
#include "Game.h"
#include "YelloBlue.h"
#include "RedYellowBlue.h"
#include "MainMenuState.h"
#include "Multiplecolorsix.h"
#include "Texter.h"

const std::string DoneState::doneid = "DONEONE";

DoneState::DoneState(std::string drawvalue)
{
	numbertodraw = drawvalue;
	goforward = nullptr;
}

DoneState::~DoneState()
{
	if (numberobjects.empty() == false)
	{
		for (int i = 0; i < numberobjects.size(); i++)
		{
			//numberobjects[i]->clean();
			delete numberobjects[i];
		}
		numberobjects.clear();
	}
	if (goforward != nullptr)
	{
		delete goforward;
		goforward = nullptr;
	}
}
/*update state*/
void DoneState::update()
{
	bool touched = false;
	if (boolloadingcomplete && !boolexiting)
	{
		//check if a number was touched
		//begin() returns an iterator that can be used to iterate through the collection,
		//while front() return a reference
#if defined( ANDROID )
		if (InputHandler::Instance()->Gettouchstate())
		{
			//if screen  touched return to main menu
			touched = true;
		}
#endif
#if !defined( ANDROID )
		if (InputHandler::Instance()->getMouseButtonState(0))
		{
			touched = true;
		}
#endif
	}
	//This is to sequence the playstate loads
	if (touched == true)
	{
		if (numbertodraw == "ten")
		{
			TheGame::Instance()->getstatemachine()->changeState(new YelloBlue());
			return;
		}
		if (numbertodraw == "five")
		{
			TheGame::Instance()->getstatemachine()->changeState(new RedYelloBlue());
			return;
		}
		if (numbertodraw == "three")
		{
			TheGame::Instance()->getstatemachine()->changeState(new Multisix());
			return;
		}
		if (numbertodraw == "six")
		{
			TheGame::Instance()->getstatemachine()->changeState(new MainMenuState());
			return;
		}
	}
}

void DoneState::draw()
{
	goforward->draw();
	//textdonebool is true once the draw is complete, do not have to continuously draw
	//nothing is moving at this stage
	if (boolloadingcomplete)
	{
		for (int i = 0; i < numberobjects.size(); i++)
		{
			//numberobjects[i]->draw();
			numberobjects[i]->drawframe(0, 0);
		}
		//numbertodraw must tie up with texturemanager
		int xposition = ((TheGame::Instance()->getGameWidth() - Texter::Instance()->GetTextureDimensions(numbertodraw).getX()) / 2);
		Texter::Instance()->draw(numbertodraw, xposition, 0, TheGame::Instance()->getdrawer());
		//Request a redraw to draw the new state
		TheGame::Instance()->Setredrawbool(true);
	}
}
//On enter prepare some variables for the level
//player lives, load content get the level filesetc.
//This is called by Statemaschine
bool DoneState::onEnter()
{
	////Get the text ready, TTF_Font
	//number to draw comes from construction of the oject
	//textmanager.load(numbertodraw, numbertodraw, TheGame::Instance()->getdrawer());

	int gamewidth = TheGame::Instance()->getGameWidth();
	int gameheight = TheGame::Instance()->getGameHeight();
	/*************Spacing down here************/
	int numberimagewidth = TheTextureManager::Instance()->GetTextureDimensions("Two").getX();
	int numberimageheight = TheTextureManager::Instance()->GetTextureDimensions("Two").getY();
	//******Horizontal spacing end****** 
	//*****vertical spacing****
	int centerheight = gameheight / 2;
	int verticalposition = centerheight;
	int numberverticalposition = verticalposition - numberimageheight - 50;
	//****Horizontal spacing*****
	int centerwidth = gamewidth / 2;
	//used for loop in playstate to do this
	//Load up the numberobjects.
	if (numbertodraw == "ten")
	{
		//one have some special stuff going on, not good
		numberobjects.push_back(new GeneralNumber(1, Vector2D(centerwidth - (numberimagewidth/2), numberverticalposition),
			numberimagewidth / 2, numberimageheight, "One", 2));
		numberobjects.push_back(new GeneralNumber(1, Vector2D(centerwidth, numberverticalposition),
			numberimagewidth, numberimageheight, "Zero", 1));
	}
	if (numbertodraw == "five")
	{
		numberobjects.push_back(new GeneralNumber(1, Vector2D(centerwidth - (numberimagewidth/2), numberverticalposition),
			numberimagewidth, numberimageheight, "Five", 1));
	}
	if (numbertodraw == "three")
	{
		numberobjects.push_back(new GeneralNumber(1, Vector2D(centerwidth - (numberimagewidth / 2), numberverticalposition),
			numberimagewidth, numberimageheight, "Three", 1));
	}
	if (numbertodraw == "six")
	{
		numberobjects.push_back(new GeneralNumber(1, Vector2D(centerwidth - (numberimagewidth / 2), numberverticalposition),
			numberimagewidth, numberimageheight, "Six", 1));
	}
	//this is the go back to main menu symbol
	int w = TextureManager::Instance()->GetTextureDimensions("next").getX();
	int h = TextureManager::Instance()->GetTextureDimensions("next").getY();
	//this is the to move to next number
	goforward = new Next(1, Vector2D(gamewidth - w, gameheight - h), w, h, "next", 1);
	//This is clearing say please write text
	textdonebool = false;
	boolloadingcomplete = true;
	//Request a redraw to draw the new state
	TheGame::Instance()->Setredrawbool(true);
	return true;
}

//Clear gameobjects and all other pointer that need clearing
bool DoneState::onExit()
{
	// reset the input handler
	TheInputHandler::Instance()->reset();
	//TextureManager::Instance()->clearTextureMap();
	//Below is the  class handling the text
	//textmanagerdone->clear();
	//delete textmanagerdone;
	if (numberobjects.empty() == false)
	{
		for (int i = 0; i < numberobjects.size(); i++)
		{
			delete numberobjects[i];
		}
		numberobjects.clear();
	}
	if (goforward != nullptr)
	{
		delete goforward;
		goforward = nullptr;
	}
	//This is clearing say please write text
	textdonebool = false;
	boolloadingcomplete = false;
	boolexiting = true;
	return true;
}
