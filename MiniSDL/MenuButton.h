#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include "StaticObject.h"//Stationary object
#include "ObjectFactory.h"
#include "InputHandler.h"

class MenuButton : public StaticObject
{
public:

	MenuButton(int ms, Vector2D pos, int w, int h, std::string id, int nf, int callbid);
    ~MenuButton(){ std::cout << "Menubutton destroyed";  }
	//not using load - dependency injection
    //virtual void load(std::unique_ptr<LoaderParams> const &pParams);
    void draw();
    void update();
    //void clean();

    void setCallback(void(*callback)()) { m_callback = callback;}
    int getCallbackID() { return callbackid; }

private:

    enum button_state
    {
        MOUSE_OUT = 0,
        MOUSE_OVER = 1,
        CLICKED = 2
    };

    bool released;
    int callbackid;
    void (*m_callback)();
};

//class MenuButtonCreator : public BaseCreator
//{
//    GameObject* createGameObject() const
//    {
//        return new MenuButton();
//    }
//};
#endif // MENUBUTTON_H
