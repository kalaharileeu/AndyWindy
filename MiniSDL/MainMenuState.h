#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H
#include <vector>
#include "MenuState.h"
#include "GameObject.h"

class MainMenuState : public MenuState
{
    public:
		virtual ~MainMenuState() {}
        virtual void update();
        virtual void draw();
        virtual bool onEnter();//Enter state
        virtual bool onExit();//Exit state
        virtual std::string getStateID() const { return menuid; }//What state is it?
    private:
        virtual void setCallbacks(const std::vector<Callback>&callbacks);
        static const std::string menuid;
		//vector of GameObject* to store our menu items:
        std::vector<GameObject*> gameobjects;//vector of GameObject* to store our menu items:
		// call back functions for menu items
		//functions as static; this is because our callback 
		//function pointers will only support static functions
        static void menutopplay();
        static void exitfromMenu();
		static void menutopdraw();
		static void menutosum();
};
#endif // MAINMENUSTATE_H
