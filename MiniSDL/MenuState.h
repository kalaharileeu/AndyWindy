#ifndef MENUSTATE_H
#define MENUSTATE_H
#include "GameState.h"//this is a abstract base class
#include <vector>


class MenuState : public GameState
{
public:
	virtual ~MenuState() {}//destructor
	virtual void update() {}//function like the functions in the Game class
	virtual void draw() {}//function like the functions in the Game class
	virtual bool onEnter() { return false; }//load
	virtual bool onExit() { return false; }//clean
	virtual void resume() {}
	//const function can not change data members
	virtual std::string getStateID() const = 0;

protected:
    typedef void(*Callback)();
    virtual void setCallbacks(const std::vector<Callback>& callbacks) = 0;
    std::vector<Callback> m_callbacks;
};
#endif // MENUSTATE_H
