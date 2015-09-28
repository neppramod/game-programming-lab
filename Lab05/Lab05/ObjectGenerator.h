#pragma once
#ifndef OBJECT_GENERATOR
#define OBJECT_GENERATOR

class ObjectGenerator
{
public:
	ObjectGenerator();
	~ObjectGenerator();

	// Generates the vertices for a right-handed axes system on the heap.
	// The very first element is the number of values.  Vertices are stored first
	// and colors are stored after.
	static float* generateRightHandedAxes(float length = 1);
	static float* generateXZSurface(float width, float depth);
	static float* generatePyramid(float width, float depth, float height);
	static float* generateCubeoid(float width, float depth, float height);	
};

#endif

