/*
Features of the texture manager:
-Holds a texture map to store textures
-Draws single images and draws animation images, if goven
-Draws a tile from a Tile sheet
*/
#pragma once
#include <iostream>
#include <string>
#include <map>
#include "SDL.h"
#include "Vector2D.h"

class TextureManager
{
public:

	static TextureManager* Instance()
	{
		if (instance == 0)
		{
			instance = new TextureManager();
			return instance;
		}
		return instance;
	}

	~TextureManager()
	{
		clearTextureMap(); 
	}

	static void destroy()
	{
		delete instance;
		instance = nullptr;
	}

	bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

	void clearTextureMap();
	void clearFromTextureMap(std::string id);

	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawzoom(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, float zoom);
	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame,
		SDL_Renderer* pRenderer, double angle, int alpha, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawTile(std::string id, int margin, int spacing, int x, int y,
		int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer);
	Vector2D GetTextureDimensions(std::string id);
	//int GetTextureWidth(std::string id) const;
	std::map<std::string, SDL_Texture*> getTextureMap() { return texturemap; }

private:
	TextureManager() {}

	std::map<std::string, SDL_Texture*> texturemap;
	static TextureManager* instance;
};

typedef TextureManager TheTextureManager;