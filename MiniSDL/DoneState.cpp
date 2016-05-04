#include "DoneState.h"
//#include "Number.h"
#include "GeneralNumber.h"
#include "Game.h"
#include "MainMenuState.h"
//#include "Vector2D.h"

const std::string DoneState::doneid = "DONEONE";

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
}

/*
update state
*/
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
	if (touched == true)
	{
		TheGame::Instance()->getstatemachine()->changeState(new MainMenuState());
	}
}

void DoneState::draw()
{
	//textdonebool is true once the draw is complete, do not have to continuously draw
	//nothing is moving at this stage
	if (boolloadingcomplete)
	{
		for (int i = 0; i < numberobjects.size(); i++)
		{
			numberobjects[i]->draw();
		}

		int xposition = ((TheGame::Instance()->getGameWidth() - textmanagerdone->GetTextureDimensions("welldone").getX()) / 2);
		textmanagerdone->draw("welldone", xposition, 0, TheGame::Instance()->getdrawer());
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
	textmanagerdone = new Texter();

	//std::vector<int> positions;
	//std::string strArr[] = { "bigone", "bigzero" };
	//load the characters into the string vector
	//std::vector<std::string> counttextures = { strArr, strArr + 2 };
	//intialize the vector with the array values
	//Manualy load some content here like level etc.
	//Register the image with the TextureManager
	//load some play objects manually into PlayState
	TextureManager::Instance()->load("Content/bigone.png", "one", TheGame::Instance()->getdrawer());//load intruder
	TextureManager::Instance()->load("Content/bigzero.png", "zero", TheGame::Instance()->getdrawer());//load intruder
	textmanagerdone->load("Ten.", "welldone", TheGame::Instance()->getdrawer());

	int gamewidth = TheGame::Instance()->getGameWidth();
	/*************Spacing down here************/
	int numberimagewidth = TheTextureManager::Instance()->GetTextureDimensions("one").getX();
	int numberimageheight = TheTextureManager::Instance()->GetTextureDimensions("zero").getY();
	//******Horizontal spacing end****** 
	//*****vertical spacing****
	int centerheight = TheGame::Instance()->getGameHeight() / 2;
	int verticalposition = centerheight;
	int numberverticalposition = verticalposition - numberimageheight - 50;
	//****Horizontal spacing*****
	int centerwidth = gamewidth / 2;

	//used for loop in playstate to do this
	numberobjects.push_back(new GeneralNumber(1, Vector2D(centerwidth - numberimagewidth, numberverticalposition),
		numberimagewidth, numberimageheight, "one", 1));
	numberobjects.push_back(new GeneralNumber(1, Vector2D(centerwidth, numberverticalposition),
		numberimagewidth, numberimageheight, "zero", 1));
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
	TextureManager::Instance()->clearTextureMap();
	//Below is the  class handling the text
	textmanagerdone->clear();
	delete textmanagerdone;
	if (numberobjects.empty() == false)
	{
		for (int i = 0; i < numberobjects.size(); i++)
		{
			delete numberobjects[i];
		}
		numberobjects.clear();
	}
	//This is clearing say please write text
	textdonebool = false;
	boolloadingcomplete = false;
	boolexiting = true;
	std::cout << "exiting Donestate\n";
	return true;
}
