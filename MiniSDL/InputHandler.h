#pragma once
#include "SDL.h"
#include <vector>
#include "Game.h"
#include "Vector2D.h"

#include <iostream>
#include <vector>

#include "SDL.h"
#include "Vector2D.h"

enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputHandler
{
public:
	static InputHandler* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new InputHandler();
		}

		return s_pInstance;
	}


	static void destroy()
	{
		delete s_pInstance;
		s_pInstance = nullptr;
	}

	~InputHandler();

	// init joysticks
	//void initialiseJoysticks();
	//bool joysticksInitialised() const { return m_bJoysticksInitialised; }
	void reset();

	// update and clean the input handler
	void update();
	void clean();
	// keyboard events
	bool isKeyDown(SDL_Scancode key) const;
	//// joystick events
	//int getAxisX(int joy, int stick) const;
	//int getAxisY(int joy, int stick) const;
	//bool getButtonState(int joy, int buttonNumber) const;
	// mouse events
	bool getMouseButtonState(int buttonNumber) const;
	Vector2D* getMousePosition() const;
	bool getMouseMoveState() { return MouseMoved; }
	//Gets the touch position 
	Vector2D* Gettouchposition();
	Vector2D* Getreleaseposition();
	Vector2D* Getfingerdragpos() { return fingerdragpos; }
	bool Gettouchstate() { return touched; }
	bool Getreleasestate() { return released; }
	bool Getfingmotionstate() { return fingermotion; }
	std::string happystring(int x);

private:
	std::string happy;
	InputHandler();
	SDL_Event event;
	SDL_Event oldevent;

	InputHandler(const InputHandler&);
	//InputHandler& operator=(const InputHandler&);
	// private functions to handle different event types
	// handle keyboard events
	void onKeyDown();
	void onKeyUp();
	//handle touch events
	void onTouchFingerDown(SDL_Event &event);
	void onTouchFingerUp(SDL_Event &event);
	void onTouchFingerMotion();
	// handle mouse events
	void onMouseMove(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);
	//// handle joysticks events
	//void onJoystickAxisMove(SDL_Event& event);
	//void onJoystickButtonDown(SDL_Event& event);
	//void onJoystickButtonUp(SDL_Event& event);
	// member variables
	// keyboard specific
	const Uint8* m_keystates;

	// joystick specific
	//std::vector<std::pair<Vector2D*, Vector2D*> > m_joystickValues;
	//std::vector<SDL_Joystick*> m_joysticks;
	//std::vector<std::vector<bool> > m_buttonStates;
	bool m_bJoysticksInitialised;
	//static const int m_joystickDeadZone = 10000;

	// mouse specific
	std::vector<bool> m_mouseButtonStates;
	Vector2D* m_mousePosition;
	Vector2D* fingerdragpos;
	Vector2D* touchfingerposition;
	Vector2D* liftfingerposition;
	bool MouseMoved;
	bool touched;
	bool released;
	bool fingermotion;

	// singleton
	static InputHandler* s_pInstance;
};
typedef InputHandler TheInputHandler;