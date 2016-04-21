
#include "StateParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
//#include "ObjectFactory.h"

using namespace std;

/*
The state parser for mainmenustate loads all the texture/objects for mainmenustate
	loads the texture file links and the texture ids.
*/

bool StateParser::parseState(string stateID, vector<GameObject *> *gameobjects, std::vector<std::string> *textureids)
{
    /** now parse the textures and fill the pTextureIDs vector */
    parseTextures(textureids);
    parseObjects(gameobjects);
    return true;
}
/**Helper function to get the texture filename and id's and load them into TextureManager*/
void StateParser::parseTextures(std::vector<std::string> *textureids)
{
        string filenameattribute = "Content/Menu/button.png";
        string idattribute = "playbutton";
		//add the id to the list so that it can be retrieved
		textureids->push_back(idattribute); // push the id into the list
        TheTextureManager::Instance()->load(filenameattribute, idattribute, TheGame::Instance()->getdrawer());

		filenameattribute = "Content/Menu/exit.png";
		idattribute = "exitbutton";
		//add the id to the list so that it can be retrieved
		textureids->push_back(idattribute); // push the id into the list
		TheTextureManager::Instance()->load(filenameattribute, idattribute, TheGame::Instance()->getdrawer());
}

void StateParser::parseObjects(std::vector<GameObject *> *gameobjects)
{
    //int x, y, width, height, numFrames, callbackID, animSpeed;
    //string textureID;
	//gameobjects->load(std::unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animSpeed)));
	//int x, int y, int width, int height, std::string textureID, int numFrames, animationspeed if needed
	gameobjects->push_back(new MenuButton(0, Vector2D((TheGame::Instance()->getGameWidth() / 2 - 200), 20),
		400, 100, "playbutton", 0, 1));
	gameobjects->push_back(new MenuButton(0, Vector2D(TheGame::Instance()->getGameWidth() / 2 - 200, 140),
		400, 100, "exitbutton", 0, 2));
}
