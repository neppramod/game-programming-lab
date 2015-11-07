#include "Sword.h"
#include "Cuboid.h"
#include "Axis.h"


Sword::Sword(const string& name) : OGL3DCompositeObject(name)
{
	this->hilt = new Cuboid("hilt", 0.2f, 0.1f, 1.3f, { 1,0,0,1 });
	this->crossguard = new Cuboid("corssguard", 0.25f, 0.25f, 0.25f, { 0,1,0,1 });
	this->blade = new Cuboid("blade", 0.1f, 3.8f, 0.1f, { 0, 0, 1, 1 });
	this->axis = new Axis("Axes", 2.0f);
}


Sword::~Sword()
{
	delete this->hilt;
	delete this->crossguard;
	delete this->blade;
	delete this->axis;
}

void Sword::setShaderProgram(GLuint shaderProgram)
{
	this->shaderProgram = shaderProgram;
	this->hilt->setShaderProgram(this->shaderProgram);
	this->crossguard->setShaderProgram(this->shaderProgram);
	this->blade->setShaderProgram(this->shaderProgram);
	this->axis->setShaderProgram(this->shaderProgram);
}

void Sword::update(float elapsedSeconds)
{
	OGL3DCompositeObject::update(elapsedSeconds);
}

void Sword::render()
{
	this->hilt->referenceFrame = this->referenceFrame;
	this->frameStack.setBaseFrame(this->hilt->referenceFrame);
	this->frameStack.rotateX(180.0f);	
	this->hilt->render();

	this->frameStack.push();
	{
		this->frameStack.translate(0, -0.775f, 0);
		this->frameStack.rotateX(90.0f);

		this->crossguard->referenceFrame = this->frameStack.top();
		this->crossguard->render();

		this->frameStack.push();
		{
			this->frameStack.translate(0, 0, 0.725f);
			this->axis->render(this->frameStack.top());
						
			this->blade->referenceFrame = this->frameStack.top();
			this->blade->referenceFrame.translate(0, 0, 1.225f);
			this->blade->render();
			
		}
		this->frameStack.pop();
	}
	this->frameStack.pop();
}