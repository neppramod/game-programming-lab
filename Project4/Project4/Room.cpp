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

	// Read the graphics data
	core.ReadGraphicsFile(GRAPHICS_FILE, siVertexData);

	int i = 0; // This will help iterate the siVertexData;

	
	// Walls
	this->floor = new Wall("Floor", this->width, this->depth, this->thickness, { siVertexData[i].red, siVertexData[i].green, siVertexData[i].blue, 1 });
	i++;

	this->ceiling = new Wall("Ceiling", this->width, this->depth, this->thickness, { siVertexData[i].red, siVertexData[i].green, siVertexData[i].blue, 1 });
	i++;

	this->northWall = new Wall("NorthWall", this->width, this->depth, this->thickness, { siVertexData[i].red, siVertexData[i].green, siVertexData[i].blue, 1 });
	i++;

	this->southWall = new Wall("SouthWall", this->width, this->depth, this->thickness, { siVertexData[i].red, siVertexData[i].green, siVertexData[i].blue, 1 });
	i++;

	this->westWall = new Wall("WestWall", this->width, this->depth, this->thickness, { siVertexData[i].red, siVertexData[i].green, siVertexData[i].blue, 1 });
	i++;

	this->eastWall = new WallWithDoor("WestWall", this->width, this->depth, this->thickness, { siVertexData[i].red, siVertexData[i].green, siVertexData[i].blue, 1 });
	i++;

	// Light source (stacked one over another)
	this->lightSourceObject = new Cuboid("LightSource", siVertexData[i].x, siVertexData[i].y, siVertexData[i].z, { siVertexData[i].red, siVertexData[i].green, siVertexData[i].blue });
	i++;

	this->lightSourceSecondObject = new Cuboid("LightSource2", siVertexData[i].x, siVertexData[i].y, siVertexData[i].z, { siVertexData[i].red, siVertexData[i].green, siVertexData[i].blue });
	i++;

	// Add a table
	this->table = new Table("Table");

	// Add a chair
	this->chair = new Chair("Chair", siVertexData[i].x, siVertexData[i].y, siVertexData[i].z, 0.1f, { siVertexData[i].red, siVertexData[i].green, siVertexData[i].blue });
	i++;

	this->chair2 = new Chair("Chair2", siVertexData[i].x, siVertexData[i].y, siVertexData[i].z, 0.1f, { siVertexData[i].red, siVertexData[i].green, siVertexData[i].blue});	
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
	delete this->lightSourceObject;
	delete this->lightSourceSecondObject;
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
	this->lightSourceObject->setShaderProgram(this->shaderProgram);
	this->lightSourceSecondObject->setShaderProgram(this->shaderProgram);
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
		
		this->frameStack.push(); // Ceiling
		{
			this->frameStack.translate(0, 0, 0);			
			this->lightSourceObject->render(this->frameStack.top());

			this->frameStack.translate(0, 0.375, 0);
			this->lightSourceSecondObject->render(this->frameStack.top());
		}
		this->frameStack.pop();

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
