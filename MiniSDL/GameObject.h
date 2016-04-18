/*
ABSTRACT base classes
-FORCE the derived classes to have their own implementation of a function
-create a blueprint for objects to follow
-derived classes have a declaration and definition for each of the functions we want to
access through the base class pointer
-ensure correct implementation by making GameObject a abstract base class
-abstract base class cannot be initialized itself
(abstract base class is a class that contains at least one pure virtual function. A
pure virtual function is a function that has no definition and must be implemented in
any derived classes. We can make a function pure virtual by suffixing it with =0.
Derived classes should model the "is a" relationship
*/

#pragma once
#include "Vector2D.h"
#include <memory>//for unique_ptr
#include <string>

class GameObject
{

public:
	// virtual destructor
	virtual ~GameObject() {}
	// load from file - int x, int y, int width, int height, std::string textureID, int numFrames, int callbackID = 0, int animSpeed = 0
	//unique_ptr holds a pointer, and ensures that the pointer is deleted on destruction. unique_ptr objects cannot be copied.
	//virtual void load(std::unique_ptr<LoaderParams> const &pParams) = 0;
	// draw the object
	virtual void draw() = 0;
	// do update stuff
	virtual void update() = 0;
	// remove anything that needs to be deleted
	//virtual void clean() = 0;
	// object has collided, handle accordingly
	virtual void collision() = 0;
	//virtual void bounce(Vector2D v) = 0;
	// get the type of the object
	virtual std::string type() = 0;
	//*********getters/setters**********
	virtual Vector2D Getposition() = 0;
	//need the image width/height for collision
	int Getwidth() { return width; }
	int Getheight() { return height; }
	bool Getcollision() { return boolcollision; }

protected:
	// constructor with default initialisation list
	//only derived classes cna ge to the protected members
	GameObject() : position(0, 0), velocity(0, 0), acceleration(0, 0),
		width(0), height(0), currentrow(0),	currentframe(0), boolcollision(false),
		angle(0), alpha(255)
	{}
	// movement variables
	Vector2D position;
	Vector2D velocity;
	Vector2D acceleration;
	// size variables
	int width;
	int height;
	// animation variables
	int currentrow;
	int currentframe;
	int numframes;
	std::string textureid;
	// common boolean variables
	//bool boolupdating;
	bool boolcollision;
	// rotation
	double angle;
	// blending
	int alpha;
};

