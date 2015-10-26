#pragma once
#ifndef RENDERER
#define RENDERER

class Logger;

class Renderer
{
protected:
	Logger* logger;

public:
	Renderer();
	virtual ~Renderer();

	virtual bool create() = 0;
	virtual void renderObjects() = 0;

	void setLogger(Logger* logger) { this->logger = logger; }
};

#endif

