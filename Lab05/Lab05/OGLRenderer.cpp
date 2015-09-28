#include "OGLRenderer.h"
#include "WindowsConsoleLogger.h"
#include "OGLShaderCompiler.h"
#include "OGLShaderProgram.h"
#include "OGLShaderManager.h"
#include "ObjectGenerator.h"

#include <cstdlib>
#include <ctime>
#include <glm/gtc/type_ptr.hpp>
#include <glutil/glutil.h>

OGLRenderer::OGLRenderer(OGLShaderManager * shaderMgr)
{
	this->shaderMgr = shaderMgr;
	this->theta = 30;
	this->phi = -30;

	
}

OGLRenderer::~OGLRenderer(void)
{
	for (auto iterator = this->objects.begin(); iterator != this->objects.end(); iterator++) {
		delete iterator->second;
	}
}

bool OGLRenderer::create()
{
	if (!this->setupShaders()) return false;

	GLuint shaderProgram3d = this->shaderMgr->getShaderHandle("ShaderProgram3d");
	GLuint stockShader = this->shaderMgr->getShaderHandle("StockShader");
	GLuint shaderProgram3dv3 = this->shaderMgr->getShaderHandle("ShaderProgram3dv3");

	this->objects["Axes"] = new OGLObject("Axes");
	this->objects["Axes"]->setVertexData(ObjectGenerator::generateRightHandedAxes(5));
	float* data = this->objects["Axes"]->getVertexData();
	VBOObject * lines = OGLObject::createVBOObject("axes");
	lines->buffer = &data[1];
	lines->primitiveType = GL_LINES;
	lines->bufferSizeInBytes = (unsigned int)data[0] * sizeof(float);
	lines->numberOfVertices = 6;
	lines->positionComponent.count = 4;
	lines->positionComponent.type = GL_FLOAT;
	lines->positionComponent.bytesToFirst = 0;
	lines->positionComponent.bytesToNext = 4 * sizeof(float);
	lines->colorComponent.count = 4;
	lines->colorComponent.type = GL_FLOAT;
	lines->colorComponent.bytesToFirst = sizeof(float) * 24;
	lines->colorComponent.bytesToNext = 4 * sizeof(float);
	this->objects["Axes"]->addVBOObject(lines);
	this->objects["Axes"]->shaderProgram = shaderProgram3d;

	this->objects["Surface"] = new OGLObject("Surface");
	this->objects["Surface"]->setVertexData(ObjectGenerator::generateXZSurface(10, 20));
	data = this->objects["Surface"]->getVertexData();
	VBOObject * triangles = OGLObject::createVBOObject("triangles");
	triangles->buffer = &data[1];
	triangles->primitiveType = GL_TRIANGLES;
	triangles->bufferSizeInBytes = (unsigned int)data[0] * sizeof(float);
	triangles->numberOfVertices = 6;
	triangles->positionComponent.count = 4;
	triangles->positionComponent.type = GL_FLOAT;
	triangles->positionComponent.bytesToFirst = 0;
	triangles->positionComponent.bytesToNext = 4 * sizeof(float);
	triangles->colorComponent.count = 4;
	triangles->colorComponent.type = GL_FLOAT;
	triangles->colorComponent.bytesToFirst = sizeof(float) * 24;
	triangles->colorComponent.bytesToNext = 4 * sizeof(float);
	this->objects["Surface"]->addVBOObject(triangles);
	this->objects["Surface"]->shaderProgram = shaderProgram3d;


	this->objects["Pyramid"] = new OGLObject("Pyramid");
	this->createPyramid();
	this->objects["Pyramid"]->shaderProgram = shaderProgram3dv3;


	this->objects["Pyramid2"] = new OGLObject("Pyramid2");
	this->objects["Pyramid2"]->setVertexData(ObjectGenerator::generatePyramid(2, 2, 2));
	data = this->objects["Pyramid2"]->getVertexData();
	triangles = OGLObject::createVBOObject("triangles");
	triangles->buffer = &data[1];
	triangles->primitiveType = GL_TRIANGLES;
	triangles->bufferSizeInBytes = (unsigned int)data[0] * sizeof(float);
	triangles->numberOfVertices = 18;
	triangles->positionComponent.count = 4;
	triangles->positionComponent.type = GL_FLOAT;
	triangles->positionComponent.bytesToFirst = 0;
	triangles->positionComponent.bytesToNext = 4 * sizeof(float);
	triangles->colorComponent.count = 4;
	triangles->colorComponent.type = GL_FLOAT;
	triangles->colorComponent.bytesToFirst = sizeof(float) * 72;
	triangles->colorComponent.bytesToNext = 4 * sizeof(float);
	this->objects["Pyramid2"]->addVBOObject(triangles);
	this->objects["Pyramid2"]->shaderProgram = shaderProgram3d;


	this->objects["Pyramid2"]->referenceFrame.setPosition(0.0f, 0.0f, 5.0f);


	// Call this once
	srand((unsigned int)time(NULL));

	// Create cuboid

	for (int i = 0; i < 10; i++) {
		int h = rand() % 3 + 1;
		int x = rand() % 21 - 10;
		int z = rand() % 21 - 10;
		string pyramidName = "Cuboid" + std::to_string(i + 3);
		this->logger->log(pyramidName);


		this->objects[pyramidName] = new OGLObject(pyramidName);
		this->objects[pyramidName]->setVertexData(ObjectGenerator::generateCubeoid(2.0, 2.0, (float)h));
		data = this->objects[pyramidName]->getVertexData();
		triangles = OGLObject::createVBOObject("triangles");
		triangles->buffer = &data[1];
		triangles->primitiveType = GL_TRIANGLES;
		triangles->bufferSizeInBytes = (unsigned int)data[0] * sizeof(float);
		triangles->numberOfVertices = 36;
		triangles->positionComponent.count = 4;
		triangles->positionComponent.type = GL_FLOAT;
		triangles->positionComponent.bytesToFirst = 0;
		triangles->positionComponent.bytesToNext = 4 * sizeof(float);
		triangles->colorComponent.count = 4;
		triangles->colorComponent.type = GL_FLOAT;
		triangles->colorComponent.bytesToFirst = sizeof(float) * 144;
		triangles->colorComponent.bytesToNext = 4 * sizeof(float);
		this->objects[pyramidName]->addVBOObject(triangles);
		this->objects[pyramidName]->shaderProgram = shaderProgram3d;


		this->objects[pyramidName]->referenceFrame.setPosition((float)x, 0.0f, (float)z);
	}



	GLuint localToWorldMatrixUnif = glGetUniformLocation(shaderProgram3d, "localToWorldMatrix");
	this->cameraToScreenMatrixUnif = glGetUniformLocation(shaderProgram3d, "cameraToScreenMatrix");
	
	this->camera.setPosition(15.0f, this->phi, this->theta);
	this->updateCameraPosition();

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);

	return true;
}

