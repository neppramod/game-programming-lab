#pragma once
#ifndef STOCK_OBJECT_LOADER
#define STOCK_OBJECT_LOADER

#include "ObjectLoader.h"

class StockObjectLoader :
	public ObjectLoader
{
public:
	StockObjectLoader();
	~StockObjectLoader();

	void loadObjects(GameObjectManager *gameObjectManager);
};

#endif

