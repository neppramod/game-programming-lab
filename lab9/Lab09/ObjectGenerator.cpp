#include "ObjectGenerator.h"
#include "MathUtil.h"
#include "OGL3DObject.h"

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

	// 1 - size, 6 vertices, each vertex has 4 position, 4 color, and 3 normal
	// 1 + (6 * 11) = 67
	float* vertexData = new float[67];
	// The first element stores the number of values
	vertexData[0] = 66;

	int i = 1;

	// Positions

	// X-axis vertex
	vertexData[i++] = 0; // x
	vertexData[i++] = 0; // y
	vertexData[i++] = 0; // z
	vertexData[i++] = 1; // w

	vertexData[i++] = length;
	vertexData[i++] = 0;
	vertexData[i++] = 0;
	vertexData[i++] = 1;

	// Y-axis vertex
	vertexData[i++] = 0; // x
	vertexData[i++] = 0; // y
	vertexData[i++] = 0; // z
	vertexData[i++] = 1; // w

	vertexData[i++] = 0;
	vertexData[i++] = length;
	vertexData[i++] = 0;
	vertexData[i++] = 1;

	// Z-axis vertex
	vertexData[i++] = 0; // x
	vertexData[i++] = 0; // y
	vertexData[i++] = 0; // z
	vertexData[i++] = 1; // w

	vertexData[i++] = 0;
	vertexData[i++] = 0;
	vertexData[i++] = length;
	vertexData[i++] = 1;

	// Colors

	// X-axis
	vertexData[i++] = 1;
	vertexData[i++] = 0;
	vertexData[i++] = 0;
	vertexData[i++] = 1;

	vertexData[i++] = 1; 
	vertexData[i++] = 0; 
	vertexData[i++] = 0; 
	vertexData[i++] = 1; 

	// Y-axis
	vertexData[i++] = 0;
	vertexData[i++] = 1;
	vertexData[i++] = 0;
	vertexData[i++] = 1;

	vertexData[i++] = 0;
	vertexData[i++] = 1;
	vertexData[i++] = 0;
	vertexData[i++] = 1;

	// Z-axis
	vertexData[i++] = 0;
	vertexData[i++] = 0;
	vertexData[i++] = 1;
	vertexData[i++] = 1;

	vertexData[i++] = 0;
	vertexData[i++] = 0;
	vertexData[i++] = 1;
	vertexData[i++] = 1;

	// Normals

	// X-axis
	vertexData[i++] = 0;
	vertexData[i++] = 1;
	vertexData[i++] = 0;

	vertexData[i++] = 0;
	vertexData[i++] = 1;
	vertexData[i++] = 0;

	// Y-axis
	vertexData[i++] = 0;
	vertexData[i++] = 0;
	vertexData[i++] = 1;

	vertexData[i++] = 0;
	vertexData[i++] = 0;
	vertexData[i++] = 1;

	// Z-axis
	vertexData[i++] = 0;
	vertexData[i++] = 1;
	vertexData[i++] = 0;

	vertexData[i++] = 0;
	vertexData[i++] = 1;
	vertexData[i++] = 0;


	// 1 - size + 3 lines * 2 vertex each
	// 1 + (3 * 2) = 7
	short* indexData = new short[7];
	indexData[0] = 6;
	i = 1;
	// X-axis
	indexData[i++] = 0;
	indexData[i++] = 1;
	// Y-axis
	indexData[i++] = 2;
	indexData[i++] = 3;
	// Z-axis
	indexData[i++] = 4;
	indexData[i++] = 5;

	ElementArray arr = { vertexData, indexData };
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

