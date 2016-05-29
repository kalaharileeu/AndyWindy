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
	counterb = -1;
	thesum, secarg, firstarg, firstargdot, secargdot, thesumdot, plus, equal, tick = nullptr;
	int a, b, sum = -1;
}

SumState::~SumState()
{
	if (tick != nullptr) { delete tick; tick = nullptr; }
	if (firstargdot != nullptr) { delete firstargdot; firstargdot = nullptr; }
	if (secargdot != nullptr) { delete secargdot; secargdot = nullptr; }
	if (thesumdot != nullptr) { delete thesumdot; thesumdot = nullptr; }
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
///*************************************UPDATE***********************************
void SumState::update()
{
	if (boolloadingcomplete && !boolexiting)
	{
		//********************************This can TEMPLATE************************
		//MAINMENU!!!!update go back to check if user want to go back to main menu
		goback->update();
		if (dynamic_cast<Goback*>(goback)->Getiftouchedbool())
		{
			TheGame::Instance()->getstatemachine()->changeState(new MainMenuState());
			return;//This return very importent, gave me lots of headaches without
		}
		//update goforward to check if user want to go back to main menu
		//*****************************************END TEMPLTATE*******************
		goforward->update();
		//CLEAR!!!! this changes the texture id if the goforward arrow is touched
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
			dynamic_cast<Number*>(thesum)->Settextureid("blue");
			dynamic_cast<Number*>(firstargdot)->Settextureid("Zero");
			dynamic_cast<Number*>(secargdot)->Settextureid("Zero");
			dynamic_cast<Number*>(thesumdot)->Settextureid("Zero");
			dynamic_cast<Number*>(tick)->Settextureid("blue");
			counter = 0;
			counterb = -1;
			a = -1;
			b = -1;
			sum = -1;
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
						a = i;//first argument
						dynamic_cast<Number*>(firstarg)->Settextureid(id);
						dynamic_cast<Number*>(firstargdot)->Settextureid(id);
					}
					if (counter == 2)
					{
						b = i;//second argument
						sum = a + b;//calculate the sum value
						dynamic_cast<Number*>(secarg)->Settextureid(id);
						dynamic_cast<Number*>(secargdot)->Settextureid(id);
						//change frame objects to color yello
						for (int j = 0; j < playobjects.size(); j++)
						{
							dynamic_cast<Number*>(frameobjects[j])->Settextureid("yellowsquare");
						}
					}
					TheGame::Instance()->Setredrawbool(true);
				}
			}
		}
		else
		{
			thesum->update();//update it to check if touched
			if (dynamic_cast<Number*>(thesum)->Getiftouchedbool())
			{
				counterb = counterb + 1;
				dynamic_cast<Number*>(thesum)->Settextureid(numbertostring[counterb]);
				dynamic_cast<Number*>(thesumdot)->Settextureid(numbertostring[counterb]);
				if (counterb > numbertostring.size() - 2) { counterb = -1; }
				if (counterb == sum)
				{ 
					//set the tick
					dynamic_cast<Number*>(tick)->Settextureid("tick");
				}
				else
				{
					//clear the tick
					dynamic_cast<Number*>(tick)->Settextureid("blue");
				}
				TheGame::Instance()->Setredrawbool(true);
			}
		}
	}
}
//**************************************UPDATE ENDS*******************************************
//*****************************************DRAW**************************************************
//In texter use "addtogether", "plus", "equal"
void SumState::draw()
{
	if (boolloadingcomplete)
	{
		if (counter == 0)
		{
			Texter::Instance()->draw("addtogether", 250, 20, TheGame::Instance()->getdrawer());
		}
		//tick has different draw depending on value
		if (dynamic_cast<Number*>(tick)->Gettextureid() == "blue")
		{
			tick->drawzoom(1.0);
		}
		//draw the argument and the answer
		firstarg->draw();
		plus->draw();
		secarg->draw();
		equal->draw();
		thesum->draw();
		//draw the Dots
		firstargdot->drawframe(0, 1);
		secargdot->drawframe(0, 1);
		thesumdot->drawframe(0, 1);
		//draw the go back to main menu button
		goback->draw();
		goforward->draw();
		if (dynamic_cast<Number*>(tick)->Gettextureid() == "tick")
		{
			tick->drawframe(0, 1);
		}


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
	boolexiting = true;
	if (tick != nullptr) { delete tick; tick = nullptr; }
	if (firstargdot != nullptr) { delete firstargdot; firstargdot = nullptr; }
	if (secargdot != nullptr) { delete secargdot; secargdot = nullptr; }
	if (thesumdot != nullptr) { delete thesumdot; thesumdot = nullptr; }
	if (firstarg != nullptr) { delete firstarg; firstarg = nullptr; }
	if (secarg != nullptr) { delete secarg; secarg = nullptr; }
	if (thesum != nullptr) { delete thesum; thesum = nullptr; }
	if (goback != nullptr) { delete goback; goback = nullptr; }
	if (goforward != nullptr) { delete goforward; goforward = nullptr; }
	if (plus != nullptr) { delete plus; plus = nullptr; }
	if (equal != nullptr) { delete equal; equal = nullptr; }

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
	numbertostring.push_back("Five");
	numbertostring.push_back("Six");
	numbertostring.push_back("Seven");
	numbertostring.push_back("Eight");
	numbertostring.push_back("Nine");
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
	int usedbyobjects = half * 5;// numbertostring.size();
	int spacing = (gamew - usedbyobjects) / (5 + 1);//(numbertostring.size() + 1);
	//******Horizontal spacing end****** 
	//*****vertical spacing****
	int y = gameh - (h2 + 90);
	//(w2 / 2) because I wat to draw half the image
	int x = 0;
	for (int i = 0; i < 5; i++)
	{
		x = spacing + ((half + spacing) * i);
		//playobjects is the numbers
		playobjects.push_back(new Number(1, Vector2D(x, y), half, h2, numbertostring[i], 1));
		//frameobject is the blue squres drawn in zoom under numbers
		frameobjects.push_back(new Number(1, Vector2D((x + (half/2)), (y + (h2/2))), w, h, "blue", 1));
	}
	//******SPACING FOR THE SUM VALUES*****************
	int xshift = 120;
	usedbyobjects = half * 5;//5 = items to space
	//the below (5 + 3), 5 item and +3 to make the spaving smaller, squash items
	spacing = (gamew - usedbyobjects) / (5 + 3);//5 = number of objects, +1 for spaces, squash items
	x = spacing + ((half + spacing) * 0) + xshift;//0 item
	firstarg = new Number(1, Vector2D(x, y - 205), half, h2, "blue", 1);
	firstargdot = new Number(1, Vector2D(x, y - 420), half, h2, "Zero", 2);//2 for 2 frames animation
	//This is for the plus sign
	x = spacing + ((half + spacing) * 1) + xshift;//1 Item
	plus = new Number(1, Vector2D(x, y - 205), half, h2, "plus", 1);
	//end plus sign
	x = spacing + ((half + spacing) * 2) + xshift;//2 Item
	secarg = new Number(1, Vector2D(x, y - 205), half, h2, "blue", 1);
	secargdot = new Number(1, Vector2D(x, y - 420), half, h2, "Zero", 2);//2 for 2 frames animation
	//This is for the equal sign
	x = spacing + ((half + spacing) * 3) + xshift;//3 Item
	equal = new Number(1, Vector2D(x, y - 205), half, h2, "equal", 1);
	//end plus sign
	x = spacing + ((half + spacing) * 4) + xshift;//4 Item
	thesum = new Number(1, Vector2D(x, y - 205), half, h2, "blue", 1);
	thesumdot = new Number(1, Vector2D(x, y - 420), half, h2, "Zero", 2);//2 for 2 frames animation
	//Tick to zero to show a blank
	tick = new Number(1, Vector2D(x, y - 205), half, h2, "blue", 2);//2 for 2 frames animation
	//************END SPACING FOR THE SUM VALUES**********************

}
