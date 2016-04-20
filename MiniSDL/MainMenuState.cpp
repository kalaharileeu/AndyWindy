#include <iostream>
#include "MainMenuState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "InputHandler.h"
#include "StateParser.h"
#include <assert.h>


const std::string MainMenuState::menuid = "MENU";

// Callbacks
void MainMenuState::menutopPlay()
{
    TheGame::Instance()->getStateMachine()->changeState(new PlayState());
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
		s_menuToPlay();
	}
    if(!m_gameObjects.empty())
    {
			for(int i = 0; i < m_gameObjects.size(); i++)
			{
				if(m_gameObjects[i] != 0)
				{
					m_gameObjects[i]->update();
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
            m_gameObjects[i]->draw();
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
    m_callbacks.push_back(menutopPlay);
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
		gameobjects.back()->clean();
		gameobjects.pop_back();
    }

	gameobjects.clear();


    /* clear the texture manager
    for(int i = 0; i < m_textureIDList.size(); i++)
    {
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }
	*/

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