void OGLRenderer::moveCameraRight()
{
	this->theta += 5;
	if (this->theta > 360) this->theta -= 360;

	this->camera.setPosition(15.0f, this->phi, this->theta);
	this->updateCameraPosition();
}

void OGLRenderer::moveCameraLeft()
{
	this->theta -= 5;
	if (this->theta < 0) this->theta = 360 - theta;

	this->camera.setPosition(15.0f, this->phi, this->theta);
	this->updateCameraPosition();
}

void OGLRenderer::moveCameraUp()
{
	this->phi -= 5;
	if (this->phi < -60) this->phi = -60;

	this->camera.setPosition(15.0f, this->phi, this->theta);
	this->updateCameraPosition();
}

void OGLRenderer::moveCameraDown()
{
	this->phi += 5;
	if (this->phi > 60) this->phi = 60;

	this->camera.setPosition(15.0f, this->phi, this->theta);
	this->updateCameraPosition();
}

void OGLRenderer::updateCameraPosition()
{
	GLuint shaderProgram3d = this->shaderMgr->getShaderHandle("ShaderProgram3d");
	GLuint shaderProgram3dv3 = this->shaderMgr->getShaderHandle("ShaderProgram3dv3");

	glUseProgram(shaderProgram3d);
	glUniformMatrix4fv(
		glGetUniformLocation(shaderProgram3d, "worldToCameraMatrix"), 1, GL_FALSE, glm::value_ptr(this->camera.orientation));
	glUseProgram(0);

	glUseProgram(shaderProgram3dv3);
	glUniformMatrix4fv(
		glGetUniformLocation(shaderProgram3dv3, "worldToCameraMatrix"), 1, GL_FALSE, glm::value_ptr(this->camera.orientation));
	glUseProgram(0);
}

void OGLRenderer::addObject(string name, OGLObject *object)
{
	this->objects[name] = object;
}

void OGLRenderer::renderObjects()
{
	GLuint shaderProgram;
	GLuint localToWorldMatrixUnif;
	for (auto iterator = this->objects.begin();
	iterator != this->objects.end();
		iterator++) {
		shaderProgram = iterator->second->shaderProgram;
		localToWorldMatrixUnif = glGetUniformLocation(shaderProgram, "localToWorldMatrix");
		glUseProgram(shaderProgram);
		glUniformMatrix4fv(
			localToWorldMatrixUnif, 1, GL_FALSE,
			glm::value_ptr(iterator->second->referenceFrame.orientation));
		glUseProgram(0);
		iterator->second->render();
	}

}

