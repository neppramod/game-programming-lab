#include "WallWithDoor.h"
#include "Cuboid.h"

WallWithDoor::WallWithDoor(string &name, float width, float height, float depth) :
	OGL3DCompositeObject(name)
{
	this->color = RGBA{ 1.0f, 0.0f, 0.0f };
	this->thickness = 0.1f;
	WallWithDoor(this->name, this->width, this->depth, this->thickness, this->color);
}

WallWithDoor::WallWithDoor(const string& name, float width, float depth, float thickness, RGBA color)
	:OGL3DCompositeObject(name)
{
	this->width = width;
	this->depth = depth;
	this->thickness = thickness;
	this->color = color;

	this->eastWallTop = new Cuboid("EastWallTop", this->width, this->depth / 2, this->thickness, this->color);
	this->eastWallBottomLeft = new Cuboid("EastWallBottomLeft", this->width * 0.35, this->depth / 2, this->thickness, this->color);
	this->eastWallBottomRight = new Cuboid("EastWallBottomRight", this->width * 0.35, this->depth / 2, this->thickness, this->color);
}




WallWithDoor::~WallWithDoor()
{
	delete this->eastWallTop;
	delete this->eastWallBottomLeft;
	delete this->eastWallBottomRight;
}

void WallWithDoor::setShaderProgram(GLuint shaderProgram)
{
	this->shaderProgram = shaderProgram;
	this->eastWallTop->setShaderProgram(this->shaderProgram);
	this->eastWallBottomLeft->setShaderProgram(this->shaderProgram);
	this->eastWallBottomRight->setShaderProgram(this->shaderProgram);
}

void WallWithDoor::update(float elapsedSeconds)
{
	OGL3DCompositeObject::update(elapsedSeconds);
}

void WallWithDoor::render()
{
	this->eastWallTop->referenceFrame = this->referenceFrame;
	this->frameStack.setBaseFrame(this->eastWallTop->referenceFrame);
	this->eastWallTop->render();

	this->frameStack.push();
	{
		// East bottom right
		this->frameStack.translate(width/2 - this->width/2 * 0.35, 0, depth / 2);
		this->eastWallBottomRight->render(this->frameStack.top());

		// East bottom left
		this->frameStack.translate(-width + 0.35 * width, 0, 0);
		this->eastWallBottomLeft->render(this->frameStack.top());
	}
	this->frameStack.pop();
}

void WallWithDoor::render(OGLReferenceFrame &frame)
{
	this->referenceFrame = frame;
	render();
}