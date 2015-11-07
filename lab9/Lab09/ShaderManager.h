#pragma once
#ifndef SHADER_MANAGER
#define SHADER_MANAGER

#include <string>
using std::string;

class Logger;
class BaseShader;

class ShaderManager
{
protected:
	Logger *logger;

public:
	ShaderManager();
	virtual ~ShaderManager();

	virtual bool createShader(const string& shaderName) = 0;

	virtual BaseShader* getShader(const string& shaderName) = 0;

	virtual void setLogger(Logger *logger) { this->logger = logger; }
};

#endif

