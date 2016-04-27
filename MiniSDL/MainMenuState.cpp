#include <iostream>
#include "MainMenuState.h"
//#include "Game.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "InputHandler.h"
#include "StateParser.h"

const std::string MainMenuState::menuid = "MENU";

void MainMenuState::update()
{
	//TODO:Remove this the space bar should not take you to play screen
	//if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
	//{
	//	menutopplay();
	//}
    if(!gameobjects.empty())
    {
		for(int i = 0; i < gameobjects.size(); i++)
		{
			if(gameobjects[i] != 0)
			{
				gameobjects[i]->update();
			}
		}
    }
}

void MainMenuState::draw()
{
    if(boolloadingcomplete && !gameobjects.empty())
    {
        for(int i = 0; i < gameobjects.size(); i++)
        {
			gameobjects[i]->draw();
        }
    }
}
//on enter call the state parser to load the object/buttons
bool MainMenuState::onEnter()
{
    //The state parser for mainmenustate loads all the texture/objects for mainmenustate
	//loads the texture file links and the texture ids.
    StateParser stateParser;
	//Im not going to use state parser with TinyXml
	//Ill just load the buttons etc. manually
    //stateParser.parseState("assets/attack.xml", s_menuID, &m_gameObjects, &m_textureIDList);
	stateParser.parseState(menuid, &gameobjects, &textureidlist);
	//m_callbacks reside in Menustate.h
	//To call the function give the index: 0, 1 or 2
    m_callbacks.push_back(0);
    m_callbacks.push_back(menutopplay);
    m_callbacks.push_back(exitfromMenu);
    // set the callbacks for menu items
    setCallbacks(m_callbacks);
	boolloadingcomplete = true;
    return true;
}

bool MainMenuState::onExit()
{
	boolexiting = true;
    // clean the game objects
    if(boolloadingcomplete && !gameobjects.empty())
    {
		//delete all the game objects
		for (std::vector<GameObject*>::iterator it = gameobjects.begin(); it != gameobjects.end(); ++it)
		{
			delete (*it);
		}
		gameobjects.clear();
		////gameobjects.back()->clean();
		//gameobjects.pop_back();
    }

    // reset the input handler
    TheInputHandler::Instance()->reset();

    std::cout << "exiting MenuState\n";
    return true;
}
//pass in a vector of local functions to use in call back
void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
{
    // go through the game objects
    if(!gameobjects.empty())
    {
        for(int i = 0; i < gameobjects.size(); i++)
        {
            // if they are of type MenuButton then assign a callback based on the id passed in from the file
			//dynamic_cast to upcast gameobject to MenuButton
            if(dynamic_cast<MenuButton*>(gameobjects[i]))
            {
                MenuButton* button = dynamic_cast<MenuButton*>(gameobjects[i]);
				//The buuton callback id(getCallbackId()) ties up with the 
				//call backs in the local callback list
				//pass the callback function to the button, based on 
				//the call back number you get from the button
                button->setCallback(callbacks[button->getCallbackID()]);
            }
        }
    }
}
// Callbacks linked to buttons
void MainMenuState::menutopplay()
{
	//change to playstate
	TheGame::Instance()->getstatemachine()->changeState(new PlayState());
}
//callbacks linked to buttons
void MainMenuState::exitfromMenu()
{
	TheGame::Instance()->quit();
}
// end callbacks