ElementArray ObjectGenerator::generateFlatSurface(int numberOfWidthSegments, int numberOfDepthSegments, float width, float depth, RGBA surfaceColor)
{
	// E.g. 
	// 1 width segment and 1 depth segments => (2 * 2) vertices = 4 vertices
	// 3 width segments and 2 depth segments => (4 * 3) vertices = 12 vertices
	int numberOfVertices = (numberOfWidthSegments + 1) * (numberOfDepthSegments + 1);
	// 4 components for position, 4 components for color, and 3 components for the normal
	int sizeOfVertexData = numberOfVertices * 11;

	// ---------------------------------------------
	// The Vertex data: position, color, and normals
	// ---------------------------------------------

	float* vertexData = new float[sizeOfVertexData + 1];
	// The first element stores the size of the vertex data
	vertexData[0] = (float)sizeOfVertexData;

	// Positions first
	// ---------------
	// Begin at the back left
	float xPos = -width / 2;
	float zPos = -depth / 2;
	float segmentWidth = width / numberOfWidthSegments;
	float segmentDepth = depth / numberOfDepthSegments;
	int i = 1;
	for (int row = 0; row <= numberOfDepthSegments; row++) {
		vertexData[i++] = xPos;
		vertexData[i++] = 0.0f;
		vertexData[i++] = zPos;
		vertexData[i++] = 1.0f;
		xPos += segmentWidth;
		for (int col = 0; col < numberOfWidthSegments; col++) {
			vertexData[i++] = xPos;
			vertexData[i++] = 0.0f;
			vertexData[i++] = zPos;
			vertexData[i++] = 1.0f;
			xPos += segmentWidth;
		}
		xPos = -width / 2;
		zPos += segmentDepth;
	}
	// Colors second
	// -------------
	for (int row = 0; row <= numberOfDepthSegments; row++) {
		vertexData[i++] = surfaceColor.red;
		vertexData[i++] = surfaceColor.green;
		vertexData[i++] = surfaceColor.blue;
		vertexData[i++] = 1.0f;
		for (int col = 0; col < numberOfWidthSegments; col++) {
			vertexData[i++] = surfaceColor.red;
			vertexData[i++] = surfaceColor.green;
			vertexData[i++] = surfaceColor.blue;
			vertexData[i++] = 1.0f;
		}
	}
	// Normals third
	// -------------
	// Since this is a flat surface, the normals point up the y-axis,
	// otherwise, we'd need to calculate the normal using the cross-product.
	for (int row = 0; row <= numberOfDepthSegments; row++) {
		vertexData[i++] = 0.0f;
		vertexData[i++] = 1.0f;
		vertexData[i++] = 0.0f;
		for (int col = 0; col < numberOfWidthSegments; col++) {
			vertexData[i++] = 0.0f;
			vertexData[i++] = 1.0f;
			vertexData[i++] = 0.0f;
		}
	}

	// --------------------------------------
	// The index data: 3 indices per triangle
	// --------------------------------------
	int numberOfTriangles = numberOfWidthSegments * numberOfDepthSegments * 2;
	int numberOfIndices = numberOfTriangles * 3;
	short* indexData = new short[numberOfIndices + 1];
	indexData[0] = numberOfIndices;
	i = 1;
	short refIndex = 0;
	short index2, index3;
	for (int row = 0; row < numberOfDepthSegments; row++) {
		for (int col = 0; col < numberOfWidthSegments; col++) {
			// Lower left triangle
			indexData[i++] = refIndex;
			index2 = refIndex + numberOfWidthSegments + 1;
			indexData[i++] = index2;
			index3 = index2 + 1;
			indexData[i++] = index3;
			// Upper right triangle
			indexData[i++] = refIndex;
			indexData[i++] = index3;
			refIndex += 1;
			indexData[i++] = refIndex;
		}
		refIndex += 1;
	}

	ElementArray arr = { vertexData, indexData };
	return arr;
}