bool OGLRenderer::setupShaders()
{
	bool result = false;
	result = this->shaderMgr->createShader("StockShader");
	if (!result) return false;
	result = this->shaderMgr->createShader("ShaderProgram3d");
	if (!result) return false;
	result = this->shaderMgr->createShader("ShaderProgram3dv3");
	if (!result) return false;
	return true;
}

void OGLRenderer::updateViewingFrustum(string shaderName, float fov, float aspectRatio, float zNear, float zFar)
{
	GLuint shaderProgram = this->shaderMgr->getShaderHandle(shaderName);

	glutil::MatrixStack persMatrix;
	persMatrix.Perspective(fov, aspectRatio, zNear, zFar);

	glUseProgram(shaderProgram);
	glUniformMatrix4fv(this->cameraToScreenMatrixUnif, 1, GL_FALSE, glm::value_ptr(persMatrix.Top()));
	glUseProgram(0);
}

void OGLRenderer::createPyramid() 
{
	pyramid[0] = { -0.5f, -0.5f, -1.5f };
	pyramid[1] = { 0.5f, -0.5f, -1.5f };
	pyramid[2] = { 0.0f, 0.5f, -2.0f };

	pyramid[3] = { 0.5f, -0.5f, -1.5f };
	pyramid[4] = { 0.5f, -0.5f, -2.5f };
	pyramid[5] = { 0.0f, 0.5f, -2.0f };

	pyramid[6] = { 0.5f, -0.5f, -2.5f };
	pyramid[7] = { -0.5f, -0.5f, -2.5f };
	pyramid[8] = { 0.0f, 0.5f, -2.0f };

	pyramid[9] = { -0.5f, -0.5f, -2.5f };
	pyramid[10] = { -0.5f, -0.5f, -1.5f };
	pyramid[11] = { 0.0f, 0.5f, -2.0f };

	pyramid[12] = { -0.5f, -0.5f, -2.5f };
	pyramid[13] = { 0.5f, -0.5f, -2.5f };
	pyramid[14] = { 0.5f, -0.5f, -1.5f };

	pyramid[15] = { -0.5f, -0.5f, -2.5f };
	pyramid[16] = { 0.5f, -0.5f, -1.5f };
	pyramid[17] = { -0.5f, -0.5f, -1.5f };


	pyramid[18] = { 0.0f, 0.0f, 1.0f };
	pyramid[19] = { 0.0f, 0.0f, 1.0f };
	pyramid[20] = { 0.0f, 0.0f, 1.0f };

	pyramid[21] = { 0.0f, 1.0f, 0.0f };
	pyramid[22] = { 0.0f, 1.0f, 0.0f };
	pyramid[23] = { 0.0f, 1.0f, 0.0f };

	pyramid[24] = { 1.0f, 0.0f, 0.0f };
	pyramid[25] = { 1.0f, 0.0f, 0.0f };
	pyramid[26] = { 1.0f, 0.0f, 0.0f };

	pyramid[27] = { 1.0f, 1.0f, 0.0f };
	pyramid[28] = { 1.0f, 1.0f, 0.0f };
	pyramid[29] = { 1.0f, 1.0f, 0.0f };

	pyramid[30] = { 0.0f, 1.0f, 1.0f };
	pyramid[31] = { 0.0f, 1.0f, 1.0f };
	pyramid[32] = { 0.0f, 1.0f, 1.0f };

	pyramid[33] = { 0.0f, 0.9f, 0.9f };
	pyramid[34] = { 0.0f, 0.9f, 0.9f };
	pyramid[35] = { 0.0f, 0.9f, 0.9f };

	VBOObject * triangles = OGLObject::createVBOObject("triangles");
	triangles->buffer = pyramid;
	triangles->primitiveType = GL_TRIANGLES;
	triangles->bufferSizeInBytes = sizeof(pyramid);
	triangles->numberOfVertices = 18;
	triangles->positionComponent.count = 3;
	triangles->positionComponent.type = GL_FLOAT;
	triangles->positionComponent.bytesToFirst = 0;
	triangles->positionComponent.bytesToNext = sizeof(Triple);
	triangles->colorComponent.count = 3;
	triangles->colorComponent.type = GL_FLOAT;
	triangles->colorComponent.bytesToFirst = sizeof(Triple) * 18;
	triangles->colorComponent.bytesToNext = sizeof(Triple);
	this->objects["Pyramid"]->addVBOObject(triangles);
}


