#pragma once
#include "Game.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include <iostream>

class Texter
{
public:
	Texter() {}
	Texter(SDL_Renderer* Drawer)
	{
		int v = TTF_Init();
		if (v == -1) 
		{
			printf("TTF_Init: %s\n", TTF_GetError());
		}
		else
		{
			//this opens a font style and sets a size
			TTF_Font* Sans = TTF_OpenFont("Content/Sans.ttf", 72);
			if (Sans == nullptr)
			{
				std::cout << "TTF_font issue - " << SDL_GetError() << "\n";
			}
			Message_rect.x = 0;  //controls the rect's x coordinate 
			Message_rect.y = 0; // controls the rect's y coordinte
			Message_rect.w = 1000; // controls the width of the rect
			Message_rect.h = 100; // controls the height of the rect
			SDL_Surface* tempsurface = nullptr;
			// as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
			tempsurface = TTF_RenderText_Solid(Sans, "put your text here !!!!!!!!!!!", Black);
			if (tempsurface == nullptr)
			{
				std::cout << "Error TTF_rendtext issue - " << SDL_GetError() << "\n";
			}
			//now you can convert it into a texture
			SDL_Texture* message = SDL_CreateTextureFromSurface(Drawer, tempsurface);
			//free he surface
			SDL_FreeSurface(tempsurface);
			tempsurface = nullptr;
			//Do the business render
			SDL_RenderCopy(Drawer, message, NULL, &Message_rect);
			//DrawText(Drawer);
		}
	}

	~Texter()
	{

	}

	void clear()
	{
		if (message != nullptr)
		{
			SDL_DestroyTexture(message);
			message = nullptr;
		}
		//Sans is the font: TTF_Font
		if(Sans != nullptr)
		{
			//Free global font
			TTF_CloseFont(Sans);
			Sans = nullptr;
		}
		TTF_Quit();
	}

private:
	//this opens a font style and sets a size
	TTF_Font* Sans = nullptr;
	SDL_Texture* message = nullptr;
	SDL_Color Black = { 0, 0, 0 };
	// as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	SDL_Rect Message_rect; //create a rect
};

//static void WriteText(SDL_Renderer* Drawer, SDL_Surface* Textsurface)
//{
//
//	TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24); //this opens a font style and sets a size
//
//	SDL_Color Black = { 0, 0, 0 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
//	// as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
//	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "put your text here", Black);
//
//	SDL_Texture* Message = SDL_CreateTextureFromSurface(Drawer, surfaceMessage); //now you can convert it into a texture
//
//	SDL_Rect Message_rect; //create a rect
//	Message_rect.x = 0;  //controls the rect's x coordinate 
//	Message_rect.y = 0; // controls the rect's y coordinte
//	Message_rect.w = 100; // controls the width of the rect
//	Message_rect.h = 100; // controls the height of the rect
//
////Mind you that (0,0) is on the top left of the window/screen, 
////think a rect as the text's box, that way it would be very simple to understance
////Now since it's a texture, you have to put RenderCopy in your game loop area,
////the area where the whole code executes
////you put the renderer's name first, the Message, the crop size(you can ignore this if you 
////don't want to dabble with cropping), 
////and the rect which is the size and coordinate of your texture
//
//	SDL_RenderCopy(Drawer, Message, NULL, &Message_rect);
//}

/*Cleaning up down here
void close()
{
	//Free loaded images
	gTextTexture.free();

	//Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;

	//Destroy window    
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
*/