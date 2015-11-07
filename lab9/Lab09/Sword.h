#pragma once
#ifndef SWORD
#define SWORD
#include "OGL3DCompositeObject.h"


#include <string>
using std::string;

class Cuboid;
class Axis;

class Sword :
	public OGL3DCompositeObject
{
protected:
	Cuboid *hilt;
	Cuboid *crossguard;
	Cuboid *blade;
	
private:
	Axis *axis;
public:

	Sword(const string &name);
	virtual ~Sword();

	void setShaderProgram(GLuint shaderProgram);
	void update(float elapsedSeconds);
	void render();
};

#endif