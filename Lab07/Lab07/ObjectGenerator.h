#pragma once
#ifndef OBJECT_GENERATOR
#define OBJECT_GENERATOR

#include "RGBA.h"

struct ElementArray {
	float *vertexData;
	short *indexData;
};

class ObjectGenerator
{
public:
	ObjectGenerator();
	~ObjectGenerator();

	// Generates the vertices for a right-handed axes system on the heap.
	// The very first element is the number of values.  Vertices are stored first
	// and colors are stored after.
	static float* generateRightHandedAxes(float length = 1);

	// Generates the vertices and indexes for a right-handed axes system on the heap.
	// The very first element is the number of values.  Vertices are stored first
	// and colors are stored after.
	// Since this uses an indexed array, the index array is also returned.
	// Return values:
	// - ElementArray::vertexData = pointer to the vertex data
	// - ElementArray::indexData = pointer to the index data
	static ElementArray generateRightHandedAxesIndexedArray(float length = 1);

	static float* generateXZSurface(float width = 1, float depth = 1);

	static float* generatePyramid(float width = 1, float depth = 1, float height = 1);

	static ElementArray generatePyramidIndexedArray(
		float width = 1, float depth = 1, float height = 1, 
		RGBA faceColor = { 1, 1, 1, 1 });

	static ElementArray generateLineBoxIndexedArray(
		float width = 1, float depth = 1, float height = 1,
		RGBA lineColor = { 1, 1, 1, 1 });

	static ElementArray generateBoxIndexedArray(
		float width, float depth, float height, RGBA faceColor);
};

#endif

