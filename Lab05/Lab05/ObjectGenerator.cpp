#include "ObjectGenerator.h"

ObjectGenerator::ObjectGenerator()
{
}

ObjectGenerator::~ObjectGenerator()
{
}

float* ObjectGenerator::generateRightHandedAxes(float length)
{
	if (length <= 0) length = 1;

	// 1 - size, 3 lines * 2 vertices each, each vertex has 4 position and 4 color
	// 1 + (6 * (4 + 4)) = 49
	float* data = new float[49];

	// The first element stores the number of values
	data[0] = 48;

	int i = 1; // index

	// Positions

	// X-axis
	//
	data[i++] = 0; // x
	data[i++] = 0; // y
	data[i++] = 0; // z
	data[i++] = 1; // w

	data[i++] = length;
	data[i++] = 0;
	data[i++] = 0;
	data[i++] = 1;

	// Y-axis
	// 
	data[i++] = 0;
	data[i++] = 0;
	data[i++] = 0;
	data[i++] = 1;

	// Vertex
	data[i++] = 0;
	data[i++] = length;
	data[i++] = 0;
	data[i++] = 1;

	// Z-axis
	// 
	data[i++] = 0;
	data[i++] = 0;
	data[i++] = 0;
	data[i++] = 1;

	data[i++] = 0;
	data[i++] = 0;
	data[i++] = length;
	data[i++] = 1;

	// Colors
	
	// X-axis
	//
	data[i++] = 1; // red
	data[i++] = 0; // green
	data[i++] = 0; // blue
	data[i++] = 1; // alpha

	data[i++] = 1;
	data[i++] = 0;
	data[i++] = 0;
	data[i++] = 1;

	// Y-axis
	//
	data[i++] = 0;
	data[i++] = 1;
	data[i++] = 0;
	data[i++] = 1;

	data[i++] = 0;
	data[i++] = 1;
	data[i++] = 0;
	data[i++] = 1;

	// Z-axis
	// 
	data[i++] = 0;
	data[i++] = 0;
	data[i++] = 1;
	data[i++] = 1;

	data[i++] = 0;
	data[i++] = 0;
	data[i++] = 1;
	data[i++] = 1;

	return data;
}

float* ObjectGenerator::generateXZSurface(float width, float depth)
{
	// This object's origin is in the center.
	float halfWidth = width / 2.0f;
	float halfDepth = depth / 2.0f;

	//         width
	//          D
	//      { A +--+ F
	// depth{   |\ |
	//      {   | \|
	//      { B +--+ C
	//             E

	// 1 - size + (2 triangles * 3 vertices each * (4 position + 4 color))
	// 1 + (2 * 3 * (4 + 4)) = 49
	float* data = new float[49];

	// The first element stores the number of values
	data[0] = 48;

	int i = 1; // index
			   // Positions
			   // A
	data[i++] = -halfWidth; // x
	data[i++] = 0.0f;       // y
	data[i++] = -halfDepth; // z
	data[i++] = 1.0f;       // w
							// B
	data[i++] = -halfWidth;
	data[i++] = 0.0f;
	data[i++] = halfDepth;
	data[i++] = 1.0f;
	// C
	data[i++] = halfWidth;
	data[i++] = 0.0f;
	data[i++] = halfDepth;
	data[i++] = 1.0f;
	// D
	data[i++] = -halfWidth;
	data[i++] = 0.0f;
	data[i++] = -halfDepth;
	data[i++] = 1.0f;
	// E
	data[i++] = halfWidth;
	data[i++] = 0.0f;
	data[i++] = halfDepth;
	data[i++] = 1.0f;
	// F
	data[i++] = halfWidth;
	data[i++] = 0.0f;
	data[i++] = -halfDepth;
	data[i++] = 1.0f;

	// Colors
	// A
	data[i++] = 0.0f; // red
	data[i++] = 0.4f; // green
	data[i++] = 0.0f; // blue
	data[i++] = 1.0f; // alpha
					  // B
	data[i++] = 0.0f;
	data[i++] = 0.4f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	// C
	data[i++] = 0.0f;
	data[i++] = 0.4f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	// D
	data[i++] = 0.0f;
	data[i++] = 0.4f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	// E
	data[i++] = 0.0f;
	data[i++] = 0.4f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	// F
	data[i++] = 0.0f;
	data[i++] = 0.4f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	return data;

}
