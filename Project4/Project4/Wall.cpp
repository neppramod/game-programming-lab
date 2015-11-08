#include "Wall.h"
#include "ObjectGenerator.h"
#include "Cuboid.h"

Wall::Wall(const string& name, float width, float depth, float thickness) :
	OGL3DCompositeObject(name)
{

	this->color = RGBA{ 1.0f, 0.0f, 0.0f };
	Wall(this->name, this->width, this->depth, this->thickness, this->color);	
}

Wall::Wall(const string& name, float width, float depth, float thickness, RGBA color):
	OGL3DCompositeObject(name)
{
	this->thickness = thickness;
	this->width = width;
	this->depth = depth;
	this->color = color;

	if (DRAW_AXES) {
		VBOObject* vboObject;

		axes = new OGL3DObject("Axes");
		axes->setIndexedArrayType();
		ElementArray arr = ObjectGenerator::generateRightHandedAxesIndexedArray(5);
		axes->setVertexData(arr.vertexData);
		axes->setIndexData(arr.indexData);
		vboObject = OGLObject::createVBOObject(
			"Axes", arr.vertexData, arr.indexData, GL_LINES);
		axes->addVBOObject(vboObject);
	}
	
	this->surface = new Cuboid("Wall", this->width, this->depth, this->thickness, this->color);
}


Wall::~Wall()
{
	if (DRAW_AXES)
		delete this->axes;
	delete this->surface;
}

void Wall::setShaderProgram(GLuint shaderProgram)
{
	this->shaderProgram = shaderProgram;
	this->surface->setShaderProgram(this->shaderProgram);
	
	if (DRAW_AXES)
		this->axes->setShaderProgram(this->shaderProgram);
}

void Wall::update(float elapsedSeconds)
{
	OGL3DCompositeObject::update(elapsedSeconds);
}

void Wall::render()
{
	this->surface->referenceFrame = this->referenceFrame;
	this->frameStack.setBaseFrame(this->surface->referenceFrame);
	this->surface->render();

	if (DRAW_AXES) {
		this->frameStack.push();
		{
			// Axes		
			this->frameStack.translate(0, this->thickness, 0);
			this->axes->render(this->frameStack.top());
		}
		this->frameStack.pop();
	}
}

void Wall::render(OGLReferenceFrame& frame)
{
	this->referenceFrame = frame;
	render();
}


