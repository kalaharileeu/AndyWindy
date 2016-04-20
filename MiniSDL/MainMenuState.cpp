#include <iostream>
#include "MainMenuState.h"
#include "Game.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "InputHandler.h"
#include "StateParser.h"

const std::string MainMenuState::menuid = "MENU";

// Callbacks
void MainMenuState::menutopplay()
{
	//change to playstate
    TheGame::Instance()->getstatemachine()->changeState(new PlayState());
}

void MainMenuState::exitfromMenu()
{
    TheGame::Instance()->quit();
}

// end callbacks

void MainMenuState::update()
{
	if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
	{
		menutopplay();
	}
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

bool MainMenuState::onEnter()
{
    // parse the state
    StateParser stateParser;
	//Im not going to use state parser with TinyXml
	//Ill just load the buttons etc. manually
    //stateParser.parseState("assets/attack.xml", s_menuID, &m_gameObjects, &m_textureIDList);
	stateParser.parseState(menuid, &gameobjects, &textureidlist);
    m_callbacks.push_back(0);
    m_callbacks.push_back(menutopplay);
    m_callbacks.push_back(exitfromMenu);
    // set the callbacks for menu items
    setCallbacks(m_callbacks);
	boolloadingcomplete = true;
    std::cout << "entering MenuState\n";
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

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
{
    // go through the game objects
    if(!gameobjects.empty())
    {
        for(int i = 0; i < gameobjects.size(); i++)
        {
            // if they are of type MenuButton then assign a callback based on the id passed in from the file
            if(dynamic_cast<MenuButton*>(gameobjects[i]))
            {
                MenuButton* pButton = dynamic_cast<MenuButton*>(gameobjects[i]);
                pButton->setCallback(callbacks[pButton->getCallbackID()]);
            }
        }
    }
}

