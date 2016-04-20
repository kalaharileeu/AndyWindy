
#include "MenuButton.h"
/*movespeed, position, width, height, textureid, numframes, callbackid*/
MenuButton::MenuButton(int ms, Vector2D pos, int w, int h, std::string id, int nf, int callbid)
	: StaticObject(ms, pos, w, h, id, nf), m_callback(0), released(true)
{
	callbackid = callbackid;
}

//void MenuButton::load(std::unique_ptr<LoaderParams> const &pParams)
//{
//    ShooterObject::load(std::move(pParams));
//    m_callbackID = pParams->getCallbackID();
//    m_currentFrame = MOUSE_OUT;
//}

void MenuButton::draw()
{
	StaticObject::draw();
}

void MenuButton::update()
{
    Vector2D* pMousePos = TheInputHandler::Instance()->getMousePosition();

    if(pMousePos->getX() < (position.getX() + width) && pMousePos->getX() > position.getX()
       && pMousePos->getY() < (position.getY() + height) && pMousePos->getY() > position.getY())
    {
        if(TheInputHandler::Instance()->getMouseButtonState(LEFT) && released)
        {
			currentframe = CLICKED;

            if(m_callback != 0)
            {
                m_callback();
            }

			released = false;
        }
        else if(!TheInputHandler::Instance()->getMouseButtonState(LEFT))
        {
			released = true;
            currentframe = MOUSE_OVER;
        }
    }
    else
    {
		currentframe = MOUSE_OUT;
    }
}

//void MenuButton::clean()
//{
//	StaticObject::clean();
//}