float* ObjectGenerator::generatePyramid(float width, float depth, float height)
{
	// This pyramid's origin is in the center of the base
	float halfWidth = width / 2.0f;
	float halfDepth = depth / 2.0f;

	// 1 size + (6 triangles * 3 vertices each * (4 position + 4 color))
	// 1 + (6 * 3 * (4 + 4)) = 145
	float *data = new float[145];

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

float* ObjectGenerator::generateCubeoid(float width, float depth, float height)
{
	
	// 1 size + (2 triangles * 6 faces * 3 vertices each * (4 position + 4 color)) 8 * 6 * 3 * 2 + 1 = 289	
	float *data = new float[289];

	// The first element stores the number of elements.
	data[0] = 289;


	int i = 1;
	

	// Bottom
	// A
	data[i++] = 0.0f;
	data[i++] = height;
	data[i++] = depth;
	data[i++] = 1.0f;

	// B
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = depth;
	data[i++] = 1.0f;

	// C
	data[i++] = width;
	data[i++] = 0.0f;
	data[i++] = depth;
	data[i++] = 1.0f;

	// A
	data[i++] = 0.0f;
	data[i++] = height;
	data[i++] = depth;
	data[i++] = 1.0f;

	// C
	data[i++] = width;
	data[i++] = 0.0f;
	data[i++] = depth;
	data[i++] = 1.0f;

	// D
	data[i++] = width;
	data[i++] = height;
	data[i++] = depth;
	data[i++] = 1.0f;

	// Back

	// E
	data[i++] = width;
	data[i++] = height;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// F
	data[i++] = width;
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// G
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// E
	data[i++] = width;
	data[i++] = height;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// G
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// H
	data[i++] = 0.0f;
	data[i++] = height;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// Left

	// H
	data[i++] = 0.0f;
	data[i++] = height;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// G
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// B
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = depth;
	data[i++] = 1.0f;


	// H
	data[i++] = 0.0f;
	data[i++] = height;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// B
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = depth;
	data[i++] = 1.0f;

	// A
	data[i++] = 0.0f;
	data[i++] = height;
	data[i++] = depth;
	data[i++] = 1.0f;

	// Right
	// D
	data[i++] = width;
	data[i++] = height;
	data[i++] = depth;
	data[i++] = 1.0f;
	
	// C
	data[i++] = width;
	data[i++] = 0.0f;
	data[i++] = depth;
	data[i++] = 1.0f;

	// F
	data[i++] = width;
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// D
	data[i++] = width;
	data[i++] = height;
	data[i++] = depth;
	data[i++] = 1.0f;

	// F
	data[i++] = width;
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// E
	data[i++] = width;
	data[i++] = height;
	data[i++] = 0.0f;
	data[i++] = 1.0f;


	// Top

	// H
	data[i++] = 0.0f;
	data[i++] = height;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// A
	data[i++] = 0.0f;
	data[i++] = height;
	data[i++] = depth;
	data[i++] = 1.0f;

	// D
	data[i++] = width;
	data[i++] = height;
	data[i++] = depth;
	data[i++] = 1.0f;


	// H
	data[i++] = 0.0f;
	data[i++] = height;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// D
	data[i++] = width;
	data[i++] = height;
	data[i++] = depth;
	data[i++] = 1.0f;

	// E
	data[i++] = width;
	data[i++] = height;
	data[i++] = 0.0f;
	data[i++] = 1.0f;


	// Bottom
	// B
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = depth;
	data[i++] = 1.0f;

	// G
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// F
	data[i++] = width;
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// B
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = depth;
	data[i++] = 1.0f;

	// F
	data[i++] = width;
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// C
	data[i++] = width;
	data[i++] = 0.0f;
	data[i++] = depth;
	data[i++] = 1.0f;




	// Color
	//////////////////////////////////////////



	// Bottom
	// A
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;

	// B
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;

	// C
	data[i++] = 1.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;

	// A
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;

	// C
	data[i++] = 1.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;

	// D
	data[i++] = 1.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;

	// Back

	// E
	data[i++] = 1.0f;
	data[i++] = 1.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// F
	data[i++] = 1.0f;
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// G
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// E
	data[i++] = 1.0f;
	data[i++] = 1.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// G
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// H
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// Left

	// H
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// G
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// B
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;


	// H
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// B
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;

	// A
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;

	// Right
	// D
	data[i++] = 1.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;

	// C
	data[i++] = 1.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;

	// F
	data[i++] = 1.0f;
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// D
	data[i++] = 1.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;

	// F
	data[i++] = 1.0f;
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// E
	data[i++] = 1.0f;
	data[i++] = 1.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;


	// Top

	// H
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// A
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;

	// D
	data[i++] = 1.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;


	// H
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// D
	data[i++] = 1.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;

	// E
	data[i++] = 1.0f;
	data[i++] = 1.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;


	// Bottom
	// B
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;

	// G
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// F
	data[i++] = 1.0f;
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// B
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;

	// F
	data[i++] = 1.0f;
	data[i++] = 0.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;

	// C
	data[i++] = 1.0f;
	data[i++] = 0.0f;
	data[i++] = 1.0f;
	data[i++] = 1.0f;

	return data;
}
