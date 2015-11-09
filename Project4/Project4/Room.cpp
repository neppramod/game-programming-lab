#include "Room.h"
#include "Cuboid.h"
#include "Wall.h"
#include "WallWithDoor.h"
#include "Table.h"
#include "Chair.h"


Room::Room(const string& name, float width, float height, float depth):
	OGL3DCompositeObject(name)
{
	this->thickness = 0.1f;
	this->width = width;
	this->depth = depth;
	this->height = height;
	
	// Walls
	this->floor = new Wall("Floor", this->width, this->depth, this->thickness, { 0.5, 0.5f, 0, 1 });
	this->ceiling = new Wall("Ceiling", this->width, this->depth, this->thickness, { 0.4f, 0.4f, 0, 1 });
	this->northWall = new Wall("NorthWall", this->width, this->depth, this->thickness, { 0.4f, 0.4f, 0, 1 });
	this->southWall = new Wall("SouthWall", this->width, this->depth, this->thickness, { 0.4f, 0.4f, 0, 1 });
	this->westWall = new Wall("WestWall", this->width, this->depth, this->thickness, { 0.4f, 0.4f, 0, 1 });
	this->eastWall = new WallWithDoor("WestWall", this->width, this->depth, this->thickness, { 0.4f, 0.4f, 0, 1 });

	// Add a table
	this->table = new Table("Table");

	// Add a chair
	this->chair = new Chair("Chair", 1, 1, 1, 0.1f, { 0,0,1.0f });
	this->chair2 = new Chair("Chair2", 1, 1, 1, 0.1f, { 0,0,1.0f });
}


Room::~Room()
{
	delete this->floor;
	delete this->ceiling;
	delete this->northWall;
	delete this->southWall;
	delete this->westWall;
	delete this->eastWall;
	delete this->table;
	delete this->chair;
	delete this->chair2;
}

void Room::setShaderProgram(GLuint shaderProgram)
{
	this->shaderProgram = shaderProgram;
	this->floor->setShaderProgram(this->shaderProgram);
	this->ceiling->setShaderProgram(this->shaderProgram);
	this->northWall->setShaderProgram(this->shaderProgram);
	this->southWall->setShaderProgram(this->shaderProgram);
	this->westWall->setShaderProgram(this->shaderProgram);
	this->eastWall->setShaderProgram(this->shaderProgram);	
	this->table->setShaderProgram(this->shaderProgram);
	this->chair->setShaderProgram(this->shaderProgram);
	this->chair2->setShaderProgram(this->shaderProgram);
}

void Room::update(float elapsedSeconds)
{
	OGL3DCompositeObject::update(elapsedSeconds);
}

void Room::render()
{
	this->floor->referenceFrame = this->referenceFrame;		
	this->floor->referenceFrame.translate(0, -2 * this->thickness, 0);	
	this->frameStack.setBaseFrame(this->floor->referenceFrame);
	this->floor->render();
	

	this->frameStack.push(); // Floor
	{
		// North Wall
		this->frameStack.rotateX(90.0f);
		this->frameStack.translate(0, -this->width/2, -this->height/2);
		this->northWall->render(this->frameStack.top());
		//this->northWall->render();

		// South Wall
		this->frameStack.rotateZ(180.0f);
		this->frameStack.translate(0, -this->width, 0);
		this->southWall->render(this->frameStack.top());

		// West Wall
		this->frameStack.rotateZ(90.0f);
		this->frameStack.translate(this->width / 2, -this->height / 2, 0);
		this->westWall->render(this->frameStack.top());

		// Ceiling
		this->frameStack.rotateX(90.0f);
		this->frameStack.translate(0, -this->width / 2, -this->height/2);
		this->ceiling->render(this->frameStack.top());

		// East Wall
		this->frameStack.rotateX(90.0f);
		this->frameStack.translate(0, -this->depth / 2, -0.25*this->height);
		this->frameStack.rotateX(180.0f);
		this->eastWall->render(this->frameStack.top());

		// Table
		this->frameStack.translate(0, 0, 0);
		this->frameStack.rotateX(90.0f);
		this->frameStack.translate(0, this->height - 3.0f, 0);
		this->frameStack.rotateY(90.0f);
		this->frameStack.translate(this->width / 2, 0, 0);  // At this point the reference is pointing at the center of the room

		this->frameStack.translate(0, 0, -this->depth / 2 + 2.0f);
		this->table->render(this->frameStack.top());

		// Chair
		this->frameStack.translate(2.0f, 0, 0);
		this->frameStack.rotateY(180);
		this->chair->render(this->frameStack.top());

		// Chair 2
		this->frameStack.translate(4.0f, 0, 0);
		this->frameStack.rotateY(180);
		this->chair->render(this->frameStack.top());
	}
	this->frameStack.pop();
}
