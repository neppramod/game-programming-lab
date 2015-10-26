#include "ObjectGenerator.h"
#include "MathUtil.h"
#include "OGL3DObject.h"

ObjectGenerator::ObjectGenerator()
{
}

ObjectGenerator::~ObjectGenerator()
{
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



// This object generator is used for creating a vehicle
ElementArray ObjectGenerator::generateBoxIndexedArrayTruck(
	float width, float depth, float height, RGBA lineColor) // faceColor
{
	float halfWidth = width / 2.0f;
	float halfDepth = width / 2.0f;
	float halfHeight = width / 2.0f;

	// 1 + (14 * (4 + 4)) = 113
	float* vertexData = new float[113];
	vertexData[0] = 112;
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

	// 8
	vertexData[i++] = -halfWidth;
	vertexData[i++] = halfHeight + halfHeight;
	vertexData[i++] = -halfDepth;
	vertexData[i++] = 1.0f;

	// 9
	vertexData[i++] = halfWidth;
	vertexData[i++] = halfHeight + halfHeight;
	vertexData[i++] = -halfDepth;
	vertexData[i++] = 1.0f;

	// 10
	vertexData[i++] = -halfWidth;
	vertexData[i++] = halfHeight + halfHeight;
	vertexData[i++] = -halfDepth - depth - depth;
	vertexData[i++] = 1.0f;

	// 11
	vertexData[i++] = halfWidth;
	vertexData[i++] = halfHeight + halfHeight;
	vertexData[i++] = -halfDepth - depth - depth;
	vertexData[i++] = 1.0f;

	// 12
	vertexData[i++] = halfWidth;
	vertexData[i++] = -halfHeight;
	vertexData[i++] = -halfDepth - depth - depth;
	vertexData[i++] = 1.0f;

	// 13
	vertexData[i++] = -halfWidth;
	vertexData[i++] = -halfHeight;
	vertexData[i++] = -halfDepth - depth - depth;
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
	// 8
	vertexData[i++] = lineColor.red;
	vertexData[i++] = lineColor.green;
	vertexData[i++] = lineColor.blue;
	vertexData[i++] = 1.0f;
	// 9
	vertexData[i++] = lineColor.red;
	vertexData[i++] = lineColor.green;
	vertexData[i++] = lineColor.blue;
	vertexData[i++] = 1.0f;
	// 10
	vertexData[i++] = lineColor.red;
	vertexData[i++] = lineColor.green;
	vertexData[i++] = lineColor.blue;
	vertexData[i++] = 1.0f;
	// 11
	vertexData[i++] = lineColor.red;
	vertexData[i++] = lineColor.green;
	vertexData[i++] = lineColor.blue;
	vertexData[i++] = 1.0f;
	// 12
	vertexData[i++] = lineColor.red;
	vertexData[i++] = lineColor.green;
	vertexData[i++] = lineColor.blue;
	vertexData[i++] = 1.0f;
	// 13
	vertexData[i++] = lineColor.red;
	vertexData[i++] = lineColor.green;
	vertexData[i++] = lineColor.blue;
	vertexData[i++] = 1.0f;

	// 1 + 2 * (6 * 2 * 3) = 73
	short* indexData = new short[73];
	indexData[0] = 72;
	i = 1;

	// Front
	indexData[i++] = 0;
	indexData[i++] = 1;
	indexData[i++] = 3;

	indexData[i++] = 1;
	indexData[i++] = 2;
	indexData[i++] = 3;

	// Right
	indexData[i++] = 3;
	indexData[i++] = 2;
	indexData[i++] = 4;

	indexData[i++] = 2;
	indexData[i++] = 5;
	indexData[i++] = 4;

	// Back
	indexData[i++] = 4;
	indexData[i++] = 5;
	indexData[i++] = 7;

	indexData[i++] = 5;
	indexData[i++] = 6;
	indexData[i++] = 7;

	// Left
	indexData[i++] = 7;
	indexData[i++] = 6;
	indexData[i++] = 0;

	indexData[i++] = 6;
	indexData[i++] = 1;
	indexData[i++] = 0;

	// Top
	indexData[i++] = 7;
	indexData[i++] = 0;
	indexData[i++] = 4;

	indexData[i++] = 0;
	indexData[i++] = 3;
	indexData[i++] = 4;

	// Bottom
	indexData[i++] = 5;
	indexData[i++] = 2;
	indexData[i++] = 6;

	indexData[i++] = 2;
	indexData[i++] = 1;
	indexData[i++] = 6;

	// Back side of the truck

	// Front
	indexData[i++] = 8;
	indexData[i++] = 6;
	indexData[i++] = 9;

	indexData[i++] = 6;
	indexData[i++] = 5;
	indexData[i++] = 9;

	// Right
	indexData[i++] = 9;
	indexData[i++] = 5;
	indexData[i++] = 11;

	indexData[i++] = 5;
	indexData[i++] = 12;
	indexData[i++] = 11;

	// Back
	indexData[i++] = 11;
	indexData[i++] = 12;
	indexData[i++] = 10;

	indexData[i++] = 12;
	indexData[i++] = 13;
	indexData[i++] = 10;

	// Left
	indexData[i++] = 10;
	indexData[i++] = 13;
	indexData[i++] = 8;

	indexData[i++] = 13;
	indexData[i++] = 6;
	indexData[i++] = 8;

	// Top
	indexData[i++] = 8;
	indexData[i++] = 9;
	indexData[i++] = 10;

	indexData[i++] = 9;
	indexData[i++] = 11;
	indexData[i++] = 10;

	// Bottom
	indexData[i++] = 5;
	indexData[i++] = 12;
	indexData[i++] = 6;

	indexData[i++] = 12;
	indexData[i++] = 13;
	indexData[i++] = 6;
	ElementArray arr = { vertexData, indexData };
	return arr;
}


ElementArray ObjectGenerator::generateFlyingSurveillanceCamera(
	float width, float depth, float height, RGBA faceColor)
{
	// This flying Surveillance camera's origin is in the center.
	float halfWidth = width / 2.0f;
	float halfDepth = depth / 2.0f;
	float halfHeight = height / 2.0f;

	//           width
	//      { 0 +-----+ 3
	//      {   |\   /|
	//      {   | \ / |      
	// depth{   |  +4 |
	//      {   | / \ |
	//      {   |/   \|
	//      { 1 +-----+ 2

	// The cuboid will have 5 6 7 8 as top face and 9 10 11 12 as bottom


	// The pyramid + cuboid object has 13 vertices, each vertex has a 4 position component
	// and a 4 color component.
	// 1 + (13 * (4 + 4)) = 105
	float* vertexData = new float[105];
	// Number of elements
	vertexData[0] = 104;
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

	// Vertex 5
	vertexData[i++] = -halfWidth / 2;
	vertexData[i++] = 0.0f;
	vertexData[i++] = -halfDepth / 2;
	vertexData[i++] = 1.0f;
	// Vertex 6
	vertexData[i++] = -halfWidth / 2;
	vertexData[i++] = 0.0f;
	vertexData[i++] = halfDepth / 2;
	vertexData[i++] = 1.0f;
	// Vertex 7
	vertexData[i++] = halfWidth / 2;
	vertexData[i++] = 0.0f;
	vertexData[i++] = halfDepth / 2;
	vertexData[i++] = 1.0f;
	// Vertex 8
	vertexData[i++] = halfWidth / 2;
	vertexData[i++] = 0.0f;
	vertexData[i++] = -halfDepth / 2;
	vertexData[i++] = 1.0f;

	// Vertex 9
	vertexData[i++] = -halfWidth / 2;
	vertexData[i++] = -halfHeight;
	vertexData[i++] = -halfDepth / 2;
	vertexData[i++] = 1.0f;
	// Vertex 10
	vertexData[i++] = -halfWidth / 2;
	vertexData[i++] = -halfHeight;
	vertexData[i++] = halfDepth / 2;
	vertexData[i++] = 1.0f;
	// Vertex 11
	vertexData[i++] = halfWidth / 2;
	vertexData[i++] = -halfHeight;
	vertexData[i++] = halfDepth / 2;
	vertexData[i++] = 1.0f;
	// Vertex 12
	vertexData[i++] = halfWidth / 2;
	vertexData[i++] = -halfHeight;
	vertexData[i++] = -halfDepth / 2;
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
	// Vertex 5
	vertexData[i++] = faceColor.red;
	vertexData[i++] = faceColor.green;
	vertexData[i++] = faceColor.blue;
	vertexData[i++] = faceColor.alpha;
	// Vertex 6
	vertexData[i++] = faceColor.red;
	vertexData[i++] = faceColor.green;
	vertexData[i++] = faceColor.blue;
	vertexData[i++] = faceColor.alpha;
	// Vertex 7
	vertexData[i++] = faceColor.red;
	vertexData[i++] = faceColor.green;
	vertexData[i++] = faceColor.blue;
	vertexData[i++] = faceColor.alpha;
	// Vertex 8
	vertexData[i++] = faceColor.red;
	vertexData[i++] = faceColor.green;
	vertexData[i++] = faceColor.blue;
	vertexData[i++] = faceColor.alpha;
	// Vertex 9
	vertexData[i++] = faceColor.red;
	vertexData[i++] = faceColor.green;
	vertexData[i++] = faceColor.blue;
	vertexData[i++] = faceColor.alpha;
	// Vertex 10
	vertexData[i++] = faceColor.red;
	vertexData[i++] = faceColor.green;
	vertexData[i++] = faceColor.blue;
	vertexData[i++] = faceColor.alpha;
	// Vertex 11
	vertexData[i++] = faceColor.red;
	vertexData[i++] = faceColor.green;
	vertexData[i++] = faceColor.blue;
	vertexData[i++] = faceColor.alpha;
	// Vertex 12
	vertexData[i++] = faceColor.red;
	vertexData[i++] = faceColor.green;
	vertexData[i++] = faceColor.blue;
	vertexData[i++] = faceColor.alpha;

	// There are 6 + 12 triangles with 3 vertex each.
	// 1 + (6 * 3) = 19 
	// 3 * 12 = 36
	// 19 + 36 = 55
	short* indexData = new short[55];
	indexData[0] = 54;
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

	// Top 1
	indexData[i++] = 6;
	indexData[i++] = 5;
	indexData[i++] = 8;

	// Top 2
	indexData[i++] = 6;
	indexData[i++] = 8;
	indexData[i++] = 7;

	// Bottom 1
	indexData[i++] = 10;
	indexData[i++] = 9;
	indexData[i++] = 12;

	// Bottom 2
	indexData[i++] = 10;
	indexData[i++] = 12;
	indexData[i++] = 11;

	// Front 1
	indexData[i++] = 10;
	indexData[i++] = 6;
	indexData[i++] = 7;

	// Front 2
	indexData[i++] = 10;
	indexData[i++] = 7;
	indexData[i++] = 11;

	// Back 1
	indexData[i++] = 12;
	indexData[i++] = 8;
	indexData[i++] = 5;

	// Back 2
	indexData[i++] = 12;
	indexData[i++] = 5;
	indexData[i++] = 9;

	// Left 1
	indexData[i++] = 9;
	indexData[i++] = 5;
	indexData[i++] = 6;

	// Left 2
	indexData[i++] = 9;
	indexData[i++] = 6;
	indexData[i++] = 10;

	// Right 1
	indexData[i++] = 11;
	indexData[i++] = 7;
	indexData[i++] = 8;

	// Right 2
	indexData[i++] = 11;
	indexData[i++] = 8;
	indexData[i++] = 12;

	ElementArray arr = { vertexData, indexData };
	return arr;
}


// Box Index Array generator is used for creating buildings.
ElementArray ObjectGenerator::generateBoxIndexedArray(
	float width, float depth, float height, RGBA lineColor) // faceColor
{
	float halfWidth = width / 2.0f;
	float halfDepth = width / 2.0f;
	float halfHeight = width / 2.0f;

	// vertices = 8 * (4 color + 4 position)
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
	

	// 1 + (6 * 2* 3) = 37
	short* indexData = new short[37];
	indexData[0] = 36;
	i = 1;

	// Front
	indexData[i++] = 0;
	indexData[i++] = 1;
	indexData[i++] = 3;

	indexData[i++] = 1;
	indexData[i++] = 2;
	indexData[i++] = 3;

	// Right
	indexData[i++] = 3;
	indexData[i++] = 2;
	indexData[i++] = 4;

	indexData[i++] = 2;
	indexData[i++] = 5;
	indexData[i++] = 4;

	// Back
	indexData[i++] = 4;
	indexData[i++] = 5;
	indexData[i++] = 7;

	indexData[i++] = 5;
	indexData[i++] = 6;
	indexData[i++] = 7;

	// Left
	indexData[i++] = 7;
	indexData[i++] = 6;
	indexData[i++] = 0;

	indexData[i++] = 6;
	indexData[i++] = 1;
	indexData[i++] = 0;

	// Top
	indexData[i++] = 7;
	indexData[i++] = 0;
	indexData[i++] = 4;

	indexData[i++] = 0;
	indexData[i++] = 3;
	indexData[i++] = 4;

	// Bottom
	indexData[i++] = 5;
	indexData[i++] = 2;
	indexData[i++] = 6;

	indexData[i++] = 2;
	indexData[i++] = 1;
	indexData[i++] = 6;

	
	ElementArray arr = { vertexData, indexData };
	return arr;
}