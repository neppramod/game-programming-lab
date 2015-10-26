#pragma once
#ifndef STOCK_OBJECT_LOADER
#define STOCK_OBJECT_LOADER

#include "ObjectLoader.h"
#include "Core.h"

#define GRAPHICS_FILE "graphics.dat"

class StockObjectLoader :
	public ObjectLoader
{
public:
	StockObjectLoader();
	~StockObjectLoader();

	void loadObjects(GameObjectManager *gameObjectManager);

	// Core is used to read data from the graphics file
	typedef Core::Vertex Vertex;
	Core core;

	// To make vector available to file, it had to be put inside Core
	vector<Vertex> siVertexData;
};

#endif

