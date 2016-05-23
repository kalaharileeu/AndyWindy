#include "Game.h"
#include "PlayState.h"
#include "MainMenuState.h"
#include "Texter.h"
#include "SDL_image.h"

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
				SDL_SetRenderDrawColor(maindrawer, 233, 242, 192, 5);
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
	////Initialize SDL_ttf
	//if (TTF_Init() == -1)
	//{
	//	std::cout << "TTF_Init: %s\n", TTF_GetError();
	//	std::cout << "TTF_init crap out";
	//	return false;
	//}
	//load some sound effect here
	//register some GameObjsect here
	//Register the image with the TextureManager
	TextureManager::Instance()->load("Content/bluesquare2.png", "bluesquare", TheGame::Instance()->getdrawer());
	TextureManager::Instance()->load("Content/redsquare.png", "redsquare", TheGame::Instance()->getdrawer());
	TextureManager::Instance()->load("Content/yellowsquare.png", "yellowsquare", TheGame::Instance()->getdrawer());
	TextureManager::Instance()->load("Content/greensquare.png", "greensquare", TheGame::Instance()->getdrawer());
	TextureManager::Instance()->load("Content/onec.png", "One", TheGame::Instance()->getdrawer());
	TextureManager::Instance()->load("Content/twoc.png", "Two", TheGame::Instance()->getdrawer());
	TextureManager::Instance()->load("Content/threec.png", "Three", TheGame::Instance()->getdrawer());
	TextureManager::Instance()->load("Content/fourc.png", "Four", TheGame::Instance()->getdrawer());
	TextureManager::Instance()->load("Content/fivec.png", "Five", TheGame::Instance()->getdrawer());
	TextureManager::Instance()->load("Content/sixc.png", "Six", TheGame::Instance()->getdrawer());
	TextureManager::Instance()->load("Content/sevenc.png", "Seven", TheGame::Instance()->getdrawer());
	TextureManager::Instance()->load("Content/eightc.png", "Eight", TheGame::Instance()->getdrawer());
	TextureManager::Instance()->load("Content/ninec.png", "Nine", TheGame::Instance()->getdrawer());
	TextureManager::Instance()->load("Content/zeroc.png", "Zero", TheGame::Instance()->getdrawer());
	TextureManager::Instance()->load("Content/exit.png", "exit", TheGame::Instance()->getdrawer());
	TextureManager::Instance()->load("Content/next.png", "next", TheGame::Instance()->getdrawer());
	TextureManager::Instance()->load("Content/star.png", "star", TheGame::Instance()->getdrawer());
	Texter::Instance()->load("one", "one", TheGame::Instance()->getdrawer());
	Texter::Instance()->load("two", "two", TheGame::Instance()->getdrawer());
	Texter::Instance()->load("three", "three", TheGame::Instance()->getdrawer());
	Texter::Instance()->load("four", "four", TheGame::Instance()->getdrawer());
	Texter::Instance()->load("five", "five", TheGame::Instance()->getdrawer());
	Texter::Instance()->load("six", "six", TheGame::Instance()->getdrawer());
	Texter::Instance()->load("seven", "seven", TheGame::Instance()->getdrawer());
	Texter::Instance()->load("eight", "eight", TheGame::Instance()->getdrawer());
	Texter::Instance()->load("nine", "nine", TheGame::Instance()->getdrawer());
	Texter::Instance()->load("ten", "ten", TheGame::Instance()->getdrawer());
	Texter::Instance()->load("Count the blue squares.", "count10", TheGame::Instance()->getdrawer());
	Texter::Instance()->load("From left to right!", "bluecircles", TheGame::Instance()->getdrawer());
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
	Texter::Instance()->destroy();
	std::cout << "cleaning game\n";
	TheInputHandler::Instance()->destroy();
	//clean state machine
	statemachine->clean();
	delete statemachine;
	statemachine = nullptr;
	//Destroy texturemanager
	TextureManager::Instance()->destroy();
	GP::Instance()->destroy();
	//Close and destroy window
	SDL_DestroyWindow(mainwindow);
	SDL_DestroyRenderer(maindrawer);
	//TTF_Quit();//TFF_quit in texter
	IMG_Quit();
	SDL_Quit();
}
