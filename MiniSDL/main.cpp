#include<SDL.h>
#include<iostream>
#include "Game.h"

#if !defined( ANDROID )
#  undef main
#endif
//#include "GeneralParameters.h"
/*
The game starts here here
The main set the the pace for the program, its purpose is to
set a contimuous while loop running at a constant pace, it
forms the main clock for the game. Start point and end point
While the Game instance running is true the 
*/
Game* game = 0;
///variable to create the fixed frames per second
const int FPS = 30; //Frames per second
const int DELAY_TIME = 1000 / FPS;//

int main(int argc, char* argv[])
{
	Uint32 frameStart, frameTime;
	//    AllocConsole();//To view cout remove
	//    freopen("CON", "w", stdout);//To view cout remove
	std::cout << "game init attempt...\n";
	//Make fullscreen true here for Android  to cover the whole surface
	if (TheGame::Instance()->init("WrapperIntruder", 100, 100, false))
	{
		std::cout << "game init success!\n";
		//Move draw out of the main loop and just use redraw
		while (TheGame::Instance()->running())
		{
			//SDL_GetTicks which returns the amount of milliseconds since we called SDL_Init
			frameStart = SDL_GetTicks();//get the time at the start of our loop

			TheGame::Instance()->handleevents();
			TheGame::Instance()->update();
			//Check is a redrw is neccesary. Redrw will be trigger byobject updates
			if (TheGame::Instance()->Getredrawbool())
			{
				TheGame::Instance()->draw();
				TheGame::Instance()->Setredrawbool(false);
			}
			frameTime = SDL_GetTicks() - frameStart;//game loop finnished and calculate how long it took to run
			//If less than the time we want a frame to take, we call SDL_Delay
			if (frameTime < DELAY_TIME)
			{
				SDL_Delay((int)(DELAY_TIME - frameTime));
			}
		}
	}
	else
	{
		std::cout << "game init failure - " << SDL_GetError() << "\n";
		return -1;
	}
	std::cout << "game closing...\n";
	//When it is all done clean up.
	TheGame::Instance()->clean();
	return 0;

}
