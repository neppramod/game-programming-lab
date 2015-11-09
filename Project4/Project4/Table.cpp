#include "Table.h"
#include "Cuboid.h"


Table::Table(const string& name, float width, float height, float depth, float thickness, RGBA color): 
	OGL3DCompositeObject(name)
{
	this->width = width;
	this->height = height;
	this->depth = depth;
	this->thickness = thickness;
	this->color = color;

	this->surface = new Cuboid("Surface", this->width, this->depth, this->thickness, this->color);
	this->base = new Cuboid("LeftNorthLeg", this->width * 0.7f, this->depth * 0.7f, this->height, this->color);
	

}


Table::~Table()
{
	delete this->surface;
	delete this->base;	
}

void Table::setShaderProgram(GLuint shaderProgram)
{
	this->shaderProgram = shaderProgram;
	this->surface->setShaderProgram(this->shaderProgram);
	this->base->setShaderProgram(this->shaderProgram);	
}

void Table::update(float elapsedSeconds)
{
	OGL3DCompositeObject::update(elapsedSeconds);
}

void Table::render()
{
	this->surface->referenceFrame = this->referenceFrame;	
	this->frameStack.setBaseFrame(this->surface->referenceFrame);
	this->frameStack.rotateX(180.0f);
	this->surface->render(this->frameStack.top());	

	this->frameStack.push(); // Table top
	{
		this->frameStack.rotateX(180.0f);
		this->frameStack.translate(0, this->height / 2, 0);
		this->base->render(this->frameStack.top());
	}
	this->frameStack.pop();
}

void Table::render(OGLReferenceFrame& frame)
{
	this->referenceFrame = frame;
	render();
}