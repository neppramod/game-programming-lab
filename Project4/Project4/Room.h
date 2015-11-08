#pragma once

#ifndef ROOM
#define ROOM

#include "OGL3DCompositeObject.h"

class Cuboid;
class Wall;
class WallWithDoor;

class Room :
	public OGL3DCompositeObject
{

	Wall *floor;
	Wall *ceiling;
	Wall *northWall;
	Wall *southWall;
	Wall *westWall;
	WallWithDoor *eastWall;

	
	float thickness;				// Thickness of wall
	float width, height, depth;

public:
	Room(const string& name, float width=10.0f, float height=10.0f, float depth=10.0f);
	virtual ~Room();
	void setShaderProgram(GLuint shaderProgram);
	void update(float elapsedSeconds);
	void render();
};

#endif