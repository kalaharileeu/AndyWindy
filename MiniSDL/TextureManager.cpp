#include "TextureManager.h"
#include "SDL_image.h"
#include "SDL.h"

TextureManager* TextureManager::instance = 0;

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
	//if(texturemap.find(id))
	SDL_Surface* tempsurface = IMG_Load(fileName.c_str());
	//Checks. change 0 to nullptr
	if (tempsurface == nullptr)
	{
		std::cout << IMG_GetError();
		return false;
	}
	//Create a texture from temporary surface
	SDL_Texture* sdltexture = SDL_CreateTextureFromSurface(pRenderer, tempsurface);
	SDL_FreeSurface(tempsurface);
	//Change 0 to nullptr
	if (sdltexture != nullptr)
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
	srcRect.w = w;
	srcRect.h = h;
	destRect.w = width;//if zoomed then zoomed value
	destRect.h = height;//if zommed then zoomed value
	destRect.x = x;//if zommed then zoomed value
	destRect.y = y;//if zommed then zoomed value

	SDL_RenderCopyEx(pRenderer, texturemap[id], &srcRect, &destRect, 0, 0, flip);
}
//zoom in out
void TextureManager::drawzoom(std::string id, int x, int y,
	int width, int height, SDL_Renderer* pRenderer, float zoom)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	//TODO: Decide if querying the texture is best, rather than using width height
	//Query the texture to get the height and the width
	int w, h;
	SDL_QueryTexture(texturemap[id], NULL, NULL, &w, &h);//Query

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = w;
	srcRect.h = h;
	//destination rect need to be zoomed
	destRect.w = w * zoom;
	destRect.h = h * zoom;
	destRect.x = x - ((w * zoom)/2);
	destRect.y = y - ((h * zoom)/2);

	SDL_RenderCopyEx(pRenderer, texturemap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height,
	int currentRow, int currentFrame, SDL_Renderer *pRenderer, double angle, int alpha, SDL_RendererFlip flip)
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
//find the texture dinesions and returns them in a Vector2D
Vector2D TextureManager::GetTextureDimensions(std::string id)
{
	Vector2D dimensions(0, 0);
	if(texturemap.find(id) != texturemap.end())
	{
		int w, h = 0;
		SDL_QueryTexture(texturemap[id], NULL, NULL, &w, &h);//Query
		dimensions.setX(w);
		dimensions.setY(h);
	}
	else
	{
		std::cout << "texture not found in the map" << id << std::endl;
	}
	return dimensions;
}


void TextureManager::clearTextureMap()
{
	if (!texturemap.empty())
	{
		for (std::map<std::string, SDL_Texture*>::iterator it = texturemap.begin(); it != texturemap.end(); it++)
		{
			SDL_DestroyTexture(it->second);
			it->second = nullptr;
			//texturemap.erase(it);
		}
		texturemap.clear();
	}
}

void TextureManager::clearFromTextureMap(std::string id)
{

	if (texturemap.find(id) != texturemap.end())
	{
		SDL_DestroyTexture(texturemap[id]);
		texturemap[id] = nullptr;
		texturemap.erase(id);
	}
	else
	{
		std::cout << "texture not found to delete" << id << std::endl;
	}
}
