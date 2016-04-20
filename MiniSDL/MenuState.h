#ifndef MENUSTATE_H
#define MENUSTATE_H
#include "GameState.h"//this is a abstract base class
#include <vector>


class MenuState : public GameState
{
    protected:
        typedef void(*Callback)();

        virtual void setCallbacks(const std::vector<Callback>& callbacks) = 0;

        std::vector<Callback> m_callbacks;
};
#endif // MENUSTATE_H
