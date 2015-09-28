#pragma once
#ifndef GAME_OBJECT
#define GAME_OBJECT

#include <string>
using std::string;

class GameObject
{
protected:
	string name;
	// Must be allocated on the heap, the first element stores
	// the size
	float * vertexData;

public:
	GameObject(string name);
	virtual ~GameObject();

	void setVertexData(float * vertexData) { this->vertexData = vertexData; }
	float* getVertexData() { return this->vertexData; }
	string getName() const { return this->name; }

	virtual void update(float elapsedMS) = 0;
	virtual void render() = 0;
};

#endif