ElementArray ObjectGenerator::generateCuboid(float width, float depth, float height, RGBA faceColor)
{
	// Since there is now a normal for each vertex and they all point in a different direction
	const int NumberOfFaces = 6;
	int numberOfVertices = NumberOfFaces * 4;
	// 4 components for position, 4 components for color, and 3 components for the normal
	int sizeOfVertexData = numberOfVertices * 11;

	// ---------------------------------------------
	// The Vertex data: position, color, and normals
	// ---------------------------------------------

	float halfWidth = width / 2.0f;
	float halfDepth = depth / 2.0f;
	float halfHeight = height / 2.0f;

	float* vertexData = new float[sizeOfVertexData + 1];
	// The first element stores the size of the vertex data
	vertexData[0] = (float)sizeOfVertexData;
	int i = 1;
	// Positions
	// Front face
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
	// Right face
	// 4
	vertexData[i++] = halfWidth;
	vertexData[i++] = halfHeight;
	vertexData[i++] = halfDepth;
	vertexData[i++] = 1.0f;
	// 5
	vertexData[i++] = halfWidth;
	vertexData[i++] = -halfHeight;
	vertexData[i++] = halfDepth;
	vertexData[i++] = 1.0f;
	// 6
	vertexData[i++] = halfWidth;
	vertexData[i++] = -halfHeight;
	vertexData[i++] = -halfDepth;
	vertexData[i++] = 1.0f;
	// 7
	vertexData[i++] = halfWidth;
	vertexData[i++] = halfHeight;
	vertexData[i++] = -halfDepth;
	vertexData[i++] = 1.0f;
	// Back face
	// 8
	vertexData[i++] = halfWidth;
	vertexData[i++] = halfHeight;
	vertexData[i++] = -halfDepth;
	vertexData[i++] = 1.0f;
	// 9
	vertexData[i++] = halfWidth;
	vertexData[i++] = -halfHeight;
	vertexData[i++] = -halfDepth;
	vertexData[i++] = 1.0f;
	// 10
	vertexData[i++] = -halfWidth;
	vertexData[i++] = -halfHeight;
	vertexData[i++] = -halfDepth;
	vertexData[i++] = 1.0f;
	// 11
	vertexData[i++] = -halfWidth;
	vertexData[i++] = halfHeight;
	vertexData[i++] = -halfDepth;
	vertexData[i++] = 1.0f;
	// Left face
	// 12
	vertexData[i++] = -halfWidth;
	vertexData[i++] = halfHeight;
	vertexData[i++] = -halfDepth;
	vertexData[i++] = 1.0f;
	// 13
	vertexData[i++] = -halfWidth;
	vertexData[i++] = -halfHeight;
	vertexData[i++] = -halfDepth;
	vertexData[i++] = 1.0f;
	// 14
	vertexData[i++] = -halfWidth;
	vertexData[i++] = -halfHeight;
	vertexData[i++] = halfDepth;
	vertexData[i++] = 1.0f;
	// 15
	vertexData[i++] = -halfWidth;
	vertexData[i++] = halfHeight;
	vertexData[i++] = halfDepth;
	vertexData[i++] = 1.0f;
	// Top face
	// 16
	vertexData[i++] = -halfWidth;
	vertexData[i++] = halfHeight;
	vertexData[i++] = -halfDepth;
	vertexData[i++] = 1.0f;
	// 17
	vertexData[i++] = -halfWidth;
	vertexData[i++] = halfHeight;
	vertexData[i++] = halfDepth;
	vertexData[i++] = 1.0f;
	// 18
	vertexData[i++] = halfWidth;
	vertexData[i++] = halfHeight;
	vertexData[i++] = halfDepth;
	vertexData[i++] = 1.0f;
	// 19
	vertexData[i++] = halfWidth;
	vertexData[i++] = halfHeight;
	vertexData[i++] = -halfDepth;
	vertexData[i++] = 1.0f;
	// Bottom face
	// 20
	vertexData[i++] = -halfWidth;
	vertexData[i++] = -halfHeight;
	vertexData[i++] = halfDepth;
	vertexData[i++] = 1.0f;
	// 21
	vertexData[i++] = -halfWidth;
	vertexData[i++] = -halfHeight;
	vertexData[i++] = -halfDepth;
	vertexData[i++] = 1.0f;
	// 22
	vertexData[i++] = halfWidth;
	vertexData[i++] = -halfHeight;
	vertexData[i++] = -halfDepth;
	vertexData[i++] = 1.0f;
	// 23
	vertexData[i++] = halfWidth;
	vertexData[i++] = -halfHeight;
	vertexData[i++] = halfDepth;
	vertexData[i++] = 1.0f;

	// Colors
	for (int vertex = 0; vertex < numberOfVertices; vertex++) {
		vertexData[i++] = faceColor.red;
		vertexData[i++] = faceColor.green;
		vertexData[i++] = faceColor.blue;
		vertexData[i++] = faceColor.alpha;
	}

	// Normals
	// Front face
	for (int vertex = 0; vertex < 4; vertex++) {
		vertexData[i++] = 0;
		vertexData[i++] = 0;
		vertexData[i++] = 1;
	}
	// Right face
	for (int vertex = 0; vertex < 4; vertex++) {
		vertexData[i++] = 1;
		vertexData[i++] = 0;
		vertexData[i++] = 0;
	}
	// Back face
	for (int vertex = 0; vertex < 4; vertex++) {
		vertexData[i++] = 0;
		vertexData[i++] = 0;
		vertexData[i++] = -1;
	}
	// Left face
	for (int vertex = 0; vertex < 4; vertex++) {
		vertexData[i++] = -1;
		vertexData[i++] = 0;
		vertexData[i++] = 0;
	}
	// Top face
	for (int vertex = 0; vertex < 4; vertex++) {
		vertexData[i++] = 0;
		vertexData[i++] = 1;
		vertexData[i++] = 0;
	}
	// Bottom face
	for (int vertex = 0; vertex < 4; vertex++) {
		vertexData[i++] = 0;
		vertexData[i++] = -1;
		vertexData[i++] = 0;
	}
	
	// --------------------------------------
	// The index data: 3 indices per triangle
	// --------------------------------------
	const int NumberOfTriangles = NumberOfFaces * 2;
	const int NumberOfIndices = NumberOfTriangles * 3;
	short* indexData = new short[NumberOfIndices + 1];
	indexData[0] = (short)NumberOfIndices;
	i = 1;
	// Front face
	indexData[i++] = 0;
	indexData[i++] = 1;
	indexData[i++] = 2;
	indexData[i++] = 0;
	indexData[i++] = 2;
	indexData[i++] = 3;
	// Right face
	indexData[i++] = 4;
	indexData[i++] = 5;
	indexData[i++] = 6;
	indexData[i++] = 4;
	indexData[i++] = 6;
	indexData[i++] = 7;
	// Back face
	indexData[i++] = 8;
	indexData[i++] = 9;
	indexData[i++] = 10;
	indexData[i++] = 8;
	indexData[i++] = 10;
	indexData[i++] = 11;
	// Left face
	indexData[i++] = 12;
	indexData[i++] = 13;
	indexData[i++] = 14;
	indexData[i++] = 12;
	indexData[i++] = 14;
	indexData[i++] = 15;
	// Top face
	indexData[i++] = 16;
	indexData[i++] = 17;
	indexData[i++] = 18;
	indexData[i++] = 16;
	indexData[i++] = 18;
	indexData[i++] = 19;
	// Bottom face
	indexData[i++] = 20;
	indexData[i++] = 21;
	indexData[i++] = 22;
	indexData[i++] = 20;
	indexData[i++] = 22;
	indexData[i++] = 23;

	ElementArray arr = { vertexData, indexData };
	return arr;
}
