#include "InputHandler.h"
#include <iostream>

InputHandler* InputHandler::s_pInstance = 0;

InputHandler::InputHandler() : m_keystates(nullptr), m_bJoysticksInitialised(false), 
m_mousePosition(new Vector2D(0, 0)), 
MouseMoved(false), 
touchfingerposition(new Vector2D(0, 0)),
liftfingerposition(new Vector2D(0, 0)),
fingerdragpos(new Vector2D(0, 0)),
touched(false)
{
	happy = "";
	// create button states for the mouse
	for (int i = 0; i < 3; i++)
	{
		m_mouseButtonStates.push_back(false);
	}
}

InputHandler::~InputHandler()
{
	std::cout << "inputhandler destroyed!!!!!!!!!!!!!" << std::endl;
	// delete anything we created dynamically
	if (m_keystates != nullptr)
	{
		delete m_keystates;
	}
	delete m_mousePosition;
	delete touchfingerposition;
	delete liftfingerposition;
	delete fingerdragpos;
	// clear our arrays
	//m_joystickValues.clear();
	//m_joysticks.clear();
	//m_buttonStates.clear();
	m_mouseButtonStates.clear();
}

void InputHandler::clean()
{
	reset();
	//close the joysticks we opened
	//if (m_bJoysticksInitialised)
	//{
	//	for (unsigned int i = 0; i < SDL_NumJoysticks(); i++)
	//	{
	//		SDL_JoystickClose(m_joysticks[i]);
	//	}
	//}
}

//void InputHandler::initialiseJoysticks()
//{
//	// if we haven't already initialised the joystick subystem, we will do it here
//	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
//	{
//		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
//	}
//
//	// get the number of joysticks, skip init if there aren't any
//	if (SDL_NumJoysticks() > 0)
//	{
//		for (int i = 0; i < SDL_NumJoysticks(); i++)
//		{
//			// create a new joystick
//			SDL_Joystick* joy = SDL_JoystickOpen(i);
//
//			// if the joystick opened correctly we need to populate our arrays
//			if (SDL_JoystickOpen(i))
//			{
//				// push back into the array to be closed later
//				m_joysticks.push_back(joy);
//
//				// create a pair of values for the axes, a vector for each stick
//				m_joystickValues.push_back(std::make_pair(new Vector2D(0, 0), new Vector2D(0, 0)));
//
//				// create an array to hold the button values
//				std::vector<bool> tempButtons;
//
//				// fill the array with a false value for each button
//				for (int j = 0; j < SDL_JoystickNumButtons(joy); j++)
//				{
//					tempButtons.push_back(false);
//				}
//				// push the button array into the button state array
//				m_buttonStates.push_back(tempButtons);
//			}
//			else
//			{
//				// if there was an error initialising a joystick we want to know about it
//				std::cout << SDL_GetError();
//			}
//		}
//
//		// enable joystick events
//		SDL_JoystickEventState(SDL_ENABLE);
//		m_bJoysticksInitialised = true;
//
//		std::cout << "Initialised " << m_joysticks.size() << " joystick(s)";
//	}
//	else
//	{
//		m_bJoysticksInitialised = false;
//	}
//}

void InputHandler::reset()
{
	m_mouseButtonStates[LEFT] = false;
	m_mouseButtonStates[RIGHT] = false;
	m_mouseButtonStates[MIDDLE] = false;
	released = false;
	touched = false;
	MouseMoved = false;
	touchfingerposition->setX(0);
	liftfingerposition->setX(0);
	fingerdragpos->setX(0);
}

