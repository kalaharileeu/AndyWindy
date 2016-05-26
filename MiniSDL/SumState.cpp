#include "SumState.h"
#include "Game.h"
#include "Goback.h"
#include "MainMenuState.h"
#include "Texter.h"

const std::string SumState::stateid = "sumstate";

SumState::SumState()
{
	goback, goforward = nullptr;
	boolloadingcomplete, boolexiting = false;
	counter = 0;
	thesum, secarg, firstarg, firstargdot, secargdot, thesumdot, plus, equal = nullptr;
}

SumState::~SumState()
{

	if (firstargdot != nullptr){ delete firstarg; firstarg = nullptr;	}
	if (secargdot != nullptr){	delete secarg; secarg = nullptr; }
	if (thesumdot != nullptr){	delete thesum; thesum = nullptr; }
	if (firstarg != nullptr) { delete firstarg; firstarg = nullptr; }
	if (secarg != nullptr) { delete secarg; secarg = nullptr; }
	if (thesum != nullptr) { delete thesum; thesum = nullptr; }
	if (goback != nullptr){	delete goback; goback = nullptr; }
	if (goforward != nullptr){ delete goforward; goforward = nullptr; }
	if (plus != nullptr) { delete plus; plus = nullptr; }
	if (equal != nullptr) { delete equal; equal = nullptr; }
	if (!playobjects.empty())
	{
		for (int i = 0; i < playobjects.size(); i++)
		{
			delete playobjects[i];
			playobjects[i] = nullptr;
		}
		playobjects.clear();
	}
	if (frameobjects.empty() == false)
	{
		for (int i = 0; i < frameobjects.size(); i++)
		{
			if (frameobjects[i] != nullptr)
			{
				delete frameobjects[i];
				frameobjects[i] = nullptr;
			}
		}
		frameobjects.clear();
	}
}

void SumState::update()
{
	if (boolloadingcomplete && !boolexiting)
	{
		//********************************This can TEMPLATE************************
		//update go back to check if user want to go back to main menu
		goback->update();
		if (dynamic_cast<Goback*>(goback)->Getiftouchedbool())
		{
			TheGame::Instance()->getstatemachine()->changeState(new MainMenuState());
			return;//This return very importent, gave me lots of headaches without
		}
		//update goforward to check if user want to go back to main menu
		//*****************************************END TEMPLTATE*******************
		goforward->update();
		//this changes the texture id if the goforward arrow is touched
		if (dynamic_cast<Next*>(goforward)->Getiftouchedbool())
		{
			//RESET set all to blue square again
			TheGame::Instance()->Setredrawbool(true);
			for (int i = 0; i < frameobjects.size(); i++)
			{
				dynamic_cast<Number*>(frameobjects[i])->Settextureid("blue");
			}
			dynamic_cast<Number*>(firstarg)->Settextureid("blue");
			dynamic_cast<Number*>(secarg)->Settextureid("blue");
			dynamic_cast<Number*>(thesum)->Settextureid("Zero");
			counter = 0;
		}
		//**********************Navigation buttons end********************************
		//Now update the game objects; can only choose wo numbers
		//Check for touched numbers
		if (counter < 2)
		{
			for (int i = 0; i < playobjects.size(); i++)
			{
				//call update to check for user interaction
				playobjects[i]->update();
				if (dynamic_cast<Number*>(playobjects[i])->Getiftouchedbool())
				{
					std::string id = dynamic_cast<Number*>(playobjects[i])->Gettextureid();
					//dynamic_cast<Number*>(playobjects[i])->Setposition(newpos);
					//if blue square touched make it green
					dynamic_cast<Number*>(frameobjects[i])->Settextureid("yellowsquare");
					counter++;//counter used in number display
					//Change the Sum values
					if (counter == 1)
					{
						dynamic_cast<Number*>(firstarg)->Settextureid(id);
					}
					if (counter == 2)
					{
						dynamic_cast<Number*>(secarg)->Settextureid(id);
					}
					TheGame::Instance()->Setredrawbool(true);
				}
			}
		}
		else
		{

		}

	}
}
//********************************DRAW***************************
//In texter use "addtogether", "plus", "equal"
void SumState::draw()
{
	if (boolloadingcomplete)
	{
		if (counter == 0)
		{
			Texter::Instance()->draw("addtogether", 250, 20, TheGame::Instance()->getdrawer());
		}
		//draw the argument and the answer
		firstarg->draw();
		plus->draw();
		secarg->draw();
		equal->draw();
		thesum->draw();
		//Dots
		firstargdot->draw();
		secargdot->draw();
		thesumdot->draw();
		//draw the go back to main menu button
		goback->draw();
		goforward->draw();
		if (!playobjects.empty())
		{
			for (int i = 0; i < playobjects.size(); i++)
			{
				frameobjects[i]->drawzoom(2.5);
				playobjects[i]->draw();
			}
		}
	}
}
//********************************ENTER***************************
bool SumState::onEnter()
{
	setup();
	/*
	 unique Code here
	*/
	//not needed.
	/*
	unique code stop
	*/
	TheGame::Instance()->Setredrawbool(true);
	boolloadingcomplete = true;
	boolexiting = false;
	return true;
}
//********************************EXIT***************************
bool SumState::onExit()
{
	if (boolloadingcomplete)
	{
	if (firstargdot != nullptr) { delete firstarg; firstarg = nullptr; }
	if (secargdot != nullptr) { delete secarg; secarg = nullptr; }
	if (thesumdot != nullptr) { delete thesum; thesum = nullptr; }
	if (firstarg != nullptr) { delete firstarg; firstarg = nullptr; }
	if (secarg != nullptr) { delete secarg; secarg = nullptr; }
	if (thesum != nullptr) { delete thesum; thesum = nullptr; }
	if (goback != nullptr) { delete goback; goback = nullptr; }
	if (goforward != nullptr) { delete goforward; goforward = nullptr; }
	if (plus != nullptr) { delete plus; plus = nullptr; }
	if (equal != nullptr) { delete equal; equal = nullptr; }
	boolexiting = true;
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
		if (frameobjects.empty() == false)
		{
			for (int i = 0; i < frameobjects.size(); i++)
			{
				if (frameobjects[i] != nullptr)
				{
					delete frameobjects[i];
					frameobjects[i] = nullptr;
				}
			}
			frameobjects.clear();
		}
		TheGame::Instance()->Setredrawbool(true);
	}
	return true;
}

