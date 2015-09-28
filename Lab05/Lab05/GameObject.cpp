#include "GameObject.h"

#ifndef NULL
#define NULL 0
#endif

GameObject::GameObject(string name)
{
	this->name = name;
	this->vertexData = NULL;
}

GameObject::~GameObject()
{
	if (this->vertexData) {
		delete[] this->vertexData;
	}
}
