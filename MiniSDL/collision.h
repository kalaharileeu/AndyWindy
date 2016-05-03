//#pragma once
//#include "SDL.h"
//#include "Vector2D.h"
//
//static bool RectRect(SDL_Rect* rect1, SDL_Rect* rect2)
//{
//	// if the bottom of rect1 is less than the top of rect2 - no collision
//	if ((rect1->y + rect1->h) <= rect2->y) { return false; }
//	// if the top of rect1 is more than the bottom of rect2 = no collision
//	if (rect1->y >= (rect2->y + rect2->h)) { return false; }
//	// if the right of rect1 is less than the left of rect2 - no collision
//	if ((rect1->x + rect1->w) <= rect2->x) { return false; }
//	// if the left of rect1 is more than the right of rect2 - no collision
//	if (rect1->x >= (rect2->x + rect2->w)) { return false; }
//	// otherwise there has been a collision
//	return true;
//}
//
//static Vector2D RectRectbounce(SDL_Rect* rect1, SDL_Rect* rect2)
//{
//	Vector2D bouncevect;
//	bouncevect.setX(0);
//	bouncevect.setY(0);
//	// if the bottom of rect1 is more than the top of rect2 - collision
//	if ((rect1->y + rect1->h) >= rect2->y)
//	{ 
//		bouncevect.setY(1);
//	}
//	// if the top of rect1 is more than the bottom of rect2 = collision
//	else if (rect1->y <= (rect2->y + rect2->h))
//	{
//		bouncevect.setY(-1);
//	}
//	// if the right of rect1 is more than the left of rect2 - collision
//	if ((rect1->x + rect1->w) <= rect2->x)
//	{
//		bouncevect.setX(-1);
//	}
//	// if the left of rect1 is less than the right of rect2 - collision
//	else if (rect1->x <= (rect2->x + rect2->w))
//	{ 
//		bouncevect.setX(1);
//	}
//	return bouncevect;
//}
//
//
///*
//Moving objects checks it own collision agains the Walls!!!!!!!!!!
//*/