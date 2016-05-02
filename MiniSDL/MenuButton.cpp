
#include "MenuButton.h"

/*movespeed, position, width, height, textureid, numframes, callbackid*/
MenuButton::MenuButton(int ms, Vector2D pos, int w, int h, std::string id, int nf, int callbid)
	: StaticObject(ms, pos, w, h, id, nf)
{
	m_callback = 0;
	released = true;
	callbackid = callbid;
}
//Not using dependency injection
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
//The update event can cause a redraw
void MenuButton::update()
{
#if !defined( ANDROID )
	Vector2D* pMousePos = TheInputHandler::Instance()->getMousePosition();

	if (pMousePos->getX() < (position.getX() + width) && pMousePos->getX() > position.getX()
		&& pMousePos->getY() < (position.getY() + height) && pMousePos->getY() > position.getY())
	{
		if (TheInputHandler::Instance()->getMouseButtonState(LEFT) && released)
		{
			//CLICKED is button state 2 see header file
			currentframe = CLICKED;

			if (m_callback != 0)
			{
				m_callback();
			}

			released = false;
		}
		else if (!TheInputHandler::Instance()->getMouseButtonState(LEFT))
		{
			released = true;
			currentframe = MOUSE_OVER;
		}
		//Set Game to redraw the update
		TheGame::Instance()->Setredrawbool(true);
	}
	else
	{
		currentframe = MOUSE_OUT;
	}
#endif
//#if defined( ANDROID )

		//int touchX = InputHandler::Instance()->Gettouchposition()->getX();
		//int touchy = InputHandler::Instance()->Gettouchposition()->getY();

		//if ((touchX > position.getX() && touchX < position.getX() + width) &&
		//	(touchy > position.getY() && touchy < position.getY() + height))
		//{

		//	currentframe = CLICKED;
		//	//false: it has not beed released
		//	//released = false;
		//	TheGame::Instance()->Setredrawbool(true);
		//}


		int touchX = InputHandler::Instance()->Getreleaseposition()->getX();
		int touchy = InputHandler::Instance()->Getreleaseposition()->getY();
		//if (touchX > position.getX())
		//{
		//	SDL_Log("step1");
		//}
		//if (touchX < position.getX() + width)
		//{
		//	SDL_Log("step2");
		//}
		//if (touchy > position.getY())
		//{
		//	SDL_Log("step3");
		//}
		//if (touchy < position.getY() + height)
		//{
		//	SDL_Log("step4");
		//}

		if ((touchX > position.getX() && touchX < position.getX() + width) &&
			(touchy > position.getY() && touchy < position.getY() + height))
		{
			SDL_Log("released on target !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
			////released = true;
			//currentframe = MOUSE_OVER;
			//TheGame::Instance()->Setredrawbool(true);
			if (m_callback != 0)
			{
				m_callback();
			}

		}
		//#endif
		//}
		//else
		//{
		//	released = true;
		//	//This is to reset the released in input manager to false
		//	touchX = InputHandler::Instance()->Getreleaseposition()->getX();
		//}
	}



//void MenuButton::clean()
//{
//	StaticObject::clean();
//}
