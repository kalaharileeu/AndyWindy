#pragma once
//#include "Game.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include <iostream>
#include "Vector2D.h"
#include <map>
//Singleton
class Texter
{
public:
	static Texter* Instance()
	{
		if (instance == 0)
		{
			instance = new Texter();
			return instance;
		}
		return instance;
	}

	~Texter()
	{
		for (std::map<std::string, SDL_Texture*>::iterator
			it = texturemap.begin(); it != texturemap.end(); it++)
		{
			SDL_DestroyTexture(it->second);
			it->second = nullptr;
		}
		texturemap.clear();
		clearfont();
		TTF_Quit();
	}

	static void destroy()
	{
		delete instance;
		instance = nullptr;
	}


	void loadfont()
	{
		Sans = TTF_OpenFont("Content/Sans.ttf", 12);
		if (Sans == nullptr)
		{
			std::cout << "TTF_font issue - " << SDL_GetError() << "\n";
		}
	}


	bool load(std::string text, std::string id, SDL_Renderer* drawer)
	{
		if (Sans != nullptr)
		{
			SDL_Surface* tempsurface = TTF_RenderText_Solid(Sans, text.c_str(), Black);
			//Checks. change 0 to nullptr
			if (tempsurface == nullptr)
			{
				std::cout << TTF_GetError();
				return false;
			}
			//Create a texture from temporary surface
			SDL_Texture* sdltexture = SDL_CreateTextureFromSurface(drawer, tempsurface);
			//free he surface
			SDL_FreeSurface(tempsurface);
			tempsurface = nullptr;
			//Change 0 to nullptr
			if (sdltexture != nullptr)
			{
				texturemap[id] = sdltexture;
				return true;
			}
		}
		else
		{
			std::cout << "sans is a nullptr, you need to load font" << std::endl;
			return false;
		}
		std::cout << "issues with sans" << std::endl;
		return false;
	}

	void draw(std::string id, int x, int y, SDL_Renderer* drawer)
	{
		//SDL_Rect srcRect;
		SDL_Rect destRect;
		//TODO: Decide if querying the texture is best, rather than using width height
		//Query the texture to get the height and the width
		int w, h;
		SDL_QueryTexture(texturemap[id], NULL, NULL, &w, &h);//Query
		destRect.w = w;
		destRect.h = h;
		destRect.x = x;
		destRect.y = y;
		//Do the business render
		//SDL_RenderCopy(drawer, message, NULL, &Message_rect);
		SDL_RenderCopy(drawer, texturemap[id], NULL, &destRect);
	}

	//find the texture dinesions and returns them in a Vector2D
	Vector2D GetTextureDimensions(std::string id)
	{
		Vector2D dimensions(0, 0);
		if (texturemap.find(id) != texturemap.end())
		{
			int w, h = 0;
			SDL_QueryTexture(texturemap[id], NULL, NULL, &w, &h);//Query
			dimensions.setX(w);
			dimensions.setY(h);
		}
		else
		{
			std::cout << "texture not found in the map" << std::endl;
		}
		return dimensions;
	}

private:
	Texter()
	{
		//Initialize SDL_ttf
		if (TTF_Init() == -1)
		{
			std::cout << "TTF_Init: %s\n", TTF_GetError();
		}
		Sans = nullptr;
		Sans = TTF_OpenFont("Content/Sans.ttf", 40);
		if (Sans == nullptr)
		{
			std::cout << "TTF_font issue - " << SDL_GetError() << "\n";
		}
	}

	void clearfont()
	{
		if (Sans != nullptr)
		{
			//Free global font
			TTF_CloseFont(Sans);
			Sans = nullptr;
		}
	}
	//this opens a font style and sets a size
	TTF_Font* Sans;
	SDL_Color Black = { 0, 0, 0 };
	// as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	std::map<std::string, SDL_Texture*> texturemap;
	//SDL_Rect Message_rect; //create a rect
	static Texter* instance;
};



