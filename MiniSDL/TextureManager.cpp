#include "TextureManager.h"
#include "SDL_image.h"
#include "SDL.h"

TextureManager* TextureManager::instance = 0;

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{

	SDL_Surface* tempsurface = IMG_Load(fileName.c_str());
	//Checks
	if (tempsurface == 0)
	{
		std::cout << IMG_GetError();
		return false;
	}
	//Create a texture from temporary surface
	SDL_Texture* sdltexture = SDL_CreateTextureFromSurface(pRenderer, tempsurface);
	SDL_FreeSurface(tempsurface);

	if (sdltexture != 0)
	{
		texturemap[id] = sdltexture;
		return true;
	}

	return false;
}

void TextureManager::draw(std::string id, int x, int y, 
	int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	//TODO: Decide if querying the texture is best, rather than using width height
	//Query the texture to get the height and the width
	int w, h;
	SDL_QueryTexture(texturemap[id], NULL, NULL, &w, &h);//Query

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = w;
	srcRect.h = destRect.h = h;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, texturemap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer, double angle, int alpha, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = width * currentFrame;
	srcRect.y = height * currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_SetTextureAlphaMod(texturemap[id], alpha);
	SDL_RenderCopyEx(pRenderer, texturemap[id], &srcRect, &destRect, angle, 0, flip);
}

void TextureManager::drawTile(std::string id, int margin, int spacing, int x, int y, 
	int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = margin + (spacing + width) * currentFrame;
	srcRect.y = margin + (spacing + height) * currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, texturemap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}


void TextureManager::clearTextureMap()
{
	for (std::map<std::string, SDL_Texture*>::iterator it = texturemap.begin();
	it != texturemap.end(); ++it)
	{
		delete it->second;
		texturemap.erase(it);
	}
}

void TextureManager::clearFromTextureMap(std::string id)
{
	//this is probably not good enough to delete the pointer
	//not using at this stage
	texturemap.erase(id);
}
