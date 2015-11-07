#pragma once
#ifndef ARM
#define ARM

#include "OGL3DCompositeObject.h"

#include <string>
using std::string;

class Cuboid;
class Axis;
class Sword;

class Arm :
	public OGL3DCompositeObject
{
public:
	enum State { UP_MOVEMENT, DOWN_MOVEMENT };

protected:
	Cuboid *shoulder;
	Cuboid *bicep;
	Cuboid *forearm;
	Cuboid *hand;
	Sword *sword;

	float angleX;
	State state;
	


private:
	Axis *axis;

public:
	Arm(const string &name);
	virtual ~Arm();

	void setShaderProgram(GLuint shaderProgram);
	void update(float elapsedSeconds);
	void render();
	void addSword(Sword *sword);
};

#endif