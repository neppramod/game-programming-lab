#include "ObjectGenerator.h"
#include "MathUtil.h"

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

ElementArray ObjectGenerator::generateRightHandedAxesIndexedArray(float length)
{
	if (length <= 0) length = 1;

	// 1 - size, 4 vertices, each vertex has 4 position and 4 color
	// 1 + (4 * (4 + 4)) = 33
	float* data = new float[33];

	// The first element stores the number of values
	data[0] = 32;

	int i = 1; // index

	// Positions

	// Origin vertex
	data[i++] = 0; // x
	data[i++] = 0; // y
	data[i++] = 0; // z
	data[i++] = 1; // w

	// X-axis vertex
	data[i++] = length;
	data[i++] = 0;
	data[i++] = 0;
	data[i++] = 1;

	// Y-axis vertex
	data[i++] = 0;
	data[i++] = length;
	data[i++] = 0;
	data[i++] = 1;

	// Z-axis vertex
	data[i++] = 0;
	data[i++] = 0;
	data[i++] = length;
	data[i++] = 1;

	// Colors

	// Origin
	data[i++] = 0; // red
	data[i++] = 0; // green
	data[i++] = 0; // blue
	data[i++] = 1; // alpha

	// X-axis
	data[i++] = 1; 
	data[i++] = 0; 
	data[i++] = 0; 
	data[i++] = 1; 

	// Y-axis
	data[i++] = 0;
	data[i++] = 1;
	data[i++] = 0;
	data[i++] = 1;

	// Z-axis
	data[i++] = 0;
	data[i++] = 0;
	data[i++] = 1;
	data[i++] = 1;

	// 1 - size + 3 lines * 2 vertex each
	// 1 + (3 * 2) = 7
	short* indexes = new short[7];
	indexes[0] = 6;
	i = 1;
	// X-axis
	indexes[i++] = 0;
	indexes[i++] = 1;
	// Y-axis
	indexes[i++] = 0;
	indexes[i++] = 2;
	// Z-axis
	indexes[i++] = 0;
	indexes[i++] = 3;

	ElementArray arr = { data, indexes };
	return arr;
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

float* ObjectGenerator::generatePyramid(float width, float depth, float height)
{
	// This pyramid's origin is in the center of the base.
	float halfWidth = width / 2.0f;
	float halfDepth = depth / 2.0f;

	// 1 size + (6 triangles * 3 vertices each * (4 position + 4 color))
	// 1 + (6 * 3 * (4 + 4)) = 145
	float* data = new float[145];

	// The first element stores the number of elements.
	data[0] = 144;

	int i = 1;
	// South face
	// Lower-left
	data[i++] = -halfWidth;
	data[i++] = 0.0f;
	data[i++] = halfDepth;
	data[i++] = 1.0f;
	// Lower-right
	data[i++] = halfWidth;
	data[i++] = 0.0f;
	data[i++] = halfDepth;
	data[i++] = 1.0f;
	// Apex
	data[i++] = 0.0f;
	data[i++] = height;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// East face
	// Lower-left
	data[i++] = halfWidth;
	data[i++] = 0.0f;
	data[i++] = halfDepth;
	data[i++] = 1.0f;
	// Lower-right
	data[i++] = halfWidth;
	data[i++] = 0.0f;
	data[i++] = -halfDepth;
	data[i++] = 1.0f;
	// Apex
	data[i++] = 0.0f;
	data[i++] = height;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// North face
	// Lower-left
	data[i++] = halfWidth;
	data[i++] = 0.0f;
	data[i++] = -halfDepth;
	data[i++] = 1.0f;
	// Lower-right
	data[i++] = -halfWidth;
	data[i++] = 0.0f;
	data[i++] = -halfDepth;
	data[i++] = 1.0f;
	// Apex
	data[i++] = 0.0f;
	data[i++] = height;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// West face
	// Lower-left
	data[i++] = -halfWidth;
	data[i++] = 0.0f;
	data[i++] = -halfDepth;
	data[i++] = 1.0f;
	// Lower-right
	data[i++] = -halfWidth;
	data[i++] = 0.0f;
	data[i++] = halfDepth;
	data[i++] = 1.0f;
	// Apex
	data[i++] = 0.0f;
	data[i++] = height;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// Base
	// Upper-left
	data[i++] = -halfWidth;
	data[i++] = 0.0f;
	data[i++] = halfDepth;
	data[i++] = 1.0f;
	// Lower-left
	data[i++] = -halfWidth;
	data[i++] = 0.0f;
	data[i++] = -halfDepth;
	data[i++] = 1.0f;
	// Lower-right
	data[i++] = halfWidth;
	data[i++] = 0.0f;
	data[i++] = -halfDepth;
	data[i++] = 1.0f;
	// Upper-left
	data[i++] = -halfWidth;
	data[i++] = 0.0f;
	data[i++] = halfDepth;
	data[i++] = 1.0f;
	// Lower-right
	data[i++] = halfWidth;
	data[i++] = 0.0f;
	data[i++] = -halfDepth;
	data[i++] = 1.0f;
	// Upper-right
	data[i++] = halfWidth;
	data[i++] = 0.0f;
	data[i++] = halfDepth;
	data[i++] = 1.0f;

	// Colors
	// South face
	// Lower-left
	data[i++] = 1.0f;
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	// Lower-right
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	// Apex
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;

	// East face
	// Lower-left
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;
	// Lower-right
	data[i++] = 1.0f;
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	// Apex
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// North face
	// Lower-left
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	// Lower-right
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;
	// Apex
	data[i++] = 1.0f;
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// West face
	// Lower-left
	data[i++] = 1.0f;
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	// Lower-right
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	// Apex
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;

	// Base
	// Upper-left
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;
	// Lower-left
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;
	// Lower-right
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;
	// Upper-left
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;
	// Lower-right
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;
	// Upper-right
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;

	return data;
}

ElementArray ObjectGenerator::generatePyramidIndexedArray(
	float width, float depth, float height, RGBA faceColor)
{
	// This pyramid's origin is in the center.
	float halfWidth = width / 2.0f;
	float halfDepth = depth / 2.0f;

	//           width
	//      { 0 +-----+ 3
	//      {   |\   /|
	//      {   | \ / | 
	// depth{   |  +4 |
	//      {   | / \ |
	//      {   |/   \|
	//      { 1 +-----+ 2

	// The pyramid has 5 vertices, each vertex has a 4 position component
	// and a 4 color component.
	// 1 + (5 * (4 + 4)) = 41
	float* vertexData = new float[41];
	// Number of elements
	vertexData[0] = 40;
	int i = 1; // Current index

	// Vertex 0
	vertexData[i++] = -halfWidth; 
	vertexData[i++] = 0.0f;       
	vertexData[i++] = -halfDepth; 
	vertexData[i++] = 1.0f;  
	// Vertex 1
	vertexData[i++] = -halfWidth;
	vertexData[i++] = 0.0f;
	vertexData[i++] = halfDepth;
	vertexData[i++] = 1.0f;
	// Vertex 2
	vertexData[i++] = halfWidth;
	vertexData[i++] = 0.0f;
	vertexData[i++] = halfDepth;
	vertexData[i++] = 1.0f;
	// Vertex 3
	vertexData[i++] = halfWidth;
	vertexData[i++] = 0.0f;
	vertexData[i++] = -halfDepth;
	vertexData[i++] = 1.0f;
	// Vertex 4
	vertexData[i++] = 0.0f;
	vertexData[i++] = height;
	vertexData[i++] = 0.0f;
	vertexData[i++] = 1.0f;
	// Colors
	// Vertex 0
	vertexData[i++] = faceColor.red;
	vertexData[i++] = faceColor.green;
	vertexData[i++] = faceColor.blue;
	vertexData[i++] = faceColor.alpha;
	// Vertex 1
	vertexData[i++] = faceColor.red;
	vertexData[i++] = faceColor.green;
	vertexData[i++] = faceColor.blue;
	vertexData[i++] = faceColor.alpha;
	// Vertex 2
	vertexData[i++] = faceColor.red;
	vertexData[i++] = faceColor.green;
	vertexData[i++] = faceColor.blue;
	vertexData[i++] = faceColor.alpha;
	// Vertex 3
	vertexData[i++] = faceColor.red;
	vertexData[i++] = faceColor.green;
	vertexData[i++] = faceColor.blue;
	vertexData[i++] = faceColor.alpha;
	// Vertex 4
	vertexData[i++] = faceColor.red;
	vertexData[i++] = faceColor.green;
	vertexData[i++] = faceColor.blue;
	vertexData[i++] = faceColor.alpha;

	// There are 6 triangles with 3 vertex each.
	// 1 + (6 * 3) = 19
	short* indexData = new short[19];
	indexData[0] = 18;
	i = 1;
	// West side
	indexData[i++] = 0;
	indexData[i++] = 1;
	indexData[i++] = 4;
	// South side
	indexData[i++] = 1;
	indexData[i++] = 2;
	indexData[i++] = 4;
	// East side
	indexData[i++] = 2;
	indexData[i++] = 3;
	indexData[i++] = 4;
	// North side
	indexData[i++] = 3;
	indexData[i++] = 0;
	indexData[i++] = 4;
	// Base 1
	indexData[i++] = 1;
	indexData[i++] = 0;
	indexData[i++] = 3;
	// Base 2
	indexData[i++] = 1;
	indexData[i++] = 3;
	indexData[i++] = 2;

	ElementArray arr = { vertexData, indexData };
	return arr;
}

ElementArray ObjectGenerator::generateLineBoxIndexedArray(
	float width, float depth, float height, RGBA lineColor)
{
	float halfWidth = width / 2.0f;
	float halfDepth = width / 2.0f;
	float halfHeight = width / 2.0f;

	// 1 + (8 * (4 + 4)) = 65
	float* vertexData = new float[65];
	vertexData[0] = 64;
	int i = 1;
	// Positions
	// 0
	vertexData[i++] = -halfWidth;
	vertexData[i++] = halfHeight;
	vertexData[i++] = halfDepth;
	vertexData[i++] = 1.0f;
	// 1
	vertexData[i++] = -halfWidth;
	vertexData[i++] = -halfHeight;
	vertexData[i++] = halfDepth;
	vertexData[i++] = 1.0f;
	// 2
	vertexData[i++] = halfWidth;
	vertexData[i++] = -halfHeight;
	vertexData[i++] = halfDepth;
	vertexData[i++] = 1.0f;
	// 3
	vertexData[i++] = halfWidth;
	vertexData[i++] = halfHeight;
	vertexData[i++] = halfDepth;
	vertexData[i++] = 1.0f;
	// 4
	vertexData[i++] = halfWidth;
	vertexData[i++] = halfHeight;
	vertexData[i++] = -halfDepth;
	vertexData[i++] = 1.0f;
	// 5
	vertexData[i++] = halfWidth;
	vertexData[i++] = -halfHeight;
	vertexData[i++] = -halfDepth;
	vertexData[i++] = 1.0f;
	// 6
	vertexData[i++] = -halfWidth;
	vertexData[i++] = -halfHeight;
	vertexData[i++] = -halfDepth;
	vertexData[i++] = 1.0f;
	// 7
	vertexData[i++] = -halfWidth;
	vertexData[i++] = halfHeight;
	vertexData[i++] = -halfDepth;
	vertexData[i++] = 1.0f;
	// Colors
	// 0
	vertexData[i++] = lineColor.red;
	vertexData[i++] = lineColor.green;
	vertexData[i++] = lineColor.blue;
	vertexData[i++] = 1.0f;
	// 1
	vertexData[i++] = lineColor.red;
	vertexData[i++] = lineColor.green;
	vertexData[i++] = lineColor.blue;
	vertexData[i++] = 1.0f;
	// 2
	vertexData[i++] = lineColor.red;
	vertexData[i++] = lineColor.green;
	vertexData[i++] = lineColor.blue;
	vertexData[i++] = 1.0f;
	// 3
	vertexData[i++] = lineColor.red;
	vertexData[i++] = lineColor.green;
	vertexData[i++] = lineColor.blue;
	vertexData[i++] = 1.0f;
	// 4
	vertexData[i++] = lineColor.red;
	vertexData[i++] = lineColor.green;
	vertexData[i++] = lineColor.blue;
	vertexData[i++] = 1.0f;
	// 5
	vertexData[i++] = lineColor.red;
	vertexData[i++] = lineColor.green;
	vertexData[i++] = lineColor.blue;
	vertexData[i++] = 1.0f;
	// 6
	vertexData[i++] = lineColor.red;
	vertexData[i++] = lineColor.green;
	vertexData[i++] = lineColor.blue;
	vertexData[i++] = 1.0f;
	// 7
	vertexData[i++] = lineColor.red;
	vertexData[i++] = lineColor.green;
	vertexData[i++] = lineColor.blue;
	vertexData[i++] = 1.0f;

	// 1 + (12 * 2) = 25
	short* indexData = new short[25];
	indexData[0] = 24;
	i = 1;
	indexData[i++] = 0;
	indexData[i++] = 1;

	indexData[i++] = 1;
	indexData[i++] = 2;

	indexData[i++] = 2;
	indexData[i++] = 3;

	indexData[i++] = 3;
	indexData[i++] = 0;

	indexData[i++] = 4;
	indexData[i++] = 5;

	indexData[i++] = 5;
	indexData[i++] = 6;

	indexData[i++] = 6;
	indexData[i++] = 7;

	indexData[i++] = 7;
	indexData[i++] = 4;

	indexData[i++] = 0;
	indexData[i++] = 7;

	indexData[i++] = 3;
	indexData[i++] = 4;

	indexData[i++] = 2;
	indexData[i++] = 5;

	indexData[i++] = 1;
	indexData[i++] = 6;

	ElementArray arr = { vertexData, indexData };
	return arr;
}

ElementArray ObjectGenerator::generateBoxIndexedArray(
	float width, float depth, float height, RGBA lineColor) // faceColor
{
	float halfWidth = width / 2.0f;
	float halfDepth = width / 2.0f;
	float halfHeight = width / 2.0f;

	// 1 + (8 * (4 + 4)) = 65
	float* vertexData = new float[65];
	vertexData[0] = 64;
	int i = 1;
	// Positions
	// 0
	vertexData[i++] = -halfWidth;
	vertexData[i++] = halfHeight;
	vertexData[i++] = halfDepth;
	vertexData[i++] = 1.0f;
	// 1
	vertexData[i++] = -halfWidth;
	vertexData[i++] = -halfHeight;
	vertexData[i++] = halfDepth;
	vertexData[i++] = 1.0f;
	// 2
	vertexData[i++] = halfWidth;
	vertexData[i++] = -halfHeight;
	vertexData[i++] = halfDepth;
	vertexData[i++] = 1.0f;
	// 3
	vertexData[i++] = halfWidth;
	vertexData[i++] = halfHeight;
	vertexData[i++] = halfDepth;
	vertexData[i++] = 1.0f;
	// 4
	vertexData[i++] = halfWidth;
	vertexData[i++] = halfHeight;
	vertexData[i++] = -halfDepth;
	vertexData[i++] = 1.0f;
	// 5
	vertexData[i++] = halfWidth;
	vertexData[i++] = -halfHeight;
	vertexData[i++] = -halfDepth;
	vertexData[i++] = 1.0f;
	// 6
	vertexData[i++] = -halfWidth;
	vertexData[i++] = -halfHeight;
	vertexData[i++] = -halfDepth;
	vertexData[i++] = 1.0f;
	// 7
	vertexData[i++] = -halfWidth;
	vertexData[i++] = halfHeight;
	vertexData[i++] = -halfDepth;
	vertexData[i++] = 1.0f;
	// Colors
	// 0
	vertexData[i++] = lineColor.red;
	vertexData[i++] = lineColor.green;
	vertexData[i++] = lineColor.blue;
	vertexData[i++] = 1.0f;
	// 1
	vertexData[i++] = lineColor.red;
	vertexData[i++] = lineColor.green;
	vertexData[i++] = lineColor.blue;
	vertexData[i++] = 1.0f;
	// 2
	vertexData[i++] = lineColor.red;
	vertexData[i++] = lineColor.green;
	vertexData[i++] = lineColor.blue;
	vertexData[i++] = 1.0f;
	// 3
	vertexData[i++] = lineColor.red;
	vertexData[i++] = lineColor.green;
	vertexData[i++] = lineColor.blue;
	vertexData[i++] = 1.0f;
	// 4
	vertexData[i++] = lineColor.red;
	vertexData[i++] = lineColor.green;
	vertexData[i++] = lineColor.blue;
	vertexData[i++] = 1.0f;
	// 5
	vertexData[i++] = lineColor.red;
	vertexData[i++] = lineColor.green;
	vertexData[i++] = lineColor.blue;
	vertexData[i++] = 1.0f;
	// 6
	vertexData[i++] = lineColor.red;
	vertexData[i++] = lineColor.green;
	vertexData[i++] = lineColor.blue;
	vertexData[i++] = 1.0f;
	// 7
	vertexData[i++] = lineColor.red;
	vertexData[i++] = lineColor.green;
	vertexData[i++] = lineColor.blue;
	vertexData[i++] = 1.0f;

	// 1 + (12 * 3) = 37
	short* indexData = new short[37];
	indexData[0] = 36;
	i = 1;
	indexData[i++] = 0;
	indexData[i++] = 1;
	indexData[i++] = 3;

	indexData[i++] = 1;
	indexData[i++] = 2;
	indexData[i++] = 3;

	indexData[i++] = 3;
	indexData[i++] = 2;
	indexData[i++] = 4;

	indexData[i++] = 2;
	indexData[i++] = 5;
	indexData[i++] = 4;

	indexData[i++] = 4;
	indexData[i++] = 5;
	indexData[i++] = 7;

	indexData[i++] = 5;
	indexData[i++] = 6;
	indexData[i++] = 7;

	indexData[i++] = 7;
	indexData[i++] = 6;
	indexData[i++] = 0;

	indexData[i++] = 6;
	indexData[i++] = 1;
	indexData[i++] = 0;

	indexData[i++] = 7;
	indexData[i++] = 0;
	indexData[i++] = 4;

	indexData[i++] = 0;
	indexData[i++] = 3;
	indexData[i++] = 4;

	indexData[i++] = 5;
	indexData[i++] = 2;
	indexData[i++] = 6;

	indexData[i++] = 2;
	indexData[i++] = 1;
	indexData[i++] = 6;
	

	ElementArray arr = { vertexData, indexData };
	return arr;
}