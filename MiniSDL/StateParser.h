/**< StateParser is used by MainMenuState, GameState and PasueState create their Texture objects
-StateParser uses TiXMl to move throught the xml file. To find buttons etc.
 */


#ifndef STATEPARSER_H
#define STATEPARSER_H
#include <iostream>
#include <vector>
#include "tinyxml.h"

class GameObject;

class StateParser
{
public:

    StateParser() {}
    ~StateParser() {}

    bool parseState(const char* stateFile, std::string stateID, std::vector<GameObject*> *pObjects, std::vector<std::string> *pTextureIDs);

private:
/**Some private helper functions used by parseState*/
    void parseObjects(TiXmlElement* pStateRoot, std::vector<GameObject*> *pObjects);
    void parseTextures(TiXmlElement* pStateRoot, std::vector<std::string> *pTextureIDs);
};

#endif // STATEPARSER_H