void SumState::setup()
{
	numbertostring.push_back("Zero");
	numbertostring.push_back("One");
	numbertostring.push_back("Two");
	numbertostring.push_back("Three");
	numbertostring.push_back("Four");
	//numbertostring.push_back("Five");
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
	int w2 = TextureManager::Instance()->GetTextureDimensions("Two").getX();
	int h2 = TextureManager::Instance()->GetTextureDimensions("Two").getY();
	//****Horizontal spacing*****
	//w2 / 2 because i only want half the image,
	int half = w2 / 2;
	int usedbyobjects = half * numbertostring.size();
	int spacing = (gamew - usedbyobjects) / (numbertostring.size() + 1);
	//******Horizontal spacing end****** 
	//*****vertical spacing****
	int y = gameh - (h2 + 100);
	//(w2 / 2) because I wat to draw half the image
	int x = 0;
	for (int i = 0; i < numbertostring.size(); i++)
	{
		x = spacing + ((half + spacing) * i);
		//playobjects is the numbers
		playobjects.push_back(new Number(1, Vector2D(x, y), half, h2, numbertostring[i], 1));
		//frameobject is the blue squres drawn in zoom under numbers
		frameobjects.push_back(new Number(1, Vector2D((x + (half/2)), (y + (h2/2))), w, h, "blue", 1));
	}
	//******SPACING FOR THE SUM VALUES*****************
	usedbyobjects = half * 5;//5 = items to space
	spacing = (gamew - usedbyobjects) / (5 + 1);//5 = number of objects, +1 for spaces
	x = spacing + ((half + spacing) * 0);
	firstarg = new Number(1, Vector2D(x, y - 220), half, h2, "blue", 1);
	firstargdot = new Number(1, Vector2D(x, y - 410), half, h2, "Zero", 2);//2 for 2 frames animation
	//This is for the plus sign
	x = spacing + ((half + spacing) * 1);
	plus = new Number(1, Vector2D(x, y - 220), half, h2, "plus", 1);
	//end plus sign
	x = spacing + ((half + spacing) * 2);
	secarg = new Number(1, Vector2D(x, y - 220), half, h2, "blue", 1);
	secargdot = new Number(1, Vector2D(x, y - 410), half, h2, "Zero", 2);//2 for 2 frames animation
	//This is for the equal sign
	x = spacing + ((half + spacing) * 3);
	equal = new Number(1, Vector2D(x, y - 220), half, h2, "equal", 1);
	//end plus sign
	x = spacing + ((half + spacing) * 4);
	thesum = new Number(1, Vector2D(x, y - 220), half, h2, "blue", 1);
	thesumdot = new Number(1, Vector2D(x, y - 410), half, h2, "Zero", 2);//2 for 2 frames animation
	//************END SPACING FOR THE SUM VALUES**********************

}
