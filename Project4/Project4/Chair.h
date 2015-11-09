#pragma once
#include "OGL3DCompositeObject.h"

class Cuboid;

/*
 A chair object that can be placed in the room
*/
class Chair :
	public OGL3DCompositeObject
{
private:
	Cuboid *surface;
	Cuboid *backSupport;
	Cuboid *frontSupport;

	float width, height, depth, thickness;
	RGBA color;
public:
	Chair(const string& name, float width = 1.0f, float height = 1.0f, float depth = 1.0f, float thickness = 0.1f, RGBA color = { 0.0f, 1.0f, 0.0f });
	virtual ~Chair();

	void setShaderProgram(GLuint shaderProgram);
	void update(float elapsedSeconds);
	void render();
	void render(OGLReferenceFrame& frame);
};