bool InputHandler::isKeyDown(SDL_Scancode key) const
{
	if (m_keystates != 0)
	{
		if (m_keystates[key] == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

//int InputHandler::getAxisX(int joy, int stick) const
//{
//	if (m_joystickValues.size() > 0)
//	{
//		if (stick == 1)
//		{
//			return m_joystickValues[joy].first->getX();
//		}
//		else if (stick == 2)
//		{
//			return m_joystickValues[joy].second->getX();
//		}
//	}
//	return 0;
//}
//
//int InputHandler::getAxisY(int joy, int stick) const
//{
//	if (m_joystickValues.size() > 0)
//	{
//		if (stick == 1)
//		{
//			return m_joystickValues[joy].first->getY();
//		}
//		else if (stick == 2)
//		{
//			return m_joystickValues[joy].second->getY();
//		}
//	}
//	return 0;
//}
//
//bool InputHandler::getButtonState(int joy, int buttonNumber) const
//{
//	return m_buttonStates[joy][buttonNumber];
//}

bool InputHandler::getMouseButtonState(int buttonNumber) const
{
	return m_mouseButtonStates[buttonNumber];
}

Vector2D* InputHandler::getMousePosition() const
{
	return m_mousePosition;
}

Vector2D* InputHandler::Gettouchposition()
{
	//touched = false;
	return touchfingerposition;
}

Vector2D* InputHandler::Getreleaseposition()
{
	//released = false;
	return liftfingerposition;
}

void InputHandler::update()
{
	int i = 0;
	//unique event printing
	if (oldevent.type != event.type)
	{
		i = static_cast<int>(event.type);
		std::string s = happystring(i);
		//SDL_Log(".");
		//SDL_Log("%s", s.c_str());
		//SDL_Log(".");
		//std::cout << "." << i << ".";
	}
	oldevent = event;
	////end unique event printing
	//if (i == 767)
	//{
	//	SDL_Log("Here trying to quit!!!!!????????????????????????");
	//	i = 0;
	//	//TheGame::Instance()->quit();
	//	//return;
	//}

	if (event.type != SDL_MOUSEMOTION)
	{
		MouseMoved = false;
	}

	if (event.type != SDL_FINGERDOWN)
	{
		touched = false;
	}

	if (event.type != SDL_FINGERUP)
	{
		released = false;
	}

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			TheGame::Instance()->quit();
			break;
#if !defined( ANDROID ) 
		//case SDL_JOYAXISMOTION:
		//	onJoystickAxisMove(event);
		//	break;

		//case SDL_JOYBUTTONDOWN:
		//	onJoystickButtonDown(event);
		//	break;

		//case SDL_JOYBUTTONUP:
		//	onJoystickButtonUp(event);
		//	break;

		case SDL_MOUSEMOTION:
			MouseMoved = true;
			onMouseMove(event);
			break;

		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonDown(event);
			break;

		case SDL_MOUSEBUTTONUP:
			onMouseButtonUp(event);
			break;

		case SDL_KEYDOWN:
			onKeyDown();
			break;

		case SDL_KEYUP:
			onKeyUp();
			break;
#endif
			//Touch events
		case SDL_FINGERDOWN:
			onTouchFingerDown(event);
			break;
			//Touch events
		case SDL_FINGERUP:
			onTouchFingerUp(event);
			break;
			//Touch events
		case SDL_FINGERMOTION:
			onTouchFingerMotion();
			break;

		default:
			break;
		}
	}
}

void InputHandler::onKeyDown()
{
	m_keystates = SDL_GetKeyboardState(0);
}

void InputHandler::onKeyUp()
{
	m_keystates = SDL_GetKeyboardState(0);
}
//handle touch events
void InputHandler::onTouchFingerDown(SDL_Event &event)
{
	touched = true;
	touchfingerposition->setX(event.tfinger.x * Game::Instance()->getGameWidth());
	touchfingerposition->setY(event.tfinger.y * Game::Instance()->getGameHeight());
}
//handle touch events
void InputHandler::onTouchFingerUp(SDL_Event &event)
{
	released = true;
	fingermotion = false;
	liftfingerposition->setX(event.tfinger.x * Game::Instance()->getGameWidth());
	liftfingerposition->setY(event.tfinger.y * Game::Instance()->getGameHeight());
}
//handle touch events
void InputHandler::onTouchFingerMotion()
{
	fingermotion = true;
	fingerdragpos->setX(event.tfinger.x * Game::Instance()->getGameWidth());
	fingerdragpos->setY(event.tfinger.y * Game::Instance()->getGameHeight());
}

void InputHandler::onMouseMove(SDL_Event &event)
{
	m_mousePosition->setX(event.motion.x);
	m_mousePosition->setY(event.motion.y);
}

void InputHandler::onMouseButtonDown(SDL_Event &event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		m_mouseButtonStates[LEFT] = true;
	}

	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		m_mouseButtonStates[MIDDLE] = true;
	}

	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		m_mouseButtonStates[RIGHT] = true;
	}
}

void InputHandler::onMouseButtonUp(SDL_Event &event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		m_mouseButtonStates[LEFT] = false;
	}

	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		m_mouseButtonStates[MIDDLE] = false;
	}

	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		m_mouseButtonStates[RIGHT] = false;
	}
}

