#pragma once

#ifndef WALL
#define WALL

#include "OGL3DCompositeObject.h"

#define DRAW_AXES false

class Cuboid;

class Wall :
	public OGL3DCompositeObject
{
private:
	Cuboid *surface;
	OGLObject *axes;

	float width, depth;
	float thickness;	
	RGBA color;

public:
	Wall(const string& name, float width=10.0f, float depth=10.0f, float thickness=0.1f);
	Wall(const string& name, float width = 10.0f, float depth = 10.0f, float thickness = 0.1f, RGBA color = {1.0f, 0.0f, 0.0f});
	virtual ~Wall();
	void setShaderProgram(GLuint shaderProgram);
	void update(float elapsedSeconds);
	void render();
	void render(OGLReferenceFrame& frame);
};

#endif