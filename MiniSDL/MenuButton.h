#pragma once

#include "StaticObject.h"//Stationary object
#include "InputHandler.h"

class MenuButton : public StaticObject
{
public:

	MenuButton(int ms, Vector2D pos, int w, int h, std::string id, int nf, int callbid);
    ~MenuButton()
	{
	}
	//not using load - dependency injection
    //virtual void load(std::unique_ptr<LoaderParams> const &pParams);
    void draw();
    void update();
    //void clean();

    void setCallback(void(*callback)()) { m_callback = callback;}
    int getCallbackID() { return callbackid; }

private:
	//below for button animation
    //enum button_state
    //{
    //    MOUSE_OUT = 0,
    //    MOUSE_OVER = 1,
    //    CLICKED = 2
    //};
	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 0,
		CLICKED = 0
	};

    bool released;
    int callbackid;
    void (*m_callback)();
	int touchX;
	int touchY;
};
