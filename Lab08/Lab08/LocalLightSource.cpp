#include "LocalLightSource.h"
#include "LightBackForthBehavior.h"



LocalLightSource::LocalLightSource()
{
	this->behavior = NULL;
}


LocalLightSource::~LocalLightSource()
{
}

void LocalLightSource::update(float elapsedSeconds)
{
	if (this->behavior) {		
		this->behavior->update(this, elapsedSeconds);
	}
}
