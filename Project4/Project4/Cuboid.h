#pragma once
#ifndef CUBOID
#define CUBOID

#include "OGL3DObject.h"

class Cuboid :
	public OGL3DObject
{
protected:
	float width, depth, height;
	RGBA faceColor;

public:
	Cuboid(const string& name,float width = 1, float depth = 1, float height = 1, RGBA faceColor = { 1, 1, 1, 1 });
	virtual ~Cuboid();

protected:
	void generate();
};

#endif

