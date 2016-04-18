#include "Game.h"
#include "PlayState.h"

Game* Game::instance = 0;

Game::Game() : mainwindow(0), maindrawer(0),
	boolrunning(false),	statemachine(0)
{
	// add some level files to an array
	//levelfiles.push_back("Content/map1.tmx");
	//m_levelFiles.push_back("assets/map2.tmx");
	// start at this level
	//It can be level 1 or level 2 for now
	//m_currentLevel = 1;
}

Game::~Game()
{
	// we must clean up 
	maindrawer = 0;
	mainwindow = 0;
}

bool Game::init(const char * title, int xpos, int ypos, bool fullscreen)
{
	int flags = 0;
	////store the game width and height
	//gamewidth = GeneralParameters::Instance()->Getxaxmax();
	//gameheight = GeneralParameters::Instance()->Getyaxmax();
	//Screen dimensions
	SDL_Rect gScreenRect = { 0, 0, 320, 240 };
	////Get device display mode
	SDL_DisplayMode displayMode;
	//Doe not have to be sdl_init_everything can just be sdl_init_video or audio or timer
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		//all this have to be done after SDL_INIT
		std::cout << "SDL inti success";
		//init the window
		if (SDL_GetCurrentDisplayMode(0, &displayMode) == 0)
		{
			gScreenRect.w = displayMode.w;
			gScreenRect.h = displayMode.h;
		}
		else
		{
			std::cout << "Error getting the display mode - " << SDL_GetError() << "\n";
			SDL_Log("Error getting the display mode: %s\n", SDL_GetError());
		}
		gamewidth = gScreenRect.w;
		gameheight = gScreenRect.h;

		mainwindow = SDL_CreateWindow
			(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, gScreenRect.w, gScreenRect.h, flags);
		if (mainwindow != 0)//check window init success
		{
					std::cout << "window vreation success\n";
			maindrawer = SDL_CreateRenderer(mainwindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (maindrawer != 0)
			{
				std::cout << "main drawer success/n";
				SDL_SetRenderDrawColor(maindrawer, 129, 191, 212, 5);
			}
			else
			{
				std::cout << "drawer init failed\n";
				return false;//draw init failed
			}
		}
		else
		{
			std::cout << "window init failed\n";
			return false;
		}
	}
	else
	{
		std::cout << "window init failed\n";
		return false;
	}

	//load some sound effect here
	//register some GameObjsect here
	// start the menu state
	statemachine = new StateMachine();
	/*cange ste tells statemachine a new state is coming
	statemachine will call onenter for that state*/
	statemachine->changeState(new PlayState());

	boolrunning = true;
	return true;
}

void Game::draw()
{
	SDL_RenderClear(maindrawer);
	statemachine->draw();
	SDL_RenderPresent(maindrawer);
}

void Game::update()
{
	statemachine->update();
}
//Handle any incoming events
void Game::handleevents()
{
	InputHandler::Instance()->update();
}
/*Clean the:
-InputManager
-StateMachine
-InputManger
*/
void Game::clean()
{
	std::cout << "cleaning game\n";
	TheInputHandler::Instance()->clean();
	statemachine->clean();
	statemachine = 0;
	//delete m_pStateMachine;
	TextureManager::Instance()->clearTextureMap();
	//Close and destroy window
	SDL_DestroyWindow(mainwindow);
	SDL_DestroyRenderer(maindrawer);
	SDL_Quit();
}
