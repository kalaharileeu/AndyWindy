/**< StateParser is used by MainMenuState, GameState and PasueState create their
Texture objects
-StateParser uses TiXMl to move throught the xml file. To find buttons etc. (not using)

The state parser for mainmenustate loads all the texture/objects for mainmenustate
loads the texture file links and the texture ids.
*/
//Im not using xml here just load the parameters manually, hard coded
#ifndef STATEPARSER_H
#define STATEPARSER_H
#include <iostream>
#include <vector>
//#include "tinyxml.h"

class GameObject;

class StateParser
{
public:
    StateParser() {}
    ~StateParser() {}
	//not using the statefile and tinyxml here, load manually
    bool parseState(std::string stateID, std::vector<GameObject*> *pObjects, std::vector<std::string> *pTextureIDs);

private:
/**Some private helper functions used by parseState*/
    void parseObjects(std::vector<GameObject*> *pObjects);
    void parseTextures(std::vector<std::string> *pTextureIDs);
};

#endif // STATEPARSER_H
