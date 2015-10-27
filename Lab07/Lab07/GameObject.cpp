#include "GameObject.h"
#include "IBehavior.h"

#ifndef NULL
#define NULL 0
#endif

GameObject::GameObject(string name)
{
	this->name = name;
	this->vertexData = NULL;
	this->visible = true;
	this->indexData = NULL;
	this->behavior = NULL;
}

void GameObject::update(float elapsedSeconds)
{
	if (this->behavior) {
		this->behavior->update(this, elapsedSeconds);
	}
}

GameObject::~GameObject()
{
	if (this->vertexData) {
		delete[] this->vertexData;
	}
	if (this->indexData) {
		delete[] this->indexData;
	}
	if (this->behavior) {
		delete this->behavior;
	}
}
