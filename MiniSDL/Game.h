#pragma once

#include "SDL.h"
#include <vector>
#include <iostream>
#include "StateMachine.h"
#include "TextureManager.h"
#include "PlayState.h"
#include "InputHandler.h"
#include "GeneralParameters.h"

class Game
{
public:

	static Game* Instance()
	{
		if (instance == 0)
		{
			instance = new Game();
			return instance;
		}
		return instance;
	}

	bool init(const char* title, int xpos, int ypos, bool fullscreen);
	void draw();
	void update();
	//handle incoming events like key input
	void handleevents();
	void clean();
	//**********get and set**************
	//maindrawer and mainwindow are pointers and this will return them as pointers
	SDL_Renderer* getdrawer() const { return maindrawer; }
	SDL_Window* getWindow() const { return mainwindow; }
	StateMachine* getstatemachine() { return statemachine; }
	int getGameWidth() const { return gamewidth; }
	int getGameHeight() const { return gameheight; }
	//**********bool modifiers********
	bool running() { return boolrunning; }
	void quit() { boolrunning = false; }

private:
	Game();
	~Game();
	StateMachine* statemachine;
	static Game* instance;//static so that no instance of class is needed
	SDL_Window* mainwindow;//This is the only window
	SDL_Renderer* maindrawer;//this is the only drawer
	int gamewidth;//window heirght
	int gameheight;//window width
	//Bool values down here
	bool boolrunning;
	//Stores the level file names ex "Content/map1.tmx"
	std::vector<std::string> levelfiles;
};

typedef Game TheGame;//create an alias that can be used anywhere