//void InputHandler::onJoystickAxisMove(SDL_Event &event)
//{
//	int whichOne = event.jaxis.which;
//
//	// left stick move left or right
//	if (event.jaxis.axis == 0)
//	{
//		if (event.jaxis.value > m_joystickDeadZone)
//		{
//			m_joystickValues[whichOne].first->setX(1);
//		}
//		else if (event.jaxis.value < -m_joystickDeadZone)
//		{
//			m_joystickValues[whichOne].first->setX(-1);
//		}
//		else
//		{
//			m_joystickValues[whichOne].first->setX(0);
//		}
//	}
//
//	// left stick move up or down
//	if (event.jaxis.axis == 1)
//	{
//		if (event.jaxis.value > m_joystickDeadZone)
//		{
//			m_joystickValues[whichOne].first->setY(1);
//		}
//		else if (event.jaxis.value < -m_joystickDeadZone)
//		{
//			m_joystickValues[whichOne].first->setY(-1);
//		}
//		else
//		{
//			m_joystickValues[whichOne].first->setY(0);
//		}
//	}
//
//	// right stick move left or right
//	if (event.jaxis.axis == 3)
//	{
//		if (event.jaxis.value > m_joystickDeadZone)
//		{
//			m_joystickValues[whichOne].second->setX(1);
//		}
//		else if (event.jaxis.value < -m_joystickDeadZone)
//		{
//			m_joystickValues[whichOne].second->setX(-1);
//		}
//		else
//		{
//			m_joystickValues[whichOne].second->setX(0);
//		}
//	}
//
//	// right stick move up or down
//	if (event.jaxis.axis == 4)
//	{
//		if (event.jaxis.value > m_joystickDeadZone)
//		{
//			m_joystickValues[whichOne].second->setY(1);
//		}
//		else if (event.jaxis.value < -m_joystickDeadZone)
//		{
//			m_joystickValues[whichOne].second->setY(-1);
//		}
//		else
//		{
//			m_joystickValues[whichOne].second->setY(0);
//		}
//	}
//}
//
//void InputHandler::onJoystickButtonDown(SDL_Event &event)
//{
//	int whichOne = event.jaxis.which;
//
//	m_buttonStates[whichOne][event.jbutton.button] = true;
//}
//
//void InputHandler::onJoystickButtonUp(SDL_Event &event)
//{
//	int whichOne = event.jaxis.which;
//
//	m_buttonStates[whichOne][event.jbutton.button] = false;
//}

std::string InputHandler::happystring(int x)
{
	std::string s = ".";
	if (x % 10 == 0) { s += "0"; }
	else if (x % 10 == 1) { s += "1"; }
	else if (x % 10 == 2) { s += "2"; }
	else if (x % 10 == 3) { s += "3"; }
	else if (x % 10 == 4) { s += "4"; }
	else if (x % 10 == 5) { s += "5"; }
	else if (x % 10 == 6) { s += "6"; }
	else if (x % 10 == 7) { s += "7"; }
	else if (x % 10 == 8) { s += "6"; }
	else if (x % 10 == 9) { s += "7"; }
	x /= 10;
	if (x == 0) { return s + "."; }
	if (x % 10 == 0) { s += "0"; }
	else if (x % 10 == 1) { s += "1"; }
	else if (x % 10 == 2) { s += "2"; }
	else if (x % 10 == 3) { s += "3"; }
	else if (x % 10 == 4) { s += "4"; }
	else if (x % 10 == 5) { s += "5"; }
	else if (x % 10 == 6) { s += "6"; }
	else if (x % 10 == 7) { s += "7"; }
	else if (x % 10 == 8) { s += "6"; }
	else if (x % 10 == 9) { s += "7"; }
	x /= 10;
	if (x == 0) { return s + "."; }
	if (x % 10 == 0) { s += "0"; }
	else if (x % 10 == 1) { s += "1"; }
	else if (x % 10 == 2) { s += "2"; }
	else if (x % 10 == 3) { s += "3"; }
	else if (x % 10 == 4) { s += "4"; }
	else if (x % 10 == 5) { s += "5"; }
	else if (x % 10 == 6) { s += "6"; }
	else if (x % 10 == 7) { s += "7"; }
	else if (x % 10 == 8) { s += "6"; }
	else if (x % 10 == 9) { s += "7"; }
	x /= 10;
	if (x == 0) { return s + "."; }
	if (x % 10 == 0) { s += "0"; }
	else if (x % 10 == 1) { s += "1"; }
	else if (x % 10 == 2) { s += "2"; }
	else if (x % 10 == 3) { s += "3"; }
	else if (x % 10 == 4) { s += "4"; }
	else if (x % 10 == 5) { s += "5"; }
	else if (x % 10 == 6) { s += "6"; }
	else if (x % 10 == 7) { s += "7"; }
	else if (x % 10 == 8) { s += "6"; }
	else if (x % 10 == 9) { s += "7"; }
	x /= 10;
	if (x == 0) { return s + "."; }
	if (x % 10 == 0) { s += "0"; }
	else if (x % 10 == 1) { s += "1"; }
	else if (x % 10 == 2) { s += "2"; }
	else if (x % 10 == 3) { s += "3"; }
	else if (x % 10 == 4) { s += "4"; }
	else if (x % 10 == 5) { s += "5"; }
	else if (x % 10 == 6) { s += "6"; }
	else if (x % 10 == 7) { s += "7"; }
	else if (x % 10 == 8) { s += "6"; }
	else if (x % 10 == 9) { s += "7"; }
	x /= 10;
	if (x == 0) { return s + "."; }
	if (x % 10 == 0) { s += "0"; }
	else if (x % 10 == 1) { s += "1"; }
	else if (x % 10 == 2) { s += "2"; }
	else if (x % 10 == 3) { s += "3"; }
	else if (x % 10 == 4) { s += "4"; }
	else if (x % 10 == 5) { s += "5"; }
	else if (x % 10 == 6) { s += "6"; }
	else if (x % 10 == 7) { s += "7"; }
	else if (x % 10 == 8) { s += "6"; }
	else if (x % 10 == 9) { s += "7"; }
	return s;
}
