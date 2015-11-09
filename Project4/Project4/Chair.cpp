#include "Chair.h"
#include "Cuboid.h"


Chair::Chair(const string& name, float width, float height, float depth, float thickness, RGBA color):
	OGL3DCompositeObject(name)
{
	this->width = width;
	this->height = height;
	this->depth = depth;
	this->thickness = thickness;
	this->color = color;
	this->surface = new Cuboid("Surface", this->width/2, this->depth, this->thickness, this->color);
	this->backSupport = new Cuboid("BackSupport", this->width, this->depth, this->thickness, this->color);
	this->frontSupport = new Cuboid("FrontSupport", this->width/2, this->depth, this->thickness, this->color);
}


Chair::~Chair()
{
	delete this->surface;
	delete this->backSupport;
	delete this->frontSupport;
}



void Chair::setShaderProgram(GLuint shaderProgram)
{
	this->shaderProgram = shaderProgram;
	this->surface->setShaderProgram(this->shaderProgram);
	this->backSupport->setShaderProgram(this->shaderProgram);
	this->frontSupport->setShaderProgram(this->shaderProgram);
}

void Chair::update(float elapsedSeconds)
{
	OGL3DCompositeObject::update(elapsedSeconds);
}

void Chair::render()
{
	this->surface->referenceFrame = this->referenceFrame;
	this->frameStack.setBaseFrame(this->surface->referenceFrame);
	this->frameStack.rotateX(180.0f);
	this->surface->render(this->frameStack.top());

	this->frameStack.push(); // Table top
	{
		// backSupport
		this->frameStack.rotateZ(90.0f);
		this->frameStack.translate(0, this->height / 4, 0);		
		this->backSupport->render(this->frameStack.top());
		
		// frontSupport
		this->frameStack.translate(this->width/4, -this->height / 2 + this->thickness, 0);
		this->frameStack.translate(-this->width/2, 0, 0);
		this->frontSupport->render(this->frameStack.top());
		
	}
	this->frameStack.pop();
}

void Chair::render(OGLReferenceFrame& frame)
{
	this->referenceFrame = frame;
	render();
}