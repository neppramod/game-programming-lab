#pragma once
#include "OGL3DCompositeObject.h"

#ifndef WALL_WITH_DOOR
#define WALL_WITH_DOOR

class Cuboid;

class WallWithDoor :
	public OGL3DCompositeObject
{
private:
	// Use three surfaces to create door 
	Cuboid *eastWallTop;
	Cuboid *eastWallBottomLeft;
	Cuboid *eastWallBottomRight;
	OGLObject *axes;

	//  -------
	//  -------
	//  --| |--

	float thickness;				// Thickness of wall
	float width, height, depth;
	RGBA color;

public:
	WallWithDoor(string &name, float width=10.0f, float height=10.0f, float depth=10.0f);
	WallWithDoor(const string& name, float width = 10.0f, float depth = 10.0f, float thickness = 0.1f, RGBA color = { 1.0f, 0.0f, 0.0f });
	virtual ~WallWithDoor();
	void setShaderProgram(GLuint shaderProgram);
	void update(float elapsedSeconds);
	void render();
	void render(OGLReferenceFrame &frame);
};

#endif