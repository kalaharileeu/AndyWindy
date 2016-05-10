#include "Game.h"
#include "PlayState.h"
#include "MainMenuState.h"

Game* Game::instance = 0;

Game::Game() : mainwindow(0), maindrawer(0),
boolrunning(false), statemachine(0)
{
	redraw = true;
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
	//Screen dimensions
	SDL_Rect gScreenRect = { 0, 0, 1280, 720 };
	////Get device display mode
	SDL_DisplayMode displayMode;
	//Doe not have to be sdl_init_everything can just be sdl_init_video or audio or timer
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		//init the window
		if (SDL_GetCurrentDisplayMode(0, &displayMode) == 0)
		{
#if defined( ANDROID )
			gScreenRect.w = displayMode.w;
			gScreenRect.h = displayMode.h;
#endif
		}
		else
		{
			std::cout << "Error getting the display mode - " << SDL_GetError() << "\n";
			SDL_Log("Error getting the display mode: %s\n", SDL_GetError());
		}

		gamewidth = gScreenRect.w;
		gameheight = gScreenRect.h;
		//added the below to try and solve the color issue on my galaxy S3
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);

		mainwindow = SDL_CreateWindow
			(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, gScreenRect.w, gScreenRect.h, flags);
		if (mainwindow != nullptr)//check window init success
		{
			std::cout << "window vreation success\n";
			maindrawer = SDL_CreateRenderer(mainwindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (maindrawer != nullptr)
			{
				std::cout << "main drawer success/n";
				SDL_SetRenderDrawColor(maindrawer, 255, 255, 255, 5);
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
	//Register the image with the TextureManager
	TextureManager::Instance()->load("Content/bluesquare.png", "bluesquare", TheGame::Instance()->getdrawer());
	TextureManager::Instance()->load("Content/redsquare.png", "redsquare", TheGame::Instance()->getdrawer());
	TextureManager::Instance()->load("Content/yellowsquare.png", "yellowsquare", TheGame::Instance()->getdrawer());
	TextureManager::Instance()->load("Content/bigone.png", "One", TheGame::Instance()->getdrawer());
	TextureManager::Instance()->load("Content/bigtwo.png", "Two", TheGame::Instance()->getdrawer());
	TextureManager::Instance()->load("Content/bigthree.png", "Three", TheGame::Instance()->getdrawer());
	TextureManager::Instance()->load("Content/bigfour.png", "Four", TheGame::Instance()->getdrawer());
	TextureManager::Instance()->load("Content/bigfive.png", "Five", TheGame::Instance()->getdrawer());
	TextureManager::Instance()->load("Content/bigsix.png", "Six", TheGame::Instance()->getdrawer());
	TextureManager::Instance()->load("Content/bigseven.png", "Seven", TheGame::Instance()->getdrawer());
	TextureManager::Instance()->load("Content/bigeight.png", "Eight", TheGame::Instance()->getdrawer());
	TextureManager::Instance()->load("Content/bignine.png", "Nine", TheGame::Instance()->getdrawer());
	TextureManager::Instance()->load("Content/bigzero.png", "Zero", TheGame::Instance()->getdrawer());
	TextureManager::Instance()->load("Content/exit.png", "exit", TheGame::Instance()->getdrawer());
	/*change the state tells statemachine a new state is coming
	statemachine will call on enter for that state*/
	//Can start immediately with new Playstate(), I want to start with menustate
	// start the menu state
	statemachine = new StateMachine();
	statemachine->changeState(new MainMenuState());
	//statemachine->changeState(new PlayState());
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
	statemachine->clean();//Does nothing at this stage
	statemachine = 0;
	//delete m_pStateMachine;
	TextureManager::Instance()->clearTextureMap();
	//Close and destroy window
	SDL_DestroyWindow(mainwindow);
	SDL_DestroyRenderer(maindrawer);
	//TTF_Quit();
	//IMG_Quit();
	SDL_Quit();

}
