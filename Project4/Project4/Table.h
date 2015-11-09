#pragma once

#ifndef TABLE
#define TABLE

#include "OGL3DCompositeObject.h"

class Cuboid;

class Table :
	public OGL3DCompositeObject
{
protected:
	Cuboid *surface;
	Cuboid *base;	

	float width, height, depth, thickness;
	RGBA color;

public:
	Table(const string& name, float width = 2.0f, float height = 1.0f, float depth = 1.0f, float thickness = 0.1f, RGBA color = {0.0f, 1.0f, 0.0f});
	virtual ~Table();

	void setShaderProgram(GLuint shaderProgram);
	void update(float elapsedSeconds);
	void render();
	void render(OGLReferenceFrame& frame);
};

#endif