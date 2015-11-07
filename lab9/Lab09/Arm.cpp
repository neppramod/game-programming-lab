#include "Arm.h"
#include "Cuboid.h"
#include "Axis.h"
#include "Sword.h"



Arm::Arm(const string& name) : OGL3DCompositeObject(name)
{
	this->shoulder = new Cuboid("shoulder", 0.3f, 0.3f, 0.3f, { 1, 0, 0, 1 });
	this->bicep = new Cuboid("bicep", 0.25f, 1.25f, 0.25f, { 0, 1, 0, 1 });
	this->forearm = new Cuboid("forearm", 0.2f, 1.25f, 0.2f, { 0, 0, 1, 1 });
	this->hand = new Cuboid("hand", 0.2f, 0.2f, 0.2f, { 1, 1, 0, 1 });
	this->axis = new Axis("Axes", 2.0f);	
	this->angleX = 0;
	this->state = DOWN_MOVEMENT;
}


Arm::~Arm()
{
	delete this->shoulder;
	delete this->bicep;
	delete this->forearm;
	delete this->hand;
	delete this->axis;

}


void Arm::setShaderProgram(GLuint shaderProgram)
{
	this->shaderProgram = shaderProgram;
	this->shoulder->setShaderProgram(this->shaderProgram);
	this->bicep->setShaderProgram(this->shaderProgram);
	this->forearm->setShaderProgram(this->shaderProgram);
	this->hand->setShaderProgram(this->shaderProgram);
	this->axis->setShaderProgram(this->shaderProgram);

}

void Arm::update(float elapsedSeconds)
{
	OGL3DCompositeObject::update(elapsedSeconds);

	switch (this->state) {
		case UP_MOVEMENT: {
			this->angleX += (30 * elapsedSeconds);
			if (this->angleX > 30) {
				//this->angleX -= 30;
				this->state = DOWN_MOVEMENT;
			}
			break;
		}
		case DOWN_MOVEMENT: {
			this->angleX -= (30 * elapsedSeconds);
			if (this->angleX < 0) {
				//this->angleX += 30;
				this->state = UP_MOVEMENT;
			}
			break;
		}

	}
}

void Arm::render()
{
	this->shoulder->referenceFrame = this->referenceFrame;
	this->frameStack.setBaseFrame(this->shoulder->referenceFrame);	
	this->shoulder->render();

	this->frameStack.push();
	{
		this->frameStack.translate(0, -0.70f, 0.1);
		this->frameStack.rotateX(80.0f);
		this->bicep->referenceFrame = this->frameStack.top();
		this->bicep->render();

		this->frameStack.push();
		{			
			this->frameStack.translate(0, 0.5f, 0.65f);
			this->frameStack.rotateX(angleX);;
			this->frameStack.rotateX(-90.0f);			
			//
			this->forearm->referenceFrame = this->frameStack.top();			
			this->forearm->render();
			this->axis->render(this->frameStack.top());
			//this->axis->render(this->frameStack.top());

			this->frameStack.push();			{

				this->frameStack.translate(0, 0, 0.725f);
				this->hand->referenceFrame = this->frameStack.top();
				this->hand->render();

				this->frameStack.push();
				{
					this->sword->referenceFrame = this->frameStack.top();
					this->sword->render();
				}
				this->frameStack.pop();
			}
			this->frameStack.pop();
		}
		this->frameStack.pop();
	}
	this->frameStack.pop();
}

void Arm::addSword(Sword *sword)
{
	this->sword = sword;
}