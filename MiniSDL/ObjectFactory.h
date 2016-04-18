/*
Using Distributed Factories
-Distributed Factories can make a generic object factory that will create types.
-Distributed factories allow: dynamically maintain the types of objects we want the factory to create, rather than hard code them into a
function.
-The factory contain std::map that maps a string (the type of our object) to a small
class called Creator whose only purpose is the creation of a specific object.
-register a new type with the factory using a function that takes a string (the ID) and
a Creator class and adds them to the factory's map. 
Start with base class for all the Creator types. Create GameObjectFactory.h and declare this
class at the top of the file.
*/
#pragma once

#include <string>
#include <map>
#include "GameObject.h"
#include <iostream>

class BaseCreator
{
public:
	//return a pointer to a GameObject
	//const:  function is not allowed to change any class members
	virtual GameObject* createGameObject() const = 0;
	virtual ~BaseCreator() {}
};


class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory();
};

