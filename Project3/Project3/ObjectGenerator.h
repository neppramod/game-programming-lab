#pragma once
#ifndef OBJECT_GENERATOR
#define OBJECT_GENERATOR

#include "RGBA.h"

class OGL3DObject;

struct ElementArray {
	float *vertexData;
	short *indexData;
};

class ObjectGenerator
{
public:
	ObjectGenerator();
	~ObjectGenerator();


	// In the indexed array generators Vertices are stored first
	// and colors are stored after.
	// Since this uses an indexed array, the index array is also returned.
	// Return values:
	// - ElementArray::vertexData = pointer to the vertex data
	// - ElementArray::indexData = pointer to the index data	

	static float* generateXZSurface(float width = 1, float depth = 1);

	// Generate the box where the animation happens
	static  ElementArray generateFlatSurface(int numberOfWidthSegments = 10, int numberOfDepthSegments = 10, float width = 10, float depth = 10, RGBA surfaceColor = { 1, 1, 1, 1 });
	
	// Generate a vehicle
	static ElementArray generateBoxIndexedArrayTruck(
		float width, float depth, float height, RGBA faceColor);

	// Generate a hovering servillenge camera
	static ElementArray generateFlyingSurveillanceCamera(
		float width, float depth, float height, RGBA faceColor);

	// Generate a box. Used for creating buildings
	static ElementArray generateBoxIndexedArray(
		float width, float depth, float height, RGBA faceColor);

	

	
};

#endif

